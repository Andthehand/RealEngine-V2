#pragma once
#include "RealEngine/Core/KeyCodes.h"
#include "RealEngine/Core/MouseCodes.h"

namespace RealEngine {
	/**
	 * @brief Static interface for querying keyboard and mouse input states.
	 */
	class Input {
	public:
		/**
         * @brief Checks if a specific keyboard key is currently pressed.
         * @param key The key code to check.
         * @return True if the key is pressed or held down, false otherwise.
         */
		static bool IsKeyPressed(KeyCode keycode);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}