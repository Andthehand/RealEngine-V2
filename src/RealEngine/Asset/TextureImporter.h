#pragma once
#include "Asset.h"
#include "AssetMetadata.h"

#include "RealEngine/Render/Texture.h"

namespace RealEngine {
	class TextureImporter {
	public:
		static Ref<Texture2D> ImportTexture2D(const AssetMetadata& metadata);
		//Used for Editor only imports
		static Ref<Texture2D> LoadTexture2D(const std::filesystem::path& path, uint32_t mipmaps = 1);
	};
}