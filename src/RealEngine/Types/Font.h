#pragma once

#include "RealEngine/Render/Texture.h"

#include <msdf-atlas-gen/msdf-atlas-gen.h>

namespace RealEngine {
	class Font {
	public:
		Font(void* fontData, uint32_t size);

		void Bind(uint32_t slot = 0);

		Ref<Texture2D> GetFontAtlas() const { return m_FontAtlas; }
		const msdf_atlas::FontGeometry& GetFontGeometry() const { return m_FontGeometry; }
	private:
		Ref<Texture2D> m_FontAtlas;

		msdf_atlas::FontGeometry m_FontGeometry;
		std::vector<msdf_atlas::GlyphGeometry> m_Glyphs;
	};
}
