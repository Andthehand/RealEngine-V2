#include "PropertiesPanel.h"

#include "Events/PanelEvents.h"

#include <imgui.h>

namespace RealEngine {
	PropertiesPanel::PropertiesPanel() {
	}
	
	void PropertiesPanel::SelectFolder(const std::filesystem::path& path) {
		m_SelectedFolder = path;
	}
	
	void PropertiesPanel::OnImGui() {
		RE_PROFILE_FUNCTION();

		ImGui::Begin("Properties");
		ImGui::Text(("Selected Folder: " + m_SelectedFolder.string()).c_str());

		float dt = Application::Get().GetWindow().GetDeltaTime();
		float fps = 1.0f / dt;
		ImGui::Text("FPS: %f", fps);
		ImGui::Text("DeltaTime: %f", dt);
		ImGui::End();
	}

	void PropertiesPanel::OnEvent(Event& event) {
		RE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<PannelFolderSelectEvent>([this](PannelFolderSelectEvent& e) {
			SelectFolder(e.GetPath());
			return true;
		});
	}
}