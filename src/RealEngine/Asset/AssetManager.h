#pragma once

#include "Asset.h"
#include "AssetMetadata.h"
#include "AssetImporter.h"

#include <memory>

namespace RealEngine {
	// All Editor related assets are managed by the Editor
	// This is only for the game assets
	class AssetManager {
	public:
		AssetManager() = default;
		~AssetManager() = default;

		void Save();
		void Load();

		AssetHandle ImportAssetIfNeeded(const std::filesystem::path& filePath);
		AssetHandle ImportAsset(const std::filesystem::path& filePath);

		template<typename T>
		Ref<T> GetAsset(AssetHandle handle) {
			RE_PROFILE_FUNCTION();
			// 1. Check if the asset is imported
			if (!IsAssetValid(handle)) {
				RE_CORE_ASSERT(false, "Asset not imported with handle: {}", (uint64_t)handle);
				return nullptr;
			}

			// 2. Check if the asset is loaded and load if not
			if (IsAssetLoaded(handle)) {
				// 3. Return the asset casted to the correct type
				return std::static_pointer_cast<T>(m_LoadedAssets.at(handle));
			}
			else {
				// 3. Return the asset casted to the correct type
				return LoadAsset<T>(handle);
			}
		}

		void Clear();

		bool IsAssetValid(AssetHandle handle) const {
			return m_AssetRegistry.find(handle) != m_AssetRegistry.end();
		}

		bool IsAssetLoaded(AssetHandle handle) const {
			return m_LoadedAssets.find(handle) != m_LoadedAssets.end();
		}
	private:
		template<typename T>
		Ref<T> LoadAsset(AssetHandle handle) {
			RE_PROFILE_FUNCTION();
			RE_CORE_ASSERT(IsAssetValid(handle), "Achivment unlocked how did we get here?");
			RE_CORE_INFO("Loading asset with handle: {}", (uint64_t)handle);

			auto& assetMetaData = m_AssetRegistry.at(handle);
			Ref<Asset> asset = AssetImporter::ImportAsset(assetMetaData);
			asset->m_Handle = handle;
			m_LoadedAssets.emplace(handle, asset);

			return std::static_pointer_cast<T>(asset);
		}
	private:
		// If the asset is out of scope reload it
		std::unordered_map<AssetHandle, AssetMetadata> m_AssetRegistry;
		std::unordered_map<AssetHandle, Ref<Asset>> m_LoadedAssets;
	};
}