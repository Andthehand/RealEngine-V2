#include "SceneRenderer.h"

#include "RealEngine/Scene/Scene.h"
#include "RealEngine/ImGui/OpenSansRegular.h"

#include <ft2build.h>
#include FT_FREETYPE_H

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
				{ DataType::Float2 } // Vertex Position
			});

			BufferCreateInfo ssboCreateInfo{
				.Size = sizeof(TextData::TextRenderData),
				.Usage = BufferUsage::DynamicDraw
			};

			m_TextData.VAO = VertexArray::Create();
			m_TextData.VAO->SetVertexBuffer(m_TextData.VBO);

			m_TextData.SSBO = ShaderStorageBuffer::Create(ssboCreateInfo, 1);

			m_TextData.TextShader = Shader::Create("assets/shaders/text.shader");

			// Load FreeType
			FT_Library ft;
			if (FT_Init_FreeType(&ft)) {
				RE_CORE_ASSERT(false, "Could not init FreeType Library");
			}

			FT_Face face;
			if (FT_New_Memory_Face(ft, Utils::OpenSans_Regular, sizeof(Utils::OpenSans_Regular), 0, &face)) {
				RE_CORE_ASSERT(false, "Failed to load font from memory!");
			}

			FT_Set_Pixel_Sizes(face, m_TextData.FontSize, m_TextData.FontSize);
			m_TextData.Line_Spacing = face->size->metrics.height >> 6;

			RenderCommands::SetPixelStoreUnpack(1);

			Texture2DArrayCreateInfo fontAtlasInfo{
				.Width = m_TextData.FontSize,
				.Height = m_TextData.FontSize,
				.NumTextures = m_TextData.NumCharecters,
				.InternalFormat = TextureDataType::RED8,
				.DataFormat = TextureFormat::RED,
			};

			m_TextData.FontAtlas = Texture2DArray::Create(fontAtlasInfo);

			for (uint32_t i = m_TextData.StartCharecterIndex; i < m_TextData.EndCharecterIndex; i++) {
				if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
					RE_CORE_ERROR("Failed to load Glyph for char code {}", i);
					continue;
				}

				uint32_t width = face->glyph->bitmap.width;
				uint32_t height = face->glyph->bitmap.rows;
				uint32_t textureOffset = i - m_TextData.StartCharecterIndex;
				if (width != 0 && width <= m_TextData.FontSize && 
					height != 0 && height <= m_TextData.FontSize) {
					m_TextData.FontAtlas->SetSubTextureData(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, textureOffset);
				}
				else {
					RE_CORE_WARN("Glyph for char code {} has invalid size: {}x{}", i, width, height);
				}

				// Now store character for later use
				Character character{
					.TextureID = textureOffset,
					.Size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					.Bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					.Advance = face->glyph->advance.x
				};
				m_TextData.Characters.insert({ (char)i, character });
			}
		
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
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

				if (text.Color != m_TextData.RenderData.textColor) {
					FlushText();
				}

				m_TextData.RenderData.textColor = text.Color;
				
				const glm::vec3& translation = transform.GetTransation();
				float x = translation.x;
				float y = translation.y;

				const glm::vec3& scale = transform.GetScale();
				float scaleX = scale.x;
				float scaleY = scale.y;

				float originalXPos = translation.x;

				std::string::const_iterator c;
				for (c = text.Text.begin(); c != text.Text.end(); c++) {
					const Character& ch = m_TextData.Characters[*c];

					if (*c == '\n') {
						x = originalXPos;
						y -= m_TextData.Line_Spacing * scaleY;
					}
					else if (*c == ' ') {
						x += (ch.Advance >> 6) * scaleX;
					}
					else {
						// Check if we exceed max letters
						if (m_TextData.RenderDataHead - m_TextData.RenderData.glyphs >= TextData::MaxBatchLetters) {
							FlushText();
						}

						float xpos = x + ch.Bearing.x * scaleX;
						float ypos = y - (m_TextData.FontSize - ch.Bearing.y) * scaleY;

						m_TextData.RenderDataHead->transform = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, translation.z)) *
																glm::scale(glm::mat4(1.0f), glm::vec3(m_TextData.FontSize * scaleX, m_TextData.FontSize * scaleY, 0));
						m_TextData.RenderDataHead->letter = ch.TextureID;
						m_TextData.RenderDataHead++;

						x += (ch.Advance >> 6) * scaleX;
					}
				}
			}
			FlushText();
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

	void SceneRenderer::FlushText() {
		RE_PROFILE_FUNCTION();

		// Check if there is somethings to draw
		if (m_TextData.RenderDataHead == m_TextData.RenderData.glyphs)
			return;

		uint32_t dataSize = (uint32_t)((uint8_t*)m_TextData.RenderDataHead - (uint8_t*)m_TextData.RenderData.glyphs);
		m_TextData.SSBO->SetData(&m_TextData.RenderData, dataSize + sizeof(glm::vec3));
		m_TextData.SSBO->SetBinding(1);

		m_TextData.FontAtlas->Bind();
		m_TextData.TextShader->Bind();

		RenderCommands::DrawArraysInstanced(m_TextData.VAO, 4, (uint32_t)(dataSize / sizeof(GlyphData)));

		m_TextData.RenderDataHead = m_TextData.RenderData.glyphs;
	}
}
