#pragma once
#include "RealEngine/Core/Layer.h"

namespace RealEngine {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};
}