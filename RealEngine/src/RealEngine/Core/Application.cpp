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

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
	}

	Application::~Application() {
		RE_PROFILE_FUNCTION();

		m_LayerStack.Clear();
		m_Window.Shutdown();
	}

	void Application::PushLayer(Layer* layer) {
		RE_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
	}

	void Application::Run() {
		RE_CORE_INFO("Application is running...");

		//TODO: replace true with if the window is still open
		while (m_Running) {
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

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack) {
					layer->OnImGui();
				}
				m_ImGuiLayer->End();
			}
		}
	}

	void Application::OnEvent(Event& e) {
		RE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		RE_PROFILE_FUNCTION();

		m_Running = false;

		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		RE_PROFILE_FUNCTION();

		RenderCommands::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
}