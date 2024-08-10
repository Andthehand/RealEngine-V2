#pragma once
#include "RealEngine/Core/Assert.h"

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
		virtual ~Application() = default;

		void Run();

		private:
			const ApplicationSpecification m_Specification;
	};

	Application* CreateApplication(const ApplicationCommandLineArgs& args);
}