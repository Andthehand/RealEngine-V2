#include "AssetImporter.h"

namespace RealEngine {
	using AssetImportFunction = std::function<Ref<Asset>(const AssetMetadata&)>;
	static HashMap<AssetType, AssetImportFunction> s_AssetImportFunctions = {
		{ AssetType::Texture2D, TextureImporter::ImportTexture2D },
	};

	Ref<Asset> AssetImporter::ImportAsset(const AssetMetadata& metadata) {
		if (s_AssetImportFunctions.find(metadata.Type) == s_AssetImportFunctions.end()) {
			RE_CORE_ERROR("No importer available for asset type: {}", (uint16_t)metadata.Type);

			return nullptr;
		}

		return s_AssetImportFunctions.at(metadata.Type)(metadata);
	}
}
