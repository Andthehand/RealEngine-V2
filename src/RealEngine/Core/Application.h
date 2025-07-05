#pragma once
#pragma warning( disable : 4100 )

#include "RealEngine/Core/Assert.h"
#include "RealEngine/Core/LayerStack.h"
#include "RealEngine/Core/Window.h"

#include "RealEngine/Events/Event.h"
#include "RealEngine/Events/WindowEvents.h"

#include "RealEngine/ImGui/ImGuiLayer.h"

//TODO: Fix github action build error
//TODO: Turn the event types to be more dynamic with the dispatcher
//TODO: Look into adding a multithreaded renderer

namespace RealEngine {
	/**
	 * @brief Command line arguments passed to the application by child application.
	 */
	struct ApplicationCommandLineArgs {
		int Count = 0;
		char** Args = nullptr;

		/**
		 * @brief Access an argument by index.
		 * @param index The index of the argument.
		 * @return The argument string.
		 */
		const char* operator[](int index) const {
			RE_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	/**
	 * @brief Contains configuration details for initializing an application.
	 */
	struct ApplicationSpecification {
		std::string Name = "RealEngine Application";

		ApplicationCommandLineArgs CommandLineArgs;
	};

	/**
	 * @brief Core class representing a RealEngine application.
	 *
	 * The Application class is the entry point and main controller for a RealEngine application.
	 * It handles the window, event loop, layers, and ImGui rendering.
	 */
	class Application {
	public:
		/**
		 * @brief Constructs the application with a given specification.
		 * @param specification Application settings and CLI arguments.
		 */
		Application(const ApplicationSpecification& specification);

		/**
		 * @brief Destructor. Cleans up resources.
		 */
		virtual ~Application();

		/**
		 * @brief Adds a layer to the layer stack.
		 * @param layer The layer to push.
		 *
		 * @note You should never pop a layer
		 */
		void PushLayer(Layer* layer);

		void Run();
		void Stop();

		/**
		 * @brief Handles an event and dispatches it to the appropriate handlers.
		 *
		 * This sends the event in reverse order through the layer stack.
		 * The event is passed to each layer until it is marked as handled.
		 *
		 * @param e The event to process.
		 */
		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		/**
		 * @brief Gets the main application window.
		 * @return Reference to the Window object.
		 */
		Window& GetWindow() { return m_Window; }

		/**
		 * @brief Gets the singleton instance of the application.
		 * @return Reference to the Application instance.
		 */
		static Application& Get() { return *s_Instance; }
	private:
		inline static Application* s_Instance = nullptr; ///< Singleton instance.
		const ApplicationSpecification m_Specification;

		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;
		Window m_Window;

		bool m_Running = true;
	};

	/**
	 * @brief User-defined factory function to create a custom application instance.
	 * @param args Command-line arguments.
	 * @return A pointer to a new Application instance.
	 */
	Application* CreateApplication(const ApplicationCommandLineArgs& args);
}