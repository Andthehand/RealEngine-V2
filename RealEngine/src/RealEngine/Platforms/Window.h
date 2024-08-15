#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RealEngine/Events/Event.h"

namespace RealEngine {
	class Window {
	public:
		Window() = default;
		~Window() = default;

		void Init(const char* title, int width, int height);
		void Shutdown();

		void OnUpdate();

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		void SetEventCallback(const std::function<void(Event&)>& callback) { m_EventCallback = callback; }

		//Temp
		bool ShouldClose() { return glfwWindowShouldClose(m_Window); }
	private:
		std::function<void(Event&)> m_EventCallback;

		GLFWwindow* m_Window;
		int m_Width, m_Height;
	};
}