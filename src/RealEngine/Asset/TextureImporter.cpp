#include "TextureImporter.h"

namespace RealEngine {
	Ref<Texture2D> TextureImporter::ImportTexture2D(const AssetMetadata& metadata) {
		RE_PROFILE_FUNCTION();

		return Texture2D::Create(metadata.FilePath);
	}
}