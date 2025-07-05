#pragma once
#include <filesystem>

#include "RealEngine/Types/PathHash.h"

namespace RealEngine {
	/**
	 * @class Texture2D
	 * @brief Represents a 2D texture loaded from an image file.
	 *
	 * Supports loading textures with 3 (RGB) or 4 (RGBA) channels.
	 * Provides binding functionality for use in shaders.
	 */
	class Texture2D {
	public:
		/**
		 * @brief Constructs a 2D texture from the given file path.
		 * @param path Filesystem path to the texture image file.
		 */
		Texture2D(const std::filesystem::path& path);
		~Texture2D();
		
		void Bind(uint32_t slot = 0) const;

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		/**
		 * @brief Creates a reference-counted Texture2D instance.
		 * @param path Path to the texture image file.
		 * @return Ref-counted pointer to a Texture2D object.
		 */
		static Ref<Texture2D> Create(const std::filesystem::path& path) { return CreateRef<Texture2D>(path); }
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	
		PathHash m_FilePath;
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

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

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
	private:
		struct TextureData {
			int Width = 0;
			int Height = 0;
			int Channels = 0;
		};

		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};
}