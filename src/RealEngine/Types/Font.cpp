#include "Font.h"

namespace RealEngine {
	Font::Font(void* fontData, uint32_t size) {
		RenderCommands::SetPixelStoreUnpack(1);

		msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
		msdfgen::FontHandle* font = msdfgen::loadFontData(ft, (msdfgen::byte*)fontData, size);

		InitFont(font);

		msdfgen::destroyFont(font);
		msdfgen::deinitializeFreetype(ft);
	}

	Font::Font(const std::filesystem::path& fontPath) {
		msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
		msdfgen::FontHandle* font = msdfgen::loadFont(ft, fontPath.string().c_str());

		InitFont(font);

		msdfgen::destroyFont(font);
		msdfgen::deinitializeFreetype(ft);
	}

	void Font::Bind(uint32_t slot) {
		m_FontAtlas->Bind(slot);
	}

	void Font::InitFont(msdfgen::FontHandle* font) {
		LoadCharset(font);
		Font::AtlasDimensions atlasDimensions = CreateAtlasPacker();
		ApplyEdgeColoring(); // Makes the glyphs into MSDFs

		ComputeAdvanceCache();
		CreateTextureAtlas(atlasDimensions);
	}

	Font::AtlasDimensions Font::CreateAtlasPacker() {
		msdf_atlas::TightAtlasPacker atlasPacker;
		atlasPacker.setPixelRange(2.0);		// default
		atlasPacker.setMiterLimit(1.0);		// default
		atlasPacker.setSpacing(0);			// default
		atlasPacker.setScale(32.0);			// default
		int remaining = atlasPacker.pack(m_Glyphs.data(), (int)m_Glyphs.size());
		RE_CORE_ASSERT(remaining == 0, "Failed to pack all glyphs into the atlas!");

		Font::AtlasDimensions dims;
		atlasPacker.getDimensions(dims.Width, dims.Height);
		return dims;
	}

	void Font::LoadCharset(msdfgen::FontHandle* font) {
		msdf_atlas::Charset charset;
		for (CharsetRange range : CHARSET_RANGE) {
			for (uint32_t c = range.Begin; c <= range.End; c++) {
				charset.add(c);
			}
		}

		constexpr double fontScale = 1.0;
		m_FontGeometry = msdf_atlas::FontGeometry(&m_Glyphs);
		int glyphsLoaded = m_FontGeometry.loadCharset(font, fontScale, charset);
		RE_CORE_INFO("Loaded {} glyphs from font (out of {})", glyphsLoaded, charset.size());
	}

	void Font::ApplyEdgeColoring() {
		constexpr double DEFAULT_ANGLE_THRESHOLD = 3.0;
		constexpr unsigned long long LCG_MULTIPLIER = 6364136223846793005ull;

		constexpr uint64_t coloringSeed = 0;
		unsigned long long glyphSeed = coloringSeed;
		for (msdf_atlas::GlyphGeometry& glyph : m_Glyphs) {
			glyphSeed *= LCG_MULTIPLIER;
			glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
		}
	}

	void Font::ComputeAdvanceCache() {
		for (uint32_t a = CHARSET_RANGE->Begin; a <= CHARSET_RANGE->End; ++a) {
			const auto* glyphA = m_FontGeometry.getGlyph((char)a);

			for (uint32_t b = CHARSET_RANGE->Begin; b <= CHARSET_RANGE->End; ++b) {
				double advance = 0.0;

				if (glyphA) {
					// Start with base advance
					advance = glyphA->getAdvance();

					// Apply kerning if next glyph exists
					const auto* glyphB = m_FontGeometry.getGlyph((char)b);
					if (glyphB)
						m_FontGeometry.getAdvance(advance, (char)a, (char)b);
				}

				m_AdvanceCache[a - CHARSET_RANGE->Begin][b - CHARSET_RANGE->Begin] = advance;
			}
		}
	}

	void Font::CreateTextureAtlas(const AtlasDimensions dimensions) {
		msdf_atlas::GeneratorAttributes attributes;
		attributes.config.overlapSupport = true;
		attributes.scanlinePass = true;

		msdf_atlas::ImmediateAtlasGenerator<float, 3, msdf_atlas::msdfGenerator, msdf_atlas::BitmapAtlasStorage<uint8_t, 3>> generator(dimensions.Width, dimensions.Height);
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
	}
}