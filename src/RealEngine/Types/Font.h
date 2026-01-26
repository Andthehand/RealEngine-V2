#pragma once
#include "RealEngine/Render/Texture.h"

#include <msdf-atlas-gen/msdf-atlas-gen.h>

#include <filesystem>

namespace RealEngine {
	class Font : public Asset {
	public:
		Font(void* fontData, uint32_t size);
		Font(const std::filesystem::path& fontPath);

		void Bind(uint32_t slot = 0);

		void GetAdvance(double* advace, char char1, char nextChar) const {
			*advace = m_AdvanceCache[char1 - CHARSET_RANGE->Begin][nextChar - CHARSET_RANGE->Begin];
		}

		Ref<Texture2D> GetFontAtlas() const { return m_FontAtlas; }
		const msdf_atlas::FontGeometry& GetFontGeometry() const { return m_FontGeometry; }

		static AssetType GetStaticType() { return AssetType::Font; }
		virtual AssetType GetType() const override { return GetStaticType(); }
	private:
		struct AtlasDimensions {
			int Width;
			int Height;
		};

		void InitFont(msdfgen::FontHandle* font);

		AtlasDimensions CreateAtlasPacker();
		void LoadCharset(msdfgen::FontHandle* font);
		void ApplyEdgeColoring();
		void ComputeAdvanceCache();

		void CreateTextureAtlas(const AtlasDimensions dimensions);
	private:
		Ref<Texture2D> m_FontAtlas;


		struct CharsetRange {
			uint32_t Begin, End;
		};
		// From imgui_draw.cpp
		static constexpr CharsetRange CHARSET_RANGE[] = {
			{ 0x000A, 0x00FF }
		};
		static constexpr uint32_t CHARSET_COUNT = CHARSET_RANGE->End - CHARSET_RANGE->Begin + 1;

		double m_AdvanceCache[CHARSET_COUNT][CHARSET_COUNT];

		msdf_atlas::FontGeometry m_FontGeometry;
		std::vector<msdf_atlas::GlyphGeometry> m_Glyphs;
	};
}
