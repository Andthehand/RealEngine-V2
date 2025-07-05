#pragma once

namespace RealEngine {
	using MouseCode = uint16_t;

	/**
	 * @enum Mouse
	 * @brief Enumeration of mouse buttons.
	 *
	 * Buttons 0 through 7 correspond to standard mouse buttons.
	 * Aliases provided for left, right, and middle buttons.
	 */
	enum Mouse : MouseCode {
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	};
}