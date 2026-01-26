#pragma once

#include "Asset.h"
#include "AssetMetadata.h"
#include "AssetImporter.h"

#include "RealEngine/Types/HashMap.h"

#include <memory>

namespace RealEngine {
	// All Editor related assets are managed by the Editor
	// This is only for the game assets
	class AssetManager {
	public:
		AssetManager() = default;
		~AssetManager() = default;

		void Save();
		// Clear and reload the asset registry from disk
		void Load();

		AssetHandle ImportAssetIfNeeded(const std::filesystem::path& filePath);
		AssetHandle ImportAsset(const std::filesystem::path& filePath);

		template<typename T>
		Ref<T> GetAsset(AssetHandle handle) {
			RE_PROFILE_FUNCTION();
			// 1. Check if the asset is imported
			if (!IsAssetValid(handle)) {
				RE_CORE_ERROR("Asset not imported with handle: {}", (uint64_t)handle);
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
		void ClearUnusedAssets();

		AssetMetadata* GetAssetMetadata(AssetHandle handle) {
			RE_PROFILE_FUNCTION();
			RE_CORE_ASSERT(IsAssetValid(handle), "Achievement unlocked how did we get here?");

			return &m_AssetRegistry.at(handle);
		}

		// Check if the asset is imported
		bool IsAssetValid(AssetHandle handle) const;
		// Check if the asset is loaded in memory
		bool IsAssetLoaded(AssetHandle handle) const;
	private:
		template<typename T>
		Ref<T> LoadAsset(AssetHandle handle) {
			RE_PROFILE_FUNCTION();
			RE_CORE_ASSERT(IsAssetValid(handle), "Achivment unlocked how did we get here?");

			AssetMetadata& assetMetaData = m_AssetRegistry.at(handle);
			RE_CORE_INFO("Loading {} asset with handle: {}", Utils::GetAssetTypeString(assetMetaData.Type), (uint64_t)handle);

			Ref<Asset> asset = AssetImporter::ImportAsset(assetMetaData);
			asset->m_Handle = handle;
			m_LoadedAssets.emplace(handle, asset);

			return std::static_pointer_cast<T>(asset);
		}
	private:
		// If the asset is out of scope reload it
		HashMap<AssetHandle, AssetMetadata> m_AssetRegistry;
		HashMap<AssetHandle, Ref<Asset>> m_LoadedAssets;
	};
}