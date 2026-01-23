#include "Font.h"

namespace RealEngine {
	Font::Font(void* fontData, uint32_t size) {
		RenderCommands::SetPixelStoreUnpack(1);

		msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
		msdfgen::FontHandle* font = msdfgen::loadFontData(ft, (msdfgen::byte*)fontData, size);

		struct CharsetRange {
			uint32_t Begin, End;
		};
		// From imgui_draw.cpp
		constexpr CharsetRange charsetRanges[] = {
			{ 0x0020, 0x00FF }
		};

		msdf_atlas::Charset charset;
		for (CharsetRange range : charsetRanges) {
			for (uint32_t c = range.Begin; c <= range.End; c++) {
				charset.add(c);
			}
		}

		constexpr double fontScale = 1.0;
		m_FontGeometry = msdf_atlas::FontGeometry(&m_Glyphs);
		int glyphsLoaded = m_FontGeometry.loadCharset(font, fontScale, charset);
		RE_CORE_INFO("Loaded {} glyphs from font (out of {})", glyphsLoaded, charset.size());

		double emSize = 32.0;
		msdf_atlas::TightAtlasPacker atlasPacker;
		atlasPacker.setPixelRange(2.0);		// default
		atlasPacker.setMiterLimit(1.0);		// default
		atlasPacker.setSpacing(0);			// default
		atlasPacker.setScale(32.0);			// default
		int remaining = atlasPacker.pack(m_Glyphs.data(), (int)m_Glyphs.size());
		RE_CORE_ASSERT(remaining == 0, "Failed to pack all glyphs into the atlas!");

		int width, height;
		atlasPacker.getDimensions(width, height);
		emSize = atlasPacker.getScale();

#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
		// if MSDF || MTSDF

		uint64_t coloringSeed = 0;
		unsigned long long glyphSeed = coloringSeed;
		for (msdf_atlas::GlyphGeometry& glyph : m_Glyphs) {
			glyphSeed *= LCG_MULTIPLIER;
			glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
		}

		msdf_atlas::GeneratorAttributes attributes;
		attributes.config.overlapSupport = true;
		attributes.scanlinePass = true;

		msdf_atlas::ImmediateAtlasGenerator<float, 3, msdf_atlas::msdfGenerator, msdf_atlas::BitmapAtlasStorage<uint8_t, 3>> generator(width, height);
		generator.setAttributes(attributes);
		generator.setThreadCount(8);
		generator.generate(m_Glyphs.data(), (int)m_Glyphs.size());

		msdfgen::BitmapConstRef<uint8_t, 3> bitmap = (msdfgen::BitmapConstRef<uint8_t, 3>)generator.atlasStorage();

		Texture2DCreateInfo spec{
			.Width = (uint32_t)bitmap.width,
			.Height = (uint32_t)bitmap.height,
			.InternalFormat = TextureDataType::RGB8,
			.DataFormat = TextureFormat::RGB
		};

		m_FontAtlas = Texture2D::Create(spec, (void*)bitmap.pixels);

		msdfgen::destroyFont(font);
		msdfgen::deinitializeFreetype(ft);
	}

	void Font::Bind(uint32_t slot) {
		m_FontAtlas->Bind(slot);
	}
}