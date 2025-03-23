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
		
		RE_CORE_ASSERT(data, "Failed to load image with path: {}", path.string());
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


	Texture2DArray::Texture2DArray(const std::initializer_list<std::filesystem::path> paths, uint32_t mipLevels) {
		LoadTextures(paths.begin(), (uint32_t)paths.size(), mipLevels);
	}

	Texture2DArray::Texture2DArray(const std::vector<std::filesystem::path>& paths, uint32_t mipLevels) {
		LoadTextures(paths.begin(), (uint32_t)paths.size(), mipLevels);
	}

	Texture2DArray::~Texture2DArray() {
		RE_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

	template<class It>
	void Texture2DArray::LoadTextures(It begin, uint32_t numTextures, uint32_t mipLevels) {
		RE_PROFILE_FUNCTION();

		RE_CORE_ASSERT(numTextures != 0, "Can't make Texuture without any textures");
		TextureData* textureData = new TextureData[numTextures];
		stbi_uc** data = new stbi_uc * [numTextures];

		int checkChannel = -1;
		stbi_set_flip_vertically_on_load(1);
		//Load all of the images into memory
		for (uint32_t i = 0; i < numTextures; i++) {
			const std::filesystem::path& path = *(begin + i);

			data[i] = stbi_load(path.string().c_str(), &textureData[i].Width, &textureData[i].Height, &textureData[i].Channels, 0);
			RE_CORE_ASSERT(data, "Failed to load image with path: {}", path.string());

			//Set data only on the first texture upload
			if (checkChannel == -1) {
				checkChannel = textureData[i].Channels;
				m_Width = textureData[i].Width;
				m_Height = textureData[i].Height;
			}

			//Make sure the channels, width, and height are the same
			RE_CORE_ASSERT(checkChannel == textureData[i].Channels &&
				m_Width == (uint32_t)textureData[i].Width &&
				m_Height == (uint32_t)textureData[i].Height, 
				"Channel, Width, or height do not match while creating TextureArray");
		}

		GLenum internalFormat = 0, dataFormat = 0;
		switch (checkChannel) {
			case 3: internalFormat = GL_RGB8; dataFormat = GL_RGB; break;
			case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
			default: RE_CORE_ASSERT(false, "Grayscale Images are not supported!");
		}

		//Create TextureArray and allocate memory
		glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_RendererID);
		glTextureStorage3D(m_RendererID, mipLevels, internalFormat, m_Width, m_Height, numTextures);
		//Upload the images to the GPU
		for (uint32_t i = 0; i < numTextures; i++) {
			glTextureSubImage3D(m_RendererID, 0, 0, 0, i, m_Width, m_Height, 1, dataFormat, GL_UNSIGNED_BYTE, data[i]);
		}
		glGenerateTextureMipmap(m_RendererID);

		GLfloat max_aniso;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &max_aniso);
		glTextureParameterf(m_RendererID, GL_TEXTURE_MAX_ANISOTROPY, max_aniso);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Delete rescources
		for (uint32_t i = 0; i < numTextures; i++) {
			stbi_image_free(data[i]);
		}
		delete[] data;
		delete[] textureData;
	}

	void Texture2DArray::Bind(uint32_t slot) const {
		RE_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
	}
}
