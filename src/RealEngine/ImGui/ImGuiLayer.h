#pragma once
#include "RealEngine/Core/Layer.h"

namespace RealEngine {
	/**
	 * @brief A layer for integrating Dear ImGui with the engine.
	 *
	 * Handles ImGui context setup, frame lifecycle, DPI scaling, and shutdown.
	 */
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		/**
		 * @brief Applies content scaling to UI elements and fonts.
		 * Used for DPI awareness and high-DPI displays.
		 */
		void SetScale();

		/** @brief Begins a new ImGui frame (must be called before UI rendering). */
		void Begin();
		/** @brief Ends the current ImGui frame and renders the draw data. */
		void End();
	};
}