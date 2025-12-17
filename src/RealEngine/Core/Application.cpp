#include "Application.h"

#include "yaml.h"

namespace RealEngine {
	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification) {
		RE_PROFILE_FUNCTION();
		
		RE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		SetYAMLErrorCallbacks();

		m_Window.SetEventCallback(RE_BIND_EVENT_FN(Application::OnEvent));
		m_Window.Init(m_Specification.Name.c_str(), 1280, 720);

		RenderCommands::Init();

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
		RE_CORE_TRACE("Application is running...");

		while (m_Running) {
			RE_PROFILE_FRAME();

			ExecuteMainThreadQueue();

			{
				RE_PROFILE_SCOPE("OnUpdate");
				m_Window.OnUpdate();

				float deltaTime = m_Window.GetDeltaTime();

				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(deltaTime);
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

	void Application::SubmitToMainThread(const std::function<void()>& function) {
		RE_PROFILE_FUNCTION();

		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		m_MainThreadQueue.emplace_back(function);
	}

	void Application::ExecuteMainThreadQueue() {
		RE_PROFILE_FUNCTION();
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		for (auto& func : m_MainThreadQueue) {
			func();
		}

		m_MainThreadQueue.clear();
	}
}