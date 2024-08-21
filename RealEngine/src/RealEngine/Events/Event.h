#pragma once
#include <string>

#include <spdlog/fmt/bundled/core.h>

namespace RealEngine {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		KeyPressed, KeyReleased
	};

	#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return #type; }

	class Event {
	public:
		virtual ~Event() = default;

		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); };

		virtual EventType GetEventType() const = 0;

	public:
		bool Handled = false;
	};

	class EventDispatcher {
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template <typename T, typename F>
		bool Dispatch(const F& func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}

