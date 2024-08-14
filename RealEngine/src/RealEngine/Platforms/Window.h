#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

		//Temp
		bool ShouldClose() { return glfwWindowShouldClose(m_Window); }
	private:
		GLFWwindow* m_Window;
		int m_Width, m_Height;
	};
}