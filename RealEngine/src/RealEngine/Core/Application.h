#pragma once
#include "RealEngine/Core/Assert.h"
#include "RealEngine/Core/LayerStack.h"
#include "RealEngine/Platforms/Window.h"

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

		static Application& Get() { return *s_Instance; }
	private:
		inline static Application* s_Instance = nullptr;

		const ApplicationSpecification m_Specification;

		LayerStack m_LayerStack;

		Window m_Window;
	};

	Application* CreateApplication(const ApplicationCommandLineArgs& args);
}