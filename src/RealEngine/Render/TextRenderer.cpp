#include "TextRenderer.h"

#include "RealEngine/Render/Texture.h"

#include <msdf-atlas-gen/msdf-atlas-gen.h>

namespace RealEngine {
	TextRenderer::TextRenderer(RenderStats* stats) 
		: m_Stats(stats) {
		constexpr glm::vec2 vertexData[] = {
			{ 0.0f, 1.0f },
			{ 0.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f }
		};
		BufferCreateInfo vboCreateInfo{
			.Size = sizeof(vertexData),
			.Data = vertexData,
			.Usage = BufferUsage::StaticDraw
		};

		m_VBO = VertexBuffer::Create(vboCreateInfo);
		m_VBO->SetLayout(BufferAttributes{
			{ DataType::Float2 }, // Vertex Position
		});

		m_VAO = VertexArray::Create();
		m_VAO->SetVertexBuffer(m_VBO);

		// We are using instance rendering so this passes in all needed data per-instance
		BufferCreateInfo ssboCreateInfo{
			.Size = sizeof(TextRenderData),
			.Usage = BufferUsage::DynamicDraw
		};
		m_SSBO = ShaderStorageBuffer::Create(ssboCreateInfo, 1);

		m_TextShader = Shader::Create("assets/shaders/text.shader");
	}

	void TextRenderer::RenderText(TransformComponent& transformComponent, const TextRendererComponent& textComponent) {
		if (!textComponent.TextFont) {
			return;	// Can't render without Font duh!
		}

		m_RenderData.Transform = transformComponent.GetTransform();
		m_RenderData.Color = textComponent.Color;

		Ref<Texture2D> fontAtlas = textComponent.TextFont->GetFontAtlas();
		const auto& fontGeometry = textComponent.TextFont->GetFontGeometry();
		const auto& metrics = fontGeometry.getMetrics();

		double x = 0.0;
		double fsScale = 1.0 / (metrics.ascenderY - metrics.descenderY);
		double y = 0.0;
		float lineHeightOffset = 0.0f;

		float invW = 1.0f / fontAtlas->GetWidth();
		float invH = 1.0f / fontAtlas->GetHeight();

		// Process each character
		const std::string& textStr = textComponent.Text;
		const size_t textLength = textStr.length();
		for (size_t i = 0; i < textLength; ++i) {
			char character = textStr[i];

			if (character == '\r')
				continue;

			if (character == '\n') {
				x = 0;
				y -= fsScale * metrics.lineHeight + lineHeightOffset;
				continue;
			}

			if (m_RenderDataHead - m_RenderData.Glyphs >= MAX_BATCH_LETTERS) {
				FlushText(textComponent.TextFont);
			}

			auto glyph = fontGeometry.getGlyph(character);
			if (!glyph)
				glyph = fontGeometry.getGlyph('?');
			if (!glyph) {
				RE_CORE_ASSERT(false, "Failed to find glyph for character and fallback '?'");
				return;
			}

			if (character == '\t')
				glyph = fontGeometry.getGlyph(' ');

			double al, ab, ar, at;
			glyph->getQuadAtlasBounds(al, ab, ar, at);
			glm::vec2 texCoordMin((float)al, (float)ab);
			glm::vec2 texCoordMax((float)ar, (float)at);

			double pl, pb, pr, pt;
			glyph->getQuadPlaneBounds(pl, pb, pr, pt);
			glm::vec2 quadMin((float)pl, (float)pb);
			glm::vec2 quadMax((float)pr, (float)pt);

			quadMin *= fsScale, quadMax *= fsScale;
			quadMin += glm::vec2(x, y);
			quadMax += glm::vec2(x, y);

			// Keep msdf-atlas-gen coordinates as-is
			glm::vec2 uvMin(
				(float)al * invW,
				(float)ab * invH
			);

			glm::vec2 uvMax(
				(float)ar * invW,
				(float)at * invH
			);


			m_RenderDataHead->Position = quadMin;
			m_RenderDataHead->Size = quadMax - quadMin;

			// Vertex order: TL, BL, TR, BR
			m_RenderDataHead->UV[0] = glm::vec2(uvMin.x, uvMax.y); // TL
			m_RenderDataHead->UV[1] = glm::vec2(uvMin.x, uvMin.y); // BL
			m_RenderDataHead->UV[2] = glm::vec2(uvMax.x, uvMax.y); // TR
			m_RenderDataHead->UV[3] = glm::vec2(uvMax.x, uvMin.y); // BR
			m_RenderDataHead++;

			if (i + 1 < textLength) {
				char nextCharacter = textStr[i + 1];

				double advance;

				textComponent.TextFont->GetAdvance(&advance, character, nextCharacter);
				x += fsScale * advance;
			}
		}
		// Flush text after each text entity
		FlushText(textComponent.TextFont);
	}

	void TextRenderer::FlushText(Ref<Font> font) {
		RE_PROFILE_FUNCTION();

		// Check if there is somethings to draw
		if (m_RenderDataHead == m_RenderData.Glyphs)
			return;

		UpdateRenderStats();

		// Get TextRenderData size without the Glyphs array
		constexpr uint32_t textRenderDataSize = sizeof(TextRenderData) - (sizeof(GlyphData) * (MAX_BATCH_LETTERS));
		uint32_t dataSize = (uint32_t)((uint8_t*)m_RenderDataHead - (uint8_t*)m_RenderData.Glyphs);
		m_SSBO->SetData(&m_RenderData, dataSize + textRenderDataSize);
		m_SSBO->SetBinding(1);

		font->Bind();
		m_TextShader->Bind();

		RenderCommands::DrawArraysInstanced(m_VAO, 4, (uint32_t)(dataSize / sizeof(GlyphData)));

		m_RenderDataHead = m_RenderData.Glyphs;
	}

	void TextRenderer::UpdateRenderStats() {
		m_Stats->DrawCalls++;

		m_Stats->Text.DrawCalls++;
		uint32_t dataSize = (uint32_t)((uint8_t*)m_RenderDataHead - (uint8_t*)m_RenderData.Glyphs);
		m_Stats->Text.GlyphCount += (uint32_t)(dataSize / sizeof(GlyphData));
	}
}
