#pragma once
#include <unordered_set>
#include <string>

#include "RealEngine/Types/StringHash.h"

namespace RealEngine {
	/**
	 * @brief Represents a unique event type, identified via StringHash.
	 */
	class EventType {
	public:
		/**
		 * @brief Constructs an EventType from a hashed string.
		 * @param id Hashed identifier for the event type.
		 */
		explicit EventType(StringHash id) : m_ID(id) {}

		bool operator==(const EventType& other) const { return m_ID == other.m_ID; }
		bool operator!=(const EventType& other) const { return m_ID != other.m_ID; }

		StringHash GetID() const { return m_ID; }

	private:
		StringHash m_ID;
	};

	/**
	 * @brief Macro to define common event type functions.
	 *
	 * Use inside event subclasses to:
	 * - Define a static `GetStaticType()` returning a unique EventType
	 * - Implement `GetEventType()` using the static type
	 * - Implement `GetName()` using the event class name
	 */
	#define EVENT_CLASS_TYPE(type_name) \
		static EventType GetStaticType() { return EventType(StringHash::StaticHash(#type_name)); } \
		virtual EventType GetEventType() const override { return GetStaticType(); } \
		virtual const char* GetName() const override { return #type_name; }

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

