#pragma once
#include <string>

namespace RealEngine {
	/**
	 * @brief Enum of all possible event types.
	 */
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowRescaled,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		KeyPressed, KeyReleased,

		// Editor events
		PannelFolderSelect
	};

	/**
	* @brief Macro to define common event functions in event subclasses.
	*
	* Defines:
	* - static GetStaticType() returning the event type enum
	* - virtual GetEventType() returning static type
	* - virtual GetName() returning event type name as string
	*/
	#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return #type; }

	/**
	 * @brief Base class for all events.
	 */
	class Event {
	public:
		virtual ~Event() = default;

		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); };

		virtual EventType GetEventType() const = 0;

	public:
		bool Handled = false;
	};

	/**
	 * @brief Helper to dispatch events to the appropriate handler based on type.
	 */
	class EventDispatcher {
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		/**
		 * @brief Dispatches the stored event to the given handler if it matches type T.
		 *
		 * Usage example:
		 * ```cpp
		 * EventDispatcher dispatcher(event);
		 * dispatcher.Dispatch<WindowCloseEvent>([](WindowCloseEvent& e) {
		 *     // handle the event
		 *     return true; // mark event as handled
		 * });
		 * ```
		 *
		 * @tparam T The event subclass type to check for.
		 * @tparam F Callable taking T& and returning bool (handled status).
		 * @param func The handler function to call if event is of type T.
		 * @return true if the event was dispatched (type matched), false otherwise.
		 */
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

