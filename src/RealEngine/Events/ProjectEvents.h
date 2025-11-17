#pragma once

#include "RealEngine/Events/Event.h"

namespace RealEngine {
	class SceneChangedEvent : public Event {
		public:
		SceneChangedEvent() = default;

		virtual std::string ToString() const override {
			return "SceneChangedEvent";
		}

		EVENT_CLASS_TYPE(SceneChanged)
	};
}
