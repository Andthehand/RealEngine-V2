#include <RealEngine/Core/EntryPoint.h>
#include <RealEngine.h>

#include "EditorLayer.h"

namespace RealEngine {
	class Editor : public Application {
	public:
		Editor(const ApplicationSpecification& specification)
			: Application(specification) {
			PushLayer(new EditorLayer());
		}

		~Editor() = default;
	};

	Application* CreateApplication(const ApplicationCommandLineArgs& args) {
		RE_PROFILE_FUNCTION();

		ApplicationSpecification specification = { "Editor", args };
		return new Editor(specification);
	}
}
