#include "EditorLayer.h"

#include <imgui.h>

namespace RealEngine {
	EditorLayer::EditorLayer()
		: Layer("Editor") {}

	void EditorLayer::OnAttach() {
		Application::Get().GetWindow().SetVSync(true);
		RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	}

	void EditorLayer::OnDetach() {
	}

	void EditorLayer::OnUpdate() {
		RenderCommands::Clear();
	}

	void EditorLayer::OnImGui() {
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void EditorLayer::OnEvent(const Event& event) {
	}
}
