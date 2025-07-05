#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

#include "RealEngine/Events/Event.h"

namespace RealEngine {
	/**
	 * @brief Window abstraction wrapping GLFW window and input events.
	 *
	 * Manages window creation, update, event dispatching, and OpenGL context.
	 */
	class Window {
	public:
		Window() = default;
		~Window() = default;

		/**
		 * @brief Initializes the window with given title and size.
		 * Sets up GLFW, OpenGL context, and event callbacks.
		 */
		void Init(const char* title, int width, int height);
		void Shutdown();

		/** @brief Polls window events and swaps the OpenGL buffers. */
		void OnUpdate();

		/** @return True if VSync is enabled, false otherwise. */
		bool GetVsync() const { return m_Vsync;  }
		void SetVSync(bool enabled);

		void HideCursor(bool hide);

		/** @return The native GLFWwindow pointer. */
		GLFWwindow* GetNativeWindow() const { return m_Window; }

		/** @return Time in seconds since last frame. */
		const float GetDeltaTime() const { return m_DeltaTime; }

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
		
		float GetScale();
	private:
		/**
		 * @brief Sets the callback function to receive window events.
		 * @param callback Function accepting an Event reference.
		 * 
		 * The Application class is the only one that should set this callback.
		 */
		void SetEventCallback(const std::function<void(Event&)>& callback) { m_EventCallback = callback; }
	private:
		std::function<void(Event&)> m_EventCallback;

		GLFWwindow* m_Window;
		int m_Width, m_Height;
		bool m_Vsync = true;

		float m_DeltaTime = 0;
		float m_LastFrameTime = 0;

		friend class Application; // Allow only Application to set the event callback
	};
}