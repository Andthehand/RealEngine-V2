#include "Input.h"

namespace RealEngine {
	bool Input::IsKeyPressed(KeyCode keycode) {
		RE_PROFILE_FUNCTION();

		auto state = glfwGetKey(Application::Get().GetWindow().GetNativeWindow(), keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button) {
		RE_PROFILE_FUNCTION();

		auto state = glfwGetMouseButton(Application::Get().GetWindow().GetNativeWindow(), button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition() {
		RE_PROFILE_FUNCTION();
		
		double xpos, ypos;
		glfwGetCursorPos(Application::Get().GetWindow().GetNativeWindow(), &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX() {
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY() {
		auto [x, y] = GetMousePosition();
		return y;
	}
}


