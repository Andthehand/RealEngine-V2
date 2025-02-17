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
		ImGui::Begin("Properties");
		ImGui::Text(("Selected Folder: " + m_SelectedFolder.string()).c_str());
		ImGui::End();
	}

	void PropertiesPanel::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<PannelFolderSelectEvent>([this](PannelFolderSelectEvent& e) {
			SelectFolder(e.GetPath());
			return true;
		});
	}
}