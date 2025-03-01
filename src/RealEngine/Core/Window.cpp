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
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			RE_PROFILE_SCOPE("glfwCreateWindow");

			glfwWindowHint(GLFW_SCALE_TO_MONITOR, false);

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

		{
			RE_PROFILE_SCOPE("gladLoader");
			int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			RE_CORE_ASSERT(success, "Failed to initialize Glad");
		}

		{
			RE_PROFILE_SCOPE("glfwSettings");
			SetVSync(true);
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

			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
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

			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int /*mods*/) {
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

				switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event((MouseCode)button);
					callback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event((MouseCode)button);
					callback(event);
					break;
				}
				}
			});

			glfwSetWindowContentScaleCallback(m_Window, [](GLFWwindow* window, float xscale, float yscale) {
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

				//x and y scale are the same
				WindowRescaledEvent event(xscale);
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
		{
			RE_PROFILE_SCOPE("Window Poll Events");
			glfwPollEvents();
		}

		{
			RE_PROFILE_SCOPE("Window Swap Buffers");
			glfwSwapBuffers(m_Window);

			float currentTime = (float)glfwGetTime();
			m_DeltaTime = currentTime - m_LastFrameTime;
			m_LastFrameTime = currentTime;
		}
	}

	void Window::SetVSync(bool enabled) {
		RE_PROFILE_FUNCTION();

		m_Vsync = enabled;
		glfwSwapInterval(enabled);
	}

	float Window::GetScale() {
		RE_PROFILE_FUNCTION();
		RE_CORE_ASSERT(m_Window);

		float scale;
		glfwGetWindowContentScale(m_Window, &scale, &scale);

		return scale;
	}
}