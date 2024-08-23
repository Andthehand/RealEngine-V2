#pragma once
#include "RealEngine.h"

namespace RealEngine {
	class EditorLayer : public Layer {
	public:
		EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(const Event& event) override;
	};
}
