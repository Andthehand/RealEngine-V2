#pragma once
#include "RealEngine/Core/KeyCodes.h"
#include "RealEngine/Core/MouseCodes.h"

namespace RealEngine {
	class Inputs {
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}