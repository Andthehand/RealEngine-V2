#pragma once
#include "Asset.h"

#include <any>

namespace RealEngine {
	// Used for loading assets
	struct AssetMetadata {
		std::filesystem::path FilePath;
		AssetType Type = AssetType::None;

		std::any CustomMetadata;
	};
}
