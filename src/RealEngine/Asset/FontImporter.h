#pragma once
#include "Asset.h"

#include "RealEngine/Types/Font.h"

namespace RealEngine {
	class FontImporter {
	public:
		static Ref<Font> ImportFont(const AssetMetadata& metadata);
	};
}