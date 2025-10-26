#pragma once
#include "Asset.h"

namespace RealEngine {
	// Used for loading assets
	struct AssetMetadata {
		std::filesystem::path FilePath;
		AssetType Type = AssetType::None;
	};
}
