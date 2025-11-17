#include "SceneRenderer.h"

#include "RealEngine/Scene/Scene.h"

namespace RealEngine {
	SceneRenderer::SceneRenderer(Scene* scene) : m_Scene(scene) {
		RE_PROFILE_FUNCTION();

		m_CameraBuffer = UniformBuffer::Create(sizeof(glm::mat4), 0);

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
		m_Render2DData.VBO = VertexBuffer::Create((uint32_t)sizeof(SpriteRenderData) * 4 * m_Render2DData.MaxVerticesCount);
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

	void SceneRenderer::OnRender(const glm::mat4& cameraProjection) {
		RE_PROFILE_FUNCTION(); 
		m_CameraBuffer->SetData(&cameraProjection, sizeof(glm::mat4));
		m_CameraBuffer->SetBinding(0);

		{
			RE_PROFILE_SCOPE("SceneRenderer::OnRender - 2D");

			auto entities = m_Scene->GetAllEntitiesWithComponents<TransformComponent, SpriteRendererComponent>();
			for (const auto& entity : entities) {
				auto [transform, sprite] = entities.get<TransformComponent, SpriteRendererComponent>(entity);

				AddSprite(transform, sprite);
			}
			Flush2D();
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
}
