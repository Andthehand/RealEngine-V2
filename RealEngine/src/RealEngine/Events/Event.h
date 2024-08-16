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
		Event() = default;
		virtual ~Event() = default;

		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); };

		virtual EventType GetEventType() const = 0;
	};

	//I hate this format overloading so much
	template <typename T>
	struct fmt::formatter<T, std::enable_if_t<std::is_base_of<RealEngine::Event, T>::value, char>> :
		fmt::formatter<std::string> {
		auto format(const RealEngine::Event& e, format_context& ctx) const {
			return fmt::formatter<std::string>::format(e.ToString(), ctx);
		}
	};
}
