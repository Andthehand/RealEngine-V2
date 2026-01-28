#include "Renderer2D.h"

namespace RealEngine {
	Renderer2D::Renderer2D(RenderStats* stats) 
		: m_Stats(stats) {
		RE_PROFILE_FUNCTION();

		uint32_t indices[MAX_INDICES_COUNT];
		uint32_t vertexOffset = 0;
		for (uint32_t i = 0; i < MAX_INDICES_COUNT; i += 6) {
			indices[i + 0] = vertexOffset + 0;
			indices[i + 1] = vertexOffset + 1;
			indices[i + 2] = vertexOffset + 2;

			indices[i + 3] = vertexOffset + 2;
			indices[i + 4] = vertexOffset + 3;
			indices[i + 5] = vertexOffset + 0;

			vertexOffset += 4;
		}

		Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, MAX_INDICES_COUNT);

		BufferCreateInfo vboCreateInfo{
			.Size = (uint32_t)sizeof(SpriteRenderData) * 4 * MAX_VERTICES_COUNT,
			.Usage = BufferUsage::DynamicDraw
		};

		m_VBO = VertexBuffer::Create(vboCreateInfo);
		m_VBO->SetLayout(BufferAttributes{
			{ DataType::Float3 }, // Position
			{ DataType::Float4 }, // Color
			{ DataType::Uint },   // TexIndex
			});

		m_VAO = VertexArray::Create();
		m_VAO->SetVertexBuffer(m_VBO);
		m_VAO->SetIndexBuffer(ibo);

		m_SpriteShader = Shader::Create("assets/shaders/sprite.shader");
		Texture2DCreateInfo whiteTextureInfo;
		whiteTextureInfo.Width = 1;
		whiteTextureInfo.Height = 1;
		uint32_t whitePixel = UINT32_MAX;
		m_WhiteTexture = Texture2D::Create(whiteTextureInfo, &whitePixel);

		// Texture slots
		m_TextureSlots[0] = m_WhiteTexture;
		m_TextureSlotIndex = 1;
	}

	void Renderer2D::DrawSprite(TransformComponent& transformComponent, const SpriteRendererComponent& spriteComponent) {
		RE_PROFILE_FUNCTION();

		if (m_QuadCount >= MAX_QUAD_COUNT ||
			m_TextureSlotIndex >= MAX_TEXTURE_SLOTS) {
			Flush2D();
		}

		static constexpr glm::vec4 QuadVertexPositions[4] = {
			{-0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f,  0.5f, 0.0f, 1.0f },
			{-0.5f,  0.5f, 0.0f, 1.0f }
		};

		uint32_t textureIndex = 0; // default to white texture
		if (spriteComponent.Texture) {
			for (uint32_t i = 1; i < m_TextureSlotIndex; i++) {
				if (m_TextureSlots[i]->GetRendererID() == spriteComponent.Texture->GetRendererID()) {
					textureIndex = i;
					break;
				}
			}

			if (textureIndex == 0) { // Not found (add into texture list)
				textureIndex = m_TextureSlotIndex;
				m_TextureSlots[m_TextureSlotIndex++] = spriteComponent.Texture;
			}
		}

		for (uint32_t i = 0; i < 4; i++) {
			m_RenderDataHead->Position = transformComponent.GetTransform() * QuadVertexPositions[i];
			m_RenderDataHead->Color = spriteComponent.Color;
			m_RenderDataHead->TexIndex = textureIndex;
			m_RenderDataHead++;
		}

		m_QuadCount++;
	}

	void Renderer2D::Flush2D() {
		RE_PROFILE_FUNCTION();

		if (m_QuadCount == 0)
			return;

		UpdateRenderStats();

		uint32_t dataSize = (uint32_t)((uint8_t*)m_RenderDataHead - (uint8_t*)m_RenderData);
		m_VBO->SetData(m_RenderData, dataSize);

		// Bind all used textures
		for (uint32_t i = 0; i < m_TextureSlotIndex; i++) {
			m_TextureSlots[i]->Bind(i);
		}
		m_SpriteShader->Bind();

		RenderCommands::DrawIndexed(m_VAO, m_QuadCount * 6);

		m_QuadCount = 0;
		m_RenderDataHead = m_RenderData;
		m_TextureSlotIndex = 1; // Reset to only white texture
	}

	void Renderer2D::UpdateRenderStats() {
		m_Stats->DrawCalls++;

		m_Stats->Sprites.DrawCalls++;
		m_Stats->Sprites.QuadCount += m_QuadCount;
		m_Stats->Sprites.TextureBinds += m_TextureSlotIndex - 1; // -1 to account for white texture
	}
}