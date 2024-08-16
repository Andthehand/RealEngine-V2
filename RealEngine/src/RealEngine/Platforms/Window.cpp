#include "Window.h"
#include "RealEngine/Events/WindowEvents.h"
#include "RealEngine/Events/KeyEvents.h"
#include "RealEngine/Events/MouseEvents.h"

namespace RealEngine {
	static void GLFWErrorCallback(int error, const char* description) {
		RE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	void Window::Init(const char* title, int width, int height) {
		RE_PROFILE_FUNCTION();

		m_Width = width;
		m_Height = height;

		{
			RE_PROFILE_SCOPE("glfwInit");

			int success = glfwInit();
			RE_CORE_ASSERT(success, "Failed to initialize GLFW");
		}

		{
			RE_PROFILE_SCOPE("glfwCreateWindow");

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef RE_DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif 


			m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
			if (!m_Window) {
				glfwTerminate();
				RE_CORE_ASSERT(false, "Failed to create window");
			}
		}


		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);

		{
			RE_PROFILE_SCOPE("gladLoader");
			int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			RE_CORE_ASSERT(success, "Failed to initialize Glad");
		}

		glfwSetWindowUserPointer(m_Window, &m_EventCallback);

		{
			RE_PROFILE_SCOPE("SetGLFWCallbacks");
			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				callback(event);
			});

			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
				WindowResizeEvent event(width, height);
				callback(event);
			});

			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

				switch (action) {
					case GLFW_PRESS: {
						KeyPressedEvent event(key);
						callback(event);
						break;
					}
					case GLFW_RELEASE: {
						KeyReleasedEvent event(key);
						callback(event);
						break;
					}
				}
			});

			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xpos, (float)ypos);
				callback(event);
			});
		}
	}

	void Window::Shutdown() {
		RE_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::OnUpdate() {
		RE_PROFILE_FUNCTION();

		{
			RE_PROFILE_SCOPE("Poll Events");
			glfwPollEvents();
		}

		{
			RE_PROFILE_SCOPE("Swap Buffers");
			glfwSwapBuffers(m_Window);
		}
	}
}