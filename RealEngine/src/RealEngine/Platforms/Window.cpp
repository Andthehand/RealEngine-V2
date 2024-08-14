#include "Window.h"

namespace RealEngine {
	static void GLFWErrorCallback(int error, const char* description) {
		RE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	void Window::Init(const char* title, int width, int height) {
		RE_PROFILE_FUNCTION();

		m_Width = width;
		m_Height = height;

		int success = glfwInit();
		RE_CORE_ASSERT(success, "Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef RE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	#endif 


		m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if(!m_Window) {
			glfwTerminate();
			RE_CORE_ASSERT(false, "Failed to create window");
		}

		glfwMakeContextCurrent(m_Window);

		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RE_CORE_ASSERT(success, "Failed to initialize Glad");
	}

	void Window::Shutdown() {
		RE_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::OnUpdate() {
		RE_PROFILE_FUNCTION();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}