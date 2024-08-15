#include "Application.h"
#include "Log.h"

namespace RealEngine {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification) {
		RE_PROFILE_FUNCTION();
		
		RE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window.SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window.Init(m_Specification.Name.c_str(), 1280, 720);
	}

	Application::~Application() {
		RE_PROFILE_FUNCTION();

		m_Window.Shutdown();
	}

	void Application::PushLayer(Layer* layer) {
		RE_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
	}

	void Application::Run() {
		RE_CORE_INFO("Application is running...");

		//TODO: replace true with if the window is still open
		while (!m_Window.ShouldClose()) {
			RE_PROFILE_FRAME();

			{
				RE_PROFILE_SCOPE("OnUpdate");
				m_Window.OnUpdate();

				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate();
				}
			}

			{
				RE_PROFILE_SCOPE("OnImGui");
				for (Layer* layer : m_LayerStack) {
					layer->OnImGui();
				}
			}
		}
	}

	void Application::OnEvent(Event& e) {
		RE_PROFILE_FUNCTION();

		RE_CORE_INFO("{0}", e);
	}
}