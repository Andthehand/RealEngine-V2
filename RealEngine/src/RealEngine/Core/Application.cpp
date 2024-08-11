#include "Application.h"
#include "Log.h"

namespace RealEngine {
	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification) {}

	void Application::Run() {
		RE_CORE_INFO("Application is running...");

		//TODO: replace true with if the window is still open
		while (true) {
			std::vector<std::string> messages = {
				"Hello, World! ",
				"Hello, World! ",
				"Hello, World! "
			};

			for (const auto& message : messages) {
				RE_CORE_TRACE(message);
				RE_CORE_INFO(message);
				RE_CORE_WARN(message);
				RE_CORE_ERROR(message);
				RE_CORE_CRITICAL(message);
			}
		}
	}
}