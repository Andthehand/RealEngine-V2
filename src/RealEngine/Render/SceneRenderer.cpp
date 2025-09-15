#include "SceneRenderer.h"

#include "RealEngine/Scene/Scene.h"

namespace RealEngine {
	SceneRenderer::SceneRenderer(Scene* scene) : m_Scene(scene) {
		RE_PROFILE_FUNCTION();

		uint32_t indices[m_Render2DData.MaxIndicesCount];
		for (uint32_t i = 0; i < m_Render2DData.MaxIndicesCount; i += 6) {
			indices[i + 0] = i + 0;
			indices[i + 1] = i + 1;
			indices[i + 2] = i + 2;

			indices[i + 3] = i + 2;
			indices[i + 4] = i + 3;
			indices[i + 5] = i + 0;
		}

		Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, m_Render2DData.MaxIndicesCount);
		m_Render2DData.VBO = VertexBuffer::Create((uint32_t)sizeof(float) * 4 * m_Render2DData.MaxVerticesCount);
		m_Render2DData.VBO->SetLayout(BufferAttributes{
			{ DataType::Float3 }, // Position
			{ DataType::Float4 }  // Color
		});

		m_Render2DData.VAO = VertexArray::Create();
		m_Render2DData.VAO->SetVertexBuffer(m_Render2DData.VBO);
		m_Render2DData.VAO->SetIndexBuffer(ibo);

		m_Render2DData.SpriteShader = Shader::Create("assets/shaders/sprite.shader");
	}

	void SceneRenderer::OnRender() {
		// Get all entities with a SpriteRenderer component
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

	//TODO: Implement texture support
	void SceneRenderer::AddSprite(const TransformComponent& transform, const SpriteRendererComponent& sprite) {
		RE_PROFILE_FUNCTION();

		if(m_Render2DData.QuadCount >= m_Render2DData.MaxQuadCount)
			Flush2D();

		static constexpr glm::vec3 QuadVertexPositions[4] = {
			{-0.5f, -0.5f, 0.0f},
			{ 0.5f, -0.5f, 0.0f},
			{ 0.5f,  0.5f, 0.0f},
			{-0.5f,  0.5f, 0.0f}
		};

		for(uint32_t i = 0; i < 4; i++) {
			m_Render2DData.RenderDataHead->Position = transform.Position + QuadVertexPositions[i];
			m_Render2DData.RenderDataHead->Color = sprite.Color;
			m_Render2DData.RenderDataHead++;
		}

		m_Render2DData.QuadCount++;
	}

	void SceneRenderer::Flush2D() {
		RE_PROFILE_FUNCTION();

		if (m_Render2DData.QuadCount == 0)
			return;

		m_Render2DData.VBO->SetData(m_Render2DData.RenderData, (uint32_t)((uint8_t*)m_Render2DData.RenderDataHead - (uint8_t*)m_Render2DData.RenderData));
		m_Render2DData.SpriteShader->Bind();

		RenderCommands::DrawIndexed(m_Render2DData.VAO, m_Render2DData.QuadCount * 6);

		m_Render2DData.QuadCount = 0;
		m_Render2DData.RenderDataHead = m_Render2DData.RenderData;
	}
}
