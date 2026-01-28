#include "SceneRenderer.h"

#include "RealEngine/Scene/Scene.h"
#include "RealEngine/Scene/Components.h"


namespace RealEngine {
	SceneRenderer::SceneRenderer(Scene* scene) : m_Scene(scene) {
		RE_PROFILE_FUNCTION();

		BufferCreateInfo cameraBufferInfo{
			.Size = sizeof(glm::mat4),
			.Usage = BufferUsage::DynamicDraw
		};
		m_CameraBuffer = UniformBuffer::Create(cameraBufferInfo, 0);
	}

	void SceneRenderer::OnRender(const glm::mat4& cameraProjection) {
		RE_PROFILE_FUNCTION(); 
		CheckAndCreateRenderers();

		m_RenderStats.Reset();
		m_CameraBuffer->SetData(&cameraProjection, sizeof(glm::mat4));
		m_CameraBuffer->SetBinding(0);

		{
			RE_PROFILE_SCOPE("SceneRenderer::OnRender - 2D");

			auto entities = m_Scene->GetAllEntitiesWithTransformAndComponents<SpriteRendererComponent>();
			for (const auto entity : entities) {
				auto [transform, sprite] = entities.get<TransformComponent, SpriteRendererComponent>(entity);

				s_Renderer2D->DrawSprite(transform, sprite);
			}
			if (s_Renderer2D) // TODO: Refactor to avoid this check
				s_Renderer2D->Flush2D();
		}

		{
			RE_PROFILE_SCOPE("SceneRenderer::OnRender - Text");

			auto entities = m_Scene->GetAllEntitiesWithTransformAndComponents<TextRendererComponent>();
			for (const auto entity : entities) {
				auto [transform, text] = entities.get<TransformComponent, TextRendererComponent>(entity);

				s_TextRenderer->RenderText(transform, text); // Flush happens inside after each text entity
			}
		}
	}

	void SceneRenderer::CheckAndCreateRenderers() {
		if (!m_Scene->GetAllEntitiesWithComponent<SpriteRendererComponent>().empty()
			&& !s_Renderer2D) {
			s_Renderer2D = CreateRef<Renderer2D>(&m_RenderStats);
		}

		if (!m_Scene->GetAllEntitiesWithComponent<TextRendererComponent>().empty()
			&& !s_TextRenderer) {
			s_TextRenderer = CreateRef<TextRenderer>(&m_RenderStats);
		}
	}
}
