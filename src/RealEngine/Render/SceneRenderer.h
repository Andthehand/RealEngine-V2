#pragma once

#include "RealEngine/Scene/Components.h"

#include "RealEngine/Render/VertexArray.h"
#include "RealEngine/Render/Shader.h"

namespace RealEngine {
	// Forward declare because of circular dependency
	class Scene;

	class SceneRenderer {
	public:
		SceneRenderer(Scene* scene);
		SceneRenderer() = delete;

		~SceneRenderer() = default;

		void OnRender(const glm::mat4& cameraProjection);
	private:
		void AddSprite(TransformComponent& transform, const SpriteRendererComponent& sprite);

		void Flush2D();
	private:
		Scene* m_Scene;

		struct SpriteRenderData {
			glm::vec3 Position;
			glm::vec4 Color;
		};

		struct Render2DData {
			Ref<VertexArray> VAO;
			Ref<VertexBuffer> VBO;

			Ref<Shader> SpriteShader;

			static constexpr uint32_t MaxQuadCount = 250;
			static constexpr uint32_t MaxVerticesCount = MaxQuadCount * 4;
			static constexpr uint32_t MaxIndicesCount = MaxQuadCount * 6;

			uint32_t QuadCount = 0;
			SpriteRenderData RenderData[MaxVerticesCount];
			SpriteRenderData* RenderDataHead = RenderData;
		};

		Ref<UniformBuffer> m_CameraBuffer;
		Render2DData m_Render2DData;
	};
}
