#include "FileExplorerPanel.h"

#include "Events/PanelEvents.h"

#include <imgui.h>

namespace RealEngine {
	FileExplorerPanel::FileExplorerPanel() 
		: m_CurrentDirectory(std::filesystem::current_path()) {}

	void FileExplorerPanel::OnImGui() {
		RE_PROFILE_FUNCTION();

		ImGui::Begin("File Explorer");
		
		if (ImGui::Button("<-")) {
			m_CurrentDirectory = m_CurrentDirectory.parent_path();
		}

		for (const auto& entry : std::filesystem::directory_iterator(m_CurrentDirectory)) {
			const auto& path = entry.path();
			if (ImGui::Button(path.filename().string().c_str())) {
				PannelFolderSelectEvent event(path);
				Application::Get().OnEvent(event);
			}
			
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) 
				&& entry.is_directory()) {
				m_CurrentDirectory = path;
			}
		}
		ImGui::End();
	}
}