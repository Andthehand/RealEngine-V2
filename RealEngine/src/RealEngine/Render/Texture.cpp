#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

namespace RealEngine {
	Texture2D::Texture2D(const std::filesystem::path& path)
		: m_FilePath(path) {
		RE_PROFILE_FUNCTION();
		
		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
		
		RE_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		switch (channels) {
			case 3: internalFormat = GL_RGB8; dataFormat = GL_RGB; break;
			case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
			default: RE_CORE_ASSERT(false, "Grayscale Images are not supported!");
		}

		// TODO: Only creates 1 mipmap level ?fix?
		// Allocate memory for the texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		// Filters
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Wrapping
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Upload data
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	Texture2D::~Texture2D() {
		RE_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}



	void Texture2D::Bind(uint32_t slot) const {
		RE_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererID);
	}
}
