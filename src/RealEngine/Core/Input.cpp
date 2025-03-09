#include "Input.h"

namespace RealEngine {
	bool Input::IsKeyPressed(KeyCode key) {
		RE_PROFILE_FUNCTION();

		auto window = glfwGetCurrentContext();
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	bool Input::IsMouseButtonPressed(MouseCode button) {
		RE_PROFILE_FUNCTION();

		auto window = glfwGetCurrentContext();
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}
	
	glm::vec2 Input::GetMousePosition() {
		RE_PROFILE_FUNCTION();

		auto window = glfwGetCurrentContext();
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}
	
	float Input::GetMouseX() {
		return GetMousePosition().x;
	}

	float Input::GetMouseY() {
		return GetMousePosition().y;
	}
}