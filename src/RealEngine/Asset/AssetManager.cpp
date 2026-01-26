#include "AssetManager.h"

#include "RealEngine/Core/Project.h"

#include <ryml_std.hpp>

namespace RealEngine {
	namespace Utils {
		static HashMap<std::filesystem::path, AssetType> s_AssetExtensionMap = {
			{ ".png", AssetType::Texture2D },
			{ ".jpg", AssetType::Texture2D },
			{ ".jpeg", AssetType::Texture2D },
			{ ".shader", AssetType::Shader },
			{ ".ttf", AssetType::Font }
		};

		static AssetType GetAssetTypeFromFileExtension(const std::filesystem::path& extension) {
			if (s_AssetExtensionMap.find(extension) == s_AssetExtensionMap.end()) {
				RE_CORE_ERROR("Could not find AssetType for {}", extension);
				return AssetType::None;
			}

			return s_AssetExtensionMap.at(extension);
		}

		static std::any CreateDefaultCustomMetadata(AssetType type) {
			switch (type) {
				case AssetType::Texture2D:
					return Texture2DMetadata{};
				case AssetType::Font:
					return {}; // No custom metadata for fonts yet
				default:
					RE_CORE_ASSERT(false, "AssetType {} is not supported for CustomMetadata", (uint16_t)type);
					return {};
			}
		}

		// Helper function to write CustomMetadata to a ryml node
		static void WriteCustomMetadata(const AssetMetadata& metadata, ryml::NodeRef& assetNode) {
			if (!metadata.CustomMetadata.has_value())
				return;

			ryml::NodeRef customNode = assetNode["CustomMetadata"];
			customNode |= ryml::MAP;
			switch (metadata.Type) {
				case AssetType::Texture2D:
					customNode << std::any_cast<Texture2DMetadata>(metadata.CustomMetadata);
					break;
				default:
					RE_CORE_ASSERT(false, "AssetType {} is not supported for CustomMetadata", (uint16_t)metadata.Type);
					break;
			}
		}

		// Helper function to read CustomMetadata from a ryml node
		static void ReadCustomMetadata(AssetMetadata& metadata, const ryml::ConstNodeRef& assetNode) {
			if (!assetNode.has_child("CustomMetadata"))
				return;

			ryml::ConstNodeRef customNode = assetNode["CustomMetadata"];
			switch (metadata.Type) {
				case AssetType::Texture2D: {
					Texture2DMetadata value;
					customNode >> value;
					metadata.CustomMetadata = value;
					break;
				}
				default:
					RE_CORE_ASSERT(false, "AssetType {} is not supported for CustomMetadata", (uint16_t)metadata.Type);
					break;

			}
		}
	}

	void AssetManager::Save() {
		RE_PROFILE_FUNCTION();

		std::filesystem::path assetRegistryPath = Project::GetProjectPath() / "asset_registry.realdb";
		ryml::Tree tree;
		ryml::NodeRef root = tree.rootref();

		root |= ryml::MAP;
		ryml::NodeRef assetsNode = root.append_child();
		assetsNode.set_key("Assets");
		assetsNode |= ryml::SEQ;

		for (const auto& [handle, metadata] : m_AssetRegistry) {
			ryml::NodeRef assetNode = assetsNode.append_child();
			assetNode |= ryml::MAP;
			assetNode.append_child() << ryml::key("Handle") << handle;
			assetNode.append_child() << ryml::key("FilePath") << Project::GetRelativePathToAssetFolder(metadata.FilePath);
			assetNode.append_child() << ryml::key("Type") << (uint16_t)metadata.Type;
			Utils::WriteCustomMetadata(metadata, assetNode);
		}

		FileHelper fileHelper(assetRegistryPath, "w");
		FILE* file = fileHelper.GetFileHandle();
		ryml::emit_yaml(tree, file);

		RE_CORE_INFO("Saved asset registry with {} assets to {}", m_AssetRegistry.size(), assetRegistryPath.string());
	}

	void AssetManager::Load() {
		RE_PROFILE_FUNCTION();
		Clear();

		std::filesystem::path assetRegistryPath = Project::GetProjectPath() / "asset_registry.realdb";
		if (!std::filesystem::is_regular_file(assetRegistryPath)) {
			RE_CORE_WARN("No asset registry found at {}", assetRegistryPath.string());
			return;
		}
		
		// Read in file
		FileHelper fileHelper(assetRegistryPath, "r");
		std::string fileContents = fileHelper.ReadAllText();
		ryml::Tree tree = ryml::parse_in_place(ryml::to_csubstr(assetRegistryPath.filename().string()), ryml::to_substr(fileContents));
		ryml::ConstNodeRef root = tree.rootref();
		RE_CORE_ASSERT(!tree.empty(), "Failed to parse asset registry file: Tree is empty");
		if (root.has_child("Assets")) {
			ryml::ConstNodeRef assetsNode = root["Assets"];
			for (auto assetNode : assetsNode.children()) {
				AssetHandle handle;
				std::string filePathStr;
				uint16_t typeValue;

				assetNode["Handle"] >> handle;
				assetNode["FilePath"] >> filePathStr;
				assetNode["Type"] >> typeValue;
				
				AssetMetadata metadata;
				metadata.FilePath = Project::ResolveAssetPathFromAssetFolder(filePathStr);
				metadata.Type = static_cast<AssetType>(typeValue);
				Utils::ReadCustomMetadata(metadata, assetNode);

				if(std::filesystem::is_regular_file(metadata.FilePath)) {
					m_AssetRegistry.emplace(handle, metadata);
				}
				else {
					RE_CORE_WARN("Asset file missing: {}", metadata.FilePath.string());
				}
			}
		}
		else {
			RE_CORE_WARN("Asset registry file missing 'Assets' node");
		}
	}

	AssetHandle AssetManager::ImportAssetIfNeeded(const std::filesystem::path& filePath) {
		RE_PROFILE_FUNCTION();

		AssetHandle handle(filePath);
		if (IsAssetValid(handle)) // Already imported
			return handle;

		return ImportAsset(filePath);
	}

	AssetHandle AssetManager::ImportAsset(const std::filesystem::path& filePath) {
		RE_PROFILE_FUNCTION();

		RE_CORE_INFO("Importing asset: {}", filePath.string());
		AssetMetadata metadata;
		metadata.FilePath = filePath;
		metadata.Type = Utils::GetAssetTypeFromFileExtension(filePath.extension());
		metadata.CustomMetadata = Utils::CreateDefaultCustomMetadata(metadata.Type);

		AssetHandle handle(filePath);
		m_AssetRegistry.emplace(handle, metadata);
		return handle;
	}

	void AssetManager::Clear() {
		RE_PROFILE_FUNCTION();

		m_AssetRegistry.clear();
		m_LoadedAssets.clear();
	}

	void AssetManager::ClearUnusedAssets() {
		RE_PROFILE_FUNCTION();

		for (auto it = m_LoadedAssets.begin(); it != m_LoadedAssets.end();) {
			if (it->second.use_count() == 1) {
				AssetHandle handle = it->first;
				std::filesystem::path& path = m_AssetRegistry[handle].FilePath;

				AssetType type = m_AssetRegistry[handle].Type;
				RE_CORE_INFO("Unloading unused {} asset with filename: {}", Utils::GetAssetTypeString(type), path.filename());

				it = m_LoadedAssets.erase(it);
			}
			else {
				it++;
			}
		}
	}

	bool AssetManager::IsAssetValid(AssetHandle handle) const {
		return m_AssetRegistry.find(handle) != m_AssetRegistry.end();
	}

	bool AssetManager::IsAssetLoaded(AssetHandle handle) const {
		return m_LoadedAssets.find(handle) != m_LoadedAssets.end();
	}
}
