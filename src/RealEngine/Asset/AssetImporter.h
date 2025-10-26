#pragma once
#include "Asset.h"
#include "AssetMetadata.h"

namespace RealEngine {
	class AssetImporter {
	public:
		static Ref<Asset> ImportAsset(const AssetMetadata& metadata);
	};
}