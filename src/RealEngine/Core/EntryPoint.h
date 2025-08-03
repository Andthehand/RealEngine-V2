#pragma once
#include "RealEngine.h"
#include "RealEngine/Core/Logger.h"
#include "RealEngine/Formatter/GLMFormatter.h"

#ifdef RE_PLATFORM_WINDOWS
extern "C"
{
	/**
	 * @brief Enables NVIDIA Optimus GPU switching on Windows.
	 *
	 * Setting this variable exports the preference for
	 * the high-performance NVIDIA GPU instead of integrated graphics.
	 */
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif


/**
 * @brief Factory function to create the application instance.
 *
 * Must be implemented by the user to return a new RealEngine::Application subclass instance.
 *
 * @param args Command-line arguments.
 * @return Pointer to the created Application instance.
 */
extern RealEngine::Application* RealEngine::CreateApplication(const ApplicationCommandLineArgs& args);

/**
 * @brief Entry point of the application.
 *
 * Initializes logging, creates the application instance,
 * runs the main loop, and cleans up on exit.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return Exit code (0 on success).
 */
int main(int argc, char** argv) {
	RealEngine::Logger::Init();

	auto app = RealEngine::CreateApplication({ argc, argv });

	app->Run();

	delete app;
}