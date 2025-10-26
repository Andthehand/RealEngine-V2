#include "AssetManager.h"

#include "RealEngine/Core/Project.h"

#include <ryml_std.hpp>

namespace RealEngine {
	namespace Utils {
		static std::unordered_map<std::filesystem::path, AssetType> s_AssetExtensionMap = {
			{ ".png", AssetType::Texture2D },
			{ ".jpg", AssetType::Texture2D },
			{ ".jpeg", AssetType::Texture2D },
			{ ".shader", AssetType::Shader }
		};

		static AssetType GetAssetTypeFromFileExtension(const std::filesystem::path& extension) {
			if (s_AssetExtensionMap.find(extension) == s_AssetExtensionMap.end()) {
				RE_CORE_ERROR("Could not find AssetType for {}", extension);
				return AssetType::None;
			}

			return s_AssetExtensionMap.at(extension);
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
			assetNode.append_child() << ryml::key("FilePath") << metadata.FilePath;
			assetNode.append_child() << ryml::key("Type") << (uint16_t)metadata.Type;
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
				metadata.FilePath = filePathStr;
				metadata.Type = static_cast<AssetType>(typeValue);
				m_AssetRegistry.emplace(handle, metadata);
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

		AssetHandle handle(filePath);
		m_AssetRegistry.emplace(handle, metadata);
		return handle;
	}

	void AssetManager::Clear() {
		RE_PROFILE_FUNCTION();

		m_AssetRegistry.clear();
		m_LoadedAssets.clear();
	}
}