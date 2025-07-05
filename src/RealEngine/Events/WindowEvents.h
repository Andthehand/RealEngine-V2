#pragma once
#include "RealEngine/Events/Event.h"

namespace RealEngine {
	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		/** @return String representation of the event for logging/debugging. */
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowRescaledEvent : public Event {
	public:
		WindowRescaledEvent(float scale)
			: m_Scale(scale) {}

		inline float GetScale() const { return m_Scale; }

		/** @return String representation of the event for logging/debugging. */
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowRescaledEvent: " << m_Scale;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowRescaled)
	private:
		float m_Scale;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
	};
}