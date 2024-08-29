#pragma once
#include "RealEngine.h"

#include <glm/glm.hpp>

namespace RealEngine {
	class EditorLayer : public Layer {
	public:
		EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnImGui() override;
		virtual void OnEvent(Event& event) override;

	private:
		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	};
}
