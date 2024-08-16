#pragma once
#include "RealEngine/Events/Event.h"
#include "RealEngine/Core/MouseCodes.h"

namespace RealEngine {
	class MouseButtonPressedEvent : public Event {
	public:
		MouseButtonPressedEvent(MouseCode button)
			: m_Button(button) {}

		inline int GetButton() const { return m_Button; }

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	private:
		MouseCode m_Button;
	};

	class MouseButtonReleasedEvent : public Event {
	public:
		MouseButtonReleasedEvent(MouseCode button)
			: m_Button(button) {}

		inline int GetButton() const { return m_Button; }

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	private:
		MouseCode m_Button;
	};

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_X(x), m_Y(y) {}

		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_X << ", " << m_Y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
	private:
		float m_X, m_Y;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
	private:
		float m_XOffset, m_YOffset;
	};
}