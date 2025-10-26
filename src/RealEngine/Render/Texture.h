#pragma once
#include <filesystem>

#include "RealEngine/Asset/Asset.h"

namespace RealEngine {
	enum class TextureFormat : GLenum {
		NONE = 0,

		RED	 =	GL_RED,			// 1 channel  (Red)
		RG   =  GL_RG,			// 2 channels (Red, Green)
		BGR  =	GL_BGR,			// 3 channels (Blue, Green, Red)
		RGB  =  GL_RGB,			// 3 channels (Red, Green, Blue)
		RGBA =  GL_RGBA,		// 4 channels (Red, Green, Blue, Alpha)
		RGBAI = GL_RGBA_INTEGER // 4 channels (Red, Green, Blue, Alpha) as integer values
	};

	enum class TextureDataType : GLenum {
		NONE = 0,

		// --------------------- RED ---------------------
		RED8	 =	 GL_R8,			// 8-bit Red channel
		RED8I	 =   GL_R8I,		// 8-bit signed integer Red channel (GL_R8I)
		RED8UI	 =   GL_R8UI,		// 8-bit unsigned integer Red channel (GL_R8UI)
				 	 
	 	RED16    =   GL_R16,		// 16-bit Red channel 
		RED16I	 =   GL_R16I,		// 16-bit signed integer Red channel (GL_R16I)
		RED16UI  =   GL_R16UI,		// 16-bit unsigned integer Red channel (GL_R16UI)
				 	 
	 	RED32    =   GL_R32F,		// 32-bit Red channel
		RED32I	 =   GL_R32I,		// 32-bit signed integer Red channel (GL_R32I)
		RED32UI  =   GL_R32UI,		// 32-bit unsigned integer Red channel (GL_R32UI)

		// --------------------- RG ----------------------
		RG8		 =	 GL_RG8,		// 8-bit Red and Green channels
		RG8I	 =   GL_RG8I,		// 8-bit signed integer Red and Green channels (GL_RG8I)
		RG8UI	 =   GL_RG8UI,		// 8-bit unsigned integer Red and Green channels (GL_RG8UI)
				 
	  	RG16     =   GL_RG16,		// 16-bit Red and Green channels 
		RG16I	 =   GL_RG16I,		// 16-bit signed integer Red and Green channels (GL_RG16I)
		RG16UI	 =   GL_RG16UI,		// 16-bit unsigned integer Red and Green channels (GL_RG16UI)
				 
	  	RG32     =	 GL_RG32F,		// 32-bit Red and Green channels 
		RG32I	 =   GL_RG32I,		// 32-bit signed integer Red and Green channels (GL_RG32I)
		RG32UI	 =   GL_RG32UI,		// 32-bit unsigned integer Red and Green channels (GL_RG32UI)

		// --------------------- RGB ---------------------
		RGB8	 =	 GL_RGB8,		// 8-bit Red, Green, Blue channels
		RGB8I	 =	 GL_RGB8I,		// 8-bit signed integer Red, Green, Blue channels (GL_RGB8I)
		RGB8UI	 =	 GL_RGB8UI,		// 8-bit unsigned integer Red, Green, Blue channels (GL_RGB8UI)

		RGB16	 =	 GL_RGB16,		// 16-bit Red, Green, Blue channels
		RGB16I	 =   GL_RGB16I,		// 16-bit signed integer Red, Green, Blue channels (GL_RGB16I)
		RGB16UI  =   GL_RGB16UI,	// 16-bit unsigned integer Red, Green, Blue channels (GL_RGB16UI)
		
		RGB32	 =	 GL_RGB32F,		// 32-bit Red, Green, Blue channels (floating point)
		RGB32I	 =   GL_RGB32I,		// 32-bit signed integer Red, Green, Blue channels (GL_RGB32I)
		RGB32UI  =   GL_RGB32UI,	// 32-bit unsigned integer Red, Green, Blue channels (GL_RGB32UI)

		// --------------------- RGBA --------------------
		RGBA8	 =	 GL_RGBA8,		// 8-bit Red, Green, Blue, Alpha channels
		RGBA8I	 =   GL_RGBA8I,		// 8-bit signed integer Red, Green, Blue, Alpha channels (GL_RGBA8I)
		RGBA8UI  =   GL_RGBA8UI,	// 8-bit unsigned integer Red, Green, Blue, Alpha channels (GL_RGBA8UI)

		RGBA16	 =	 GL_RGBA16,		// 16-bit Red, Green, Blue, Alpha channels
		RGBA16I  =   GL_RGBA16I,	// 16-bit signed integer Red, Green, Blue, Alpha channels (GL_RGBA16I)
		RGBA16UI =   GL_RGBA16UI,	// 16-bit unsigned integer Red, Green, Blue, Alpha channels (GL_RGBA16UI)

		RGBA32	 =   GL_RGBA32F,	// 32-bit Red, Green, Blue, Alpha channels (floating point)
		RGBA32I  =   GL_RGBA32I,	// 32-bit signed integer Red, Green, Blue, Alpha channels (GL_RGBA32I)
		RGBA32UI =   GL_RGBA32UI	// 32-bit unsigned integer Red, Green, Blue, Alpha channels (GL_RGBA32UI)
	};

	struct Texture2DCreateInfo {
		uint32_t Width;
		uint32_t Height;
		TextureDataType InternalFormat = TextureDataType::RGBA8;
		TextureFormat DataFormat = TextureFormat::RGBA;

		uint32_t MipLevels = 1;
	};

	/**
	 * @class Texture2D
	 * @brief Represents a 2D texture loaded from an image file.
	 *
	 * Supports loading textures with 3 (RGB) or 4 (RGBA) channels.
	 * Provides binding functionality for use in shaders.
	 */
	class Texture2D : public Asset {
	public:
		/**
		 * @brief Constructs a 2D texture from the given file path.
		 * @param path Filesystem path to the texture image file.
		 */
		 //TODO: Add helper for less duplicated code
		Texture2D(const std::filesystem::path& path, uint32_t mipLevels = 1);
		Texture2D(const Texture2DCreateInfo& info, const void* data = nullptr);
		~Texture2D();
		
		void Bind(uint32_t slot = 0) const;
		void BindImage(uint32_t slot, GLenum access = GL_WRITE_ONLY) const;

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		uint32_t GetRendererID() const { return m_RendererID; }

		static AssetType GetStaticType() { return AssetType::Texture2D; }
		virtual AssetType GetType() const override { return GetStaticType(); }

		/**
		 * @brief Creates a reference-counted Texture2D instance.
		 * @param path Path to the texture image file.
		 * @return Ref-counted pointer to a Texture2D object.
		 */
		static Ref<Texture2D> Create(const std::filesystem::path& path, uint32_t mipLevels = 1) { return CreateRef<Texture2D>(path, mipLevels); }
		static Ref<Texture2D> Create(const Texture2DCreateInfo& info, const void* data = nullptr) { return CreateRef<Texture2D>(info, data); }
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;

		TextureDataType m_InternalFormat;
		TextureFormat m_DataFormat;
	};

	struct Texture2DArrayCreateInfo {
		uint32_t Width;
		uint32_t Height;
		uint32_t NumTextures;
		TextureDataType InternalFormat = TextureDataType::RGBA8;
		TextureFormat DataFormat = TextureFormat::RGBA;

		uint32_t MipLevels = 1;
	};

	/**
	 * @class Texture2DArray
	 * @brief Represents a 2D texture array composed of multiple textures.
	 *
	 * All textures must have the same dimensions and channel count.
	 * Supports mipmapping and provides binding functionality.
	 */
	class Texture2DArray {
	public:
		Texture2DArray(const Texture2DArrayCreateInfo& info, const void** data = nullptr);
		/**
		 * @brief Constructs a texture array from an initializer list of file paths.
		 * @param paths List of texture image paths.
		 * @param mipLevels Number of mipmap levels (default is 1).
		 */
		Texture2DArray(const std::initializer_list<std::filesystem::path> paths, uint32_t mipLevels = 1);
		/**
		 * @brief Constructs a texture array from a vector of file paths.
		 * @param paths Vector of texture image paths.
		 * @param mipLevels Number of mipmap levels (default is 1).
		 */
		Texture2DArray(const std::vector<std::filesystem::path>& paths, uint32_t mipLevels = 1);
		~Texture2DArray();

		void Bind(uint32_t slot = 0) const;

		void SetSubTextureData(const void* data, uint32_t zOffset);

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		uint32_t GetLength() const { return m_Length; }

		static Ref<Texture2DArray> Create(const Texture2DArrayCreateInfo& info, const void** data = nullptr) { return CreateRef<Texture2DArray>(info, data); }
		/**
		 * @brief Creates a reference-counted Texture2DArray instance from an initializer list.
		 * @param paths List of texture image paths.
		 * @param mipLevels Number of mipmap levels.
		 * @return Ref-counted pointer to a Texture2DArray object.
		 */
		static Ref<Texture2DArray> Create(const std::initializer_list<std::filesystem::path> paths, uint32_t mipLevels = 1) { return CreateRef<Texture2DArray>(paths, mipLevels); }
		/**
		 * @brief Creates a reference-counted Texture2DArray instance from a vector.
		 * @param paths Vector of texture image paths.
		 * @param mipLevels Number of mipmap levels.
		 * @return Ref-counted pointer to a Texture2DArray object.
		 */
		static Ref<Texture2DArray> Create(const std::vector<std::filesystem::path>& paths, uint32_t mipLevels = 1) { return CreateRef<Texture2DArray>(paths, mipLevels); }
	private:
		template<class It>
		void LoadTextures(It begin, uint32_t numTextures, uint32_t mipLevels);
		void CreateTextureArray(const void** data, TextureDataType internalFormat, TextureFormat dataFormat, uint32_t numTextures, uint32_t mipLevels);
	private:
		// Used in the LoadTextures function to store texture data
		struct TextureData {
			int Width = 0;
			int Height = 0;
			int Channels = 0;
		};

		uint32_t m_Width, m_Height, m_Length;
		TextureDataType m_InternalFormat;
		TextureFormat m_DataFormat;
		uint32_t m_RendererID;
	};

	struct Texture3DCreateInfo {
		uint32_t Width;
		uint32_t Height;
		uint32_t Depth;
		TextureDataType InternalFormat = TextureDataType::RGBA8;
		TextureFormat DataFormat = TextureFormat::RGBA;

		uint32_t MipLevels = 1;
	};

	class Texture3D {
	public:
		Texture3D(const Texture3DCreateInfo& createInfo, const void* data);
		~Texture3D();
		
		void Bind(uint32_t slot = 0) const;
		void BindImage(uint32_t slot, GLenum access = GL_READ_ONLY) const;

		uint32_t GetWidth() const { return m_Size.x; }
		uint32_t GetHeight() const { return m_Size.y; }
		uint32_t GetDepth() const { return m_Size.z; }
		glm::uvec3 GetSize() const { return m_Size; }

		static Ref<Texture3D> Create(const Texture3DCreateInfo& createInfo, const void* data = nullptr) { return CreateRef<Texture3D>(createInfo, data); }
	private:
		glm::uvec3 m_Size;
		TextureDataType m_InternalFormat;

		uint32_t m_RendererID;
	};
}