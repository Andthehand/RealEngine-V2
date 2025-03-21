#pragma once
#include <filesystem>

#include "RealEngine/Types/PathHash.h"

namespace RealEngine {
	class Texture2D {
	public:
		Texture2D(const std::filesystem::path& path);
		~Texture2D();
		
		void Bind(uint32_t slot = 0) const;

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		static Ref<Texture2D> Create(const std::filesystem::path& path) { return CreateRef<Texture2D>(path); }
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	
		PathHash m_FilePath;
	};

	class Texture2DArray {
	public:
		Texture2DArray(const std::initializer_list<std::filesystem::path> paths, uint32_t mipLevels = 1);
		Texture2DArray(const std::vector<std::filesystem::path>& paths, uint32_t mipLevels = 1);
		~Texture2DArray();

		void Bind(uint32_t slot = 0) const;

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		static Ref<Texture2DArray> Create(const std::initializer_list<std::filesystem::path> paths, uint32_t mipLevels = 1) { return CreateRef<Texture2DArray>(paths, mipLevels); }
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