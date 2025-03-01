#pragma once
#pragma warning( disable : 4100 )

#include "RealEngine/Core/Assert.h"
#include "RealEngine/Core/LayerStack.h"
#include "RealEngine/Core/Window.h"

#include "RealEngine/Events/Event.h"
#include "RealEngine/Events/WindowEvents.h"

#include "RealEngine/ImGui/ImGuiLayer.h"

namespace RealEngine {
	struct ApplicationCommandLineArgs {
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const {
			RE_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct ApplicationSpecification {
		std::string Name = "RealEngine Application";

		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application {
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		//You should never Pop a layer
		void PushLayer(Layer* layer);

		void Run();
		void Stop();

		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Window& GetWindow() { return m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		//Singleton
		inline static Application* s_Instance = nullptr;
		const ApplicationSpecification m_Specification;

		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;
		Window m_Window;

		bool m_Running = true;
	};

	Application* CreateApplication(const ApplicationCommandLineArgs& args);
}