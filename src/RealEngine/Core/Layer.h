#pragma once
#include "RealEngine/Events/Event.h"

namespace RealEngine {

	/**
	 * @brief Base class for application layers.
	 *
	 * Layers represent modular pieces of functionality or rendering,
	 * and receive events, update calls, and ImGui rendering callbacks.
	 */
	class Layer {
	public:
		/**
		 * @brief Constructs a layer with an optional debug name.
		 * @param name Name shown in debugging and profiling tools.
		 */
		Layer(const std::string& name = "Default Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		/**
		 * @brief Called once per frame with the time delta since last update.
		 * @param deltaTime Time elapsed since last frame (in seconds).
		 */
		virtual void OnUpdate(const float deltaTime) {}
		virtual void OnImGui() {}
		virtual void OnEvent(Event& event) {}

		/** @return The debug name of the layer. */
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

} // namespace RealEngine