#pragma once
#include "RealEngine/Core/Layer.h"

#define SCALE_OFFSET 0.1f

namespace RealEngine {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		//If the monitor scale changes change the scale of all imgui
		virtual void OnEvent(Event& event) override;
		bool OnWindowRescaled(WindowRescaledEvent& e);

		//This is used for DPI scaling
		void SetScale(float scale);

		void Begin();
		void End();
	};
}