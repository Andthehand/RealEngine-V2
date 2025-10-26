#pragma once
#include "Asset.h"
#include "AssetMetadata.h"

#include "RealEngine/Render/Texture.h"

namespace RealEngine {
	class TextureImporter {
	public:
		static Ref<Texture2D> ImportTexture2D(const AssetMetadata& metadata);
	};
}