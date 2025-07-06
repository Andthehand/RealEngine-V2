#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

namespace RealEngine {
	namespace Utils {
		GLenum GetGLType(TextureDataType type) {
			switch (type) {
				case TextureDataType::RED8:    
				case TextureDataType::RGB8:    
				case TextureDataType::RGBA8:   
					return GL_UNSIGNED_BYTE; // 8-bit unsigned byte formats
				case TextureDataType::RED8I:
				case TextureDataType::RGB8I:
				case TextureDataType::RGBA8I:
					return GL_BYTE; // 8-bit signed integer formats
				case TextureDataType::RED8UI:
				case TextureDataType::RGB8UI:
				case TextureDataType::RGBA8UI:
					return GL_UNSIGNED_BYTE; // 8-bit unsigned integer formats
				case TextureDataType::RED16:
				case TextureDataType::RGB16:
				case TextureDataType::RGBA16:
					return GL_UNSIGNED_SHORT; // 16-bit unsigned short formats
				case TextureDataType::RED16I:
				case TextureDataType::RGB16I:
				case TextureDataType::RGBA16I:
					return GL_SHORT; // 16-bit signed integer formats
				case TextureDataType::RED16UI:
				case TextureDataType::RGB16UI:
				case TextureDataType::RGBA16UI:
					return GL_UNSIGNED_SHORT; // 16-bit unsigned integer formats
				case TextureDataType::RED32:
				case TextureDataType::RGB32:
				case TextureDataType::RGBA32:
					return GL_FLOAT; // 32-bit floating point formats
				case TextureDataType::RED32I:
				case TextureDataType::RGB32I:
				case TextureDataType::RGBA32I:
					return GL_INT; // 32-bit signed integer formats
				case TextureDataType::RED32UI:
				case TextureDataType::RGB32UI:
				case TextureDataType::RGBA32UI:
					return GL_UNSIGNED_INT; // 32-bit unsigned integer formats
				default: 
					RE_CORE_ASSERT(false, "Unsupported TextureDataType"); 
					return 0;
			}
		}
	}

	Texture2D::Texture2D(const std::filesystem::path& path) {
		RE_PROFILE_FUNCTION();
		
		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
		
		RE_CORE_ASSERT(data, "Failed to load image with path: {}", path);
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

	Texture2DArray::Texture2DArray(const Texture2DArrayCreateInfo& info, const void** data)
		: m_Width(info.Width), m_Length(info.Height) {
		RE_PROFILE_FUNCTION();

		RE_CORE_ASSERT(info.NumTextures > 0, "Cannot create TextureArray with no textures");
		RE_CORE_ASSERT(m_Width > 0 && m_Length > 0, "Width and Height must be greater than 0 for TextureArray");
		RE_CORE_ASSERT(info.MipLevels > 0, "MipLevels must be greater than 0 for TextureArray");

		// Create an empty texture array with no data, will be filled later if needed
		CreateTextureArray(data, info.InternalFormat, info.DataFormat, info.NumTextures, info.MipLevels);
	}

	Texture2DArray::Texture2DArray(const std::initializer_list<std::filesystem::path> paths, uint32_t mipLevels) {
		RE_CORE_ASSERT(mipLevels > 0, "MipLevels must be greater than 0 for TextureArray");

		LoadTextures(paths.begin(), (uint32_t)paths.size(), mipLevels);
	}

	Texture2DArray::Texture2DArray(const std::vector<std::filesystem::path>& paths, uint32_t mipLevels) {
		RE_CORE_ASSERT(mipLevels > 0, "MipLevels must be greater than 0 for TextureArray");

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
			RE_CORE_ASSERT(data == NULL, "Failed to load image with path: {}", path);

			//Set data only on the first texture upload
			if (checkChannel == -1) {
				checkChannel = textureData[i].Channels;
				m_Width = textureData[i].Width;
				m_Length = textureData[i].Height;
			}

			//Make sure the channels, width, and height are the same
			RE_CORE_ASSERT(checkChannel == textureData[i].Channels &&
				m_Width == (uint32_t)textureData[i].Width &&
				m_Length == (uint32_t)textureData[i].Height, 
				"Channel, Width, or height do not match while creating TextureArray");
		}

		TextureDataType internalFormat = TextureDataType::NONE;
		TextureFormat dataFormat = TextureFormat::NONE;
		switch (checkChannel) {
			case 3: internalFormat = TextureDataType::RGB8;  dataFormat = TextureFormat::RGB; break;
			case 4: internalFormat = TextureDataType::RGBA8; dataFormat = TextureFormat::RGBA; break;
			default: RE_CORE_ASSERT(false, "Grayscale Images are not supported!");
		}

		CreateTextureArray((const void**)data, internalFormat, dataFormat, numTextures, mipLevels);

		//Delete rescources
		for (uint32_t i = 0; i < numTextures; i++) {
			stbi_image_free(data[i]);
		}
		delete[] data;
		delete[] textureData;
	}

	void Texture2DArray::CreateTextureArray(const void** data, TextureDataType internalFormat, TextureFormat dataFormat, uint32_t numTextures, uint32_t mipLevels) {
		RE_PROFILE_FUNCTION();
		RE_CORE_ASSERT(numTextures > 0, "Cannot create TextureArray with no textures");

		m_Height = numTextures; // Or Z direction
		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		//Create TextureArray and allocate memory
		glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_RendererID);
		glTextureStorage3D(m_RendererID, mipLevels, (GLenum)internalFormat, m_Width, m_Length, numTextures);
		
		//Upload the images to the GPU
		if (data != nullptr) {
			for (uint32_t i = 0; i < numTextures; i++) {
				glTextureSubImage3D(m_RendererID, 0, 0, 0, i, m_Width, m_Length, 1, (GLenum)dataFormat, GL_UNSIGNED_BYTE, data[i]);
			}
		}
		
		glGenerateTextureMipmap(m_RendererID);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void Texture2DArray::Bind(uint32_t slot) const {
		RE_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
	}

	void Texture2DArray::SetSubTextureData(const void* data, uint32_t zOffset) {
		RE_PROFILE_FUNCTION();

		RE_CORE_ASSERT(zOffset < m_Height, "zOffset out of bounds for Texture2DArray. Must be less than the number of textures in the array");
		// Set the data for a specific slice in the texture array
		// Has to be GL_RGBA because OpenGL has aninitial default pixel alignment of 4
		// https://stackoverflow.com/questions/61429347/gltexturesubimage3d-misbehaving-with-small-image-input
		glTextureSubImage3D(m_RendererID, 0, 0, 0, zOffset, m_Width, m_Length, 1, GL_RGBA, Utils::GetGLType(m_InternalFormat), data);
	}
}
