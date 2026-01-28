#pragma once

#include "RenderStats.h"
#include "Renderer2D.h"
#include "TextRenderer.h"

namespace RealEngine {
	// Forward declare because of circular dependency
	class Scene;

	class SceneRenderer {
	public:
		SceneRenderer(Scene* scene);
		SceneRenderer() = delete;

		~SceneRenderer() = default;

		void OnRender(const glm::mat4& cameraProjection);

		const RenderStats& GetRenderStats() const { return m_RenderStats; }
	private:
		// Creates renderers if there are entities with relevant components in the scene
		void CheckAndCreateRenderers();
	private:
		Scene* m_Scene;

		Ref<UniformBuffer> m_CameraBuffer;

		// Renderers
		// The lifetime of these renderers is currently the lifetime of the application if initialized
		// This is a little weird from the editor POV but from a game POV if you're rendering 2D or text
		// you're probably going to do it again and again so it's better to keep them around
		static inline Ref<Renderer2D> s_Renderer2D;
		static inline Ref<TextRenderer> s_TextRenderer;
		static inline RenderStats m_RenderStats;
	};
}
