#pragma once
#include "RealEngine/Events/Event.h"

namespace RealEngine {
	class KeyPressedEvent : public Event {
	public:
		KeyPressedEvent(int keycode)
			: m_KeyCode(keycode) {}

		inline int GetKeyCode() const { return m_KeyCode; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		//TODO: Change
		int m_KeyCode;
	};

	class KeyReleasedEvent : public Event {
	public:
		KeyReleasedEvent(int keycode)
			: m_KeyCode(keycode) {}

		inline int GetKeyCode() const { return m_KeyCode; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	private:
		//TODO: Change
		int m_KeyCode;
	};
}