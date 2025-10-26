#include "TextureImporter.h"

#include "stb_image.h"

namespace RealEngine {
	Ref<Texture2D> TextureImporter::ImportTexture2D(const AssetMetadata& metadata) {
		return LoadTexture2D(metadata.FilePath);
	}

	Ref<Texture2D> TextureImporter::LoadTexture2D(const std::filesystem::path& path, uint32_t mipmaps) {
		RE_PROFILE_FUNCTION();

		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

		RE_CORE_ASSERT(data, "Failed to load image with path: {}", path);

		Texture2DCreateInfo info;
		info.Width = width;
		info.Height = height;
		switch (channels) {
		case 3:
			info.InternalFormat = TextureDataType::RGB8;
			info.DataFormat = TextureFormat::RGB;
			break;
		case 4:
			info.InternalFormat = TextureDataType::RGBA8;
			info.DataFormat = TextureFormat::RGBA;
			break;
		default:
			RE_CORE_ASSERT(false, "Grayscale Images are not supported!");
		}
		info.MipLevels = mipmaps;

		Ref<Texture2D> texture = Texture2D::Create(info, data);
		stbi_image_free(data);
		return texture;
	}
}