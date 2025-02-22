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
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	
		PathHash m_FilePath;
	};
}