#include "Inputs.h"

namespace RealEngine {
	bool Inputs::IsKeyPressed(KeyCode keycode) {
		RE_PROFILE_FUNCTION();

		auto state = glfwGetKey(Application::Get().GetWindow().GetNativeWindow(), keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Inputs::IsMouseButtonPressed(MouseCode button) {
		RE_PROFILE_FUNCTION();

		auto state = glfwGetMouseButton(Application::Get().GetWindow().GetNativeWindow(), button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Inputs::GetMousePosition() {
		RE_PROFILE_FUNCTION();
		
		double xpos, ypos;
		glfwGetCursorPos(Application::Get().GetWindow().GetNativeWindow(), &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Inputs::GetMouseX() {
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Inputs::GetMouseY() {
		auto [x, y] = GetMousePosition();
		return y;
	}
}


