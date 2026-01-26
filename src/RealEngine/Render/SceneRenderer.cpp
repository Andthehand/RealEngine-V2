#include "SceneRenderer.h"

#include "RealEngine/Scene/Scene.h"
#include "RealEngine/ImGui/OpenSansRegular.h"

#include <msdf-atlas-gen/msdf-atlas-gen.h>

namespace RealEngine {
	SceneRenderer::SceneRenderer(Scene* scene) : m_Scene(scene) {
		RE_PROFILE_FUNCTION();

		BufferCreateInfo cameraBufferInfo{
			.Size = sizeof(glm::mat4),
			.Usage = BufferUsage::DynamicDraw
		};
		m_CameraBuffer = UniformBuffer::Create(cameraBufferInfo, 0);

		// TODO: Move into SpriteRenderer class
		// Render2DData initialization
		{	
			uint32_t indices[m_Render2DData.MaxIndicesCount];
			uint32_t vertexOffset = 0;
			for (uint32_t i = 0; i < m_Render2DData.MaxIndicesCount; i += 6) {
				indices[i + 0] = vertexOffset + 0;
				indices[i + 1] = vertexOffset + 1;
				indices[i + 2] = vertexOffset + 2;

				indices[i + 3] = vertexOffset + 2;
				indices[i + 4] = vertexOffset + 3;
				indices[i + 5] = vertexOffset + 0;

				vertexOffset += 4;
			}

			Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, m_Render2DData.MaxIndicesCount);

			BufferCreateInfo vboCreateInfo{
				.Size = (uint32_t)sizeof(SpriteRenderData) * 4 * m_Render2DData.MaxVerticesCount,
				.Usage = BufferUsage::DynamicDraw
			};

			m_Render2DData.VBO = VertexBuffer::Create(vboCreateInfo);
			m_Render2DData.VBO->SetLayout(BufferAttributes{
				{ DataType::Float3 }, // Position
				{ DataType::Float4 }, // Color
				{ DataType::Uint },   // TexIndex
			});

			m_Render2DData.VAO = VertexArray::Create();
			m_Render2DData.VAO->SetVertexBuffer(m_Render2DData.VBO);
			m_Render2DData.VAO->SetIndexBuffer(ibo);

			m_Render2DData.SpriteShader = Shader::Create("assets/shaders/sprite.shader");
			Texture2DCreateInfo whiteTextureInfo;
			whiteTextureInfo.Width = 1;
			whiteTextureInfo.Height = 1;
			uint32_t whitePixel = UINT32_MAX;
			m_Render2DData.WhiteTexture = Texture2D::Create(whiteTextureInfo, &whitePixel);

			// Texture slots
			m_Render2DData.TextureSlots[0] = m_Render2DData.WhiteTexture;
			m_Render2DData.TextureSlotIndex = 1;
		}


		// TODO: Move into TextRenderer class
		// Text Rendering initialization
		{
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

			m_TextData.VBO = VertexBuffer::Create(vboCreateInfo);
			m_TextData.VBO->SetLayout(BufferAttributes{
				{ DataType::Float2 }, // Vertex Position
			});

			BufferCreateInfo ssboCreateInfo{
				.Size = sizeof(TextData::TextRenderData),
				.Usage = BufferUsage::DynamicDraw
			};

			m_TextData.VAO = VertexArray::Create();
			m_TextData.VAO->SetVertexBuffer(m_TextData.VBO);

			m_TextData.SSBO = ShaderStorageBuffer::Create(ssboCreateInfo, 1);

			m_TextData.TextShader = Shader::Create("assets/shaders/text.shader");
		}
	}

	void SceneRenderer::OnRender(const glm::mat4& cameraProjection) {
		RE_PROFILE_FUNCTION(); 
		m_CameraBuffer->SetData(&cameraProjection, sizeof(glm::mat4));
		m_CameraBuffer->SetBinding(0);

		{
			RE_PROFILE_SCOPE("SceneRenderer::OnRender - 2D");

			auto entities = m_Scene->GetAllEntitiesWithTransformAndComponents<SpriteRendererComponent>();
			for (const auto entity : entities) {
				auto [transform, sprite] = entities.get<TransformComponent, SpriteRendererComponent>(entity);

				AddSprite(transform, sprite);
			}
			Flush2D();
		}

		{
			RE_PROFILE_SCOPE("SceneRenderer::OnRender - Text");

			auto entities = m_Scene->GetAllEntitiesWithTransformAndComponents<TextRendererComponent>();
			for (const auto entity : entities) {
				auto [transform, text] = entities.get<TransformComponent, TextRendererComponent>(entity);

				if (!text.Font) {
					return;	// Can't render without Font duh!
				}

				m_TextData.RenderData.Transform = transform.GetTransform();
				m_TextData.RenderData.Color = text.Color;

				Ref<Texture2D> fontAtlas = text.Font->GetFontAtlas();
				const auto& fontGeometry = text.Font->GetFontGeometry();
				const auto& metrics = fontGeometry.getMetrics();

				double x = 0.0;
				double fsScale = 1.0 / (metrics.ascenderY - metrics.descenderY);
				double y = 0.0;
				float lineHeightOffset = 0.0f;

				float invW = 1.0f / fontAtlas->GetWidth();
				float invH = 1.0f / fontAtlas->GetHeight();

				// Process each character
				const std::string& textStr = text.Text;
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

					if (m_TextData.RenderDataHead - m_TextData.RenderData.Glyphs >= TextData::MaxBatchLetters) {
						FlushText(text.Font);
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


					m_TextData.RenderDataHead->Position = quadMin;
					m_TextData.RenderDataHead->Size = quadMax - quadMin;

					// Vertex order: TL, BL, TR, BR
					m_TextData.RenderDataHead->UV[0] = glm::vec2(uvMin.x, uvMax.y); // TL
					m_TextData.RenderDataHead->UV[1] = glm::vec2(uvMin.x, uvMin.y); // BL
					m_TextData.RenderDataHead->UV[2] = glm::vec2(uvMax.x, uvMax.y); // TR
					m_TextData.RenderDataHead->UV[3] = glm::vec2(uvMax.x, uvMin.y); // BR
					m_TextData.RenderDataHead++;

					if (i + 1 < textLength) {
						char nextCharacter = textStr[i + 1];

						double advance;

						text.Font->GetAdvance(&advance, character, nextCharacter);
						x += fsScale * advance;
					}
				}
				// Flush text after each entity
				FlushText(text.Font);
			}
		}
	}

	void SceneRenderer::AddSprite(TransformComponent& transform, const SpriteRendererComponent& sprite) {
		RE_PROFILE_FUNCTION();

		if (m_Render2DData.QuadCount >= m_Render2DData.MaxQuadCount ||
			m_Render2DData.TextureSlotIndex >= m_Render2DData.MaxTextureSlots) {
			Flush2D();
		}

		static constexpr glm::vec4 QuadVertexPositions[4] = {
			{-0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f,  0.5f, 0.0f, 1.0f },
			{-0.5f,  0.5f, 0.0f, 1.0f }
		};

		uint32_t textureIndex = 0; // default to white texture
		if (sprite.Texture) {
			for(uint32_t i = 1; i < m_Render2DData.TextureSlotIndex; i++) {
				if (m_Render2DData.TextureSlots[i]->GetRendererID() == sprite.Texture->GetRendererID()) {
					textureIndex = i;
					break;
				}
			}

			if (textureIndex == 0) { // Not found (add into texture list)
				textureIndex = m_Render2DData.TextureSlotIndex;
				m_Render2DData.TextureSlots[m_Render2DData.TextureSlotIndex++] = sprite.Texture;
			}
		}

		for(uint32_t i = 0; i < 4; i++) {
			m_Render2DData.RenderDataHead->Position = transform.GetTransform() * QuadVertexPositions[i];
			m_Render2DData.RenderDataHead->Color = sprite.Color;
			m_Render2DData.RenderDataHead->TexIndex = textureIndex;
			m_Render2DData.RenderDataHead++;
		}

		m_Render2DData.QuadCount++;
	}

	void SceneRenderer::Flush2D() {
		RE_PROFILE_FUNCTION();

		if (m_Render2DData.QuadCount == 0)
			return;
		
		uint32_t dataSize = (uint32_t)((uint8_t*)m_Render2DData.RenderDataHead - (uint8_t*)m_Render2DData.RenderData);
		m_Render2DData.VBO->SetData(m_Render2DData.RenderData, dataSize);

		// Bind all used textures
		for (uint32_t i = 0; i < m_Render2DData.TextureSlotIndex; i++) {
			m_Render2DData.TextureSlots[i]->Bind(i);
		}
		m_Render2DData.SpriteShader->Bind();

		RenderCommands::DrawIndexed(m_Render2DData.VAO, m_Render2DData.QuadCount * 6);

		m_Render2DData.QuadCount = 0;
		m_Render2DData.RenderDataHead = m_Render2DData.RenderData;
		m_Render2DData.TextureSlotIndex = 1; // Reset to only white texture
	}

	void SceneRenderer::FlushText(Ref<Font> font) {
		RE_PROFILE_FUNCTION();

		// Check if there is somethings to draw
		if (m_TextData.RenderDataHead == m_TextData.RenderData.Glyphs)
			return;

		constexpr uint32_t textRenderDataSize = sizeof(TextData::TextRenderData) - (sizeof(GlyphData) * (TextData::MaxBatchLetters));
		uint32_t dataSize = (uint32_t)((uint8_t*)m_TextData.RenderDataHead - (uint8_t*)m_TextData.RenderData.Glyphs);
		m_TextData.SSBO->SetData(&m_TextData.RenderData, dataSize + textRenderDataSize);
		m_TextData.SSBO->SetBinding(1);

		font->Bind();
		m_TextData.TextShader->Bind();

		RenderCommands::DrawArraysInstanced(m_TextData.VAO, 4, (uint32_t)(dataSize / sizeof(GlyphData)));

		m_TextData.RenderDataHead = m_TextData.RenderData.Glyphs;
	}
}
