#include "Application.h"
#include "Log.h"

#include "RealEngine/Render/Renderer.h"

namespace RealEngine {
	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification) {
		RE_PROFILE_FUNCTION();
		
		RE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window.SetEventCallback(RE_BIND_EVENT_FN(Application::OnEvent));
		m_Window.Init(m_Specification.Name.c_str(), 1280, 720);

		RE_CORE_INFO("Working Directory: {0}", std::filesystem::current_path().string());
		RenderCommands::Init();
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
	}

	Application::~Application() {
		RE_PROFILE_FUNCTION();

		m_LayerStack.Clear();
		Renderer::Shutdown();
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

	void Application::Stop() {
		RE_PROFILE_FUNCTION();

		m_Running = false;
	}

	void Application::OnEvent(Event& e) {
		RE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(RE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(RE_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		RE_PROFILE_FUNCTION();

		Stop();

		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		RE_PROFILE_FUNCTION();
		RenderCommands::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
}