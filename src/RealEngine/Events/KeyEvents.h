#pragma once
#include "RealEngine/Events/Event.h"
#include "RealEngine/Core/KeyCodes.h"

namespace RealEngine {
	class KeyPressedEvent : public Event {
	public:
		KeyPressedEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}

		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		const KeyCode m_KeyCode;
	};

	class KeyReleasedEvent : public Event {
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}

		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	private:
		const KeyCode m_KeyCode;
	};
}