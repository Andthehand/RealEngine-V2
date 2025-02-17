#pragma once 
#include "RealEngine.h"

#include "Panel.h"

#include <filesystem>

namespace RealEngine {
	class PropertiesPanel : public Panel {
	public:
		PropertiesPanel();
		~PropertiesPanel() = default;

		void SelectFolder(const std::filesystem::path& path);

		virtual void OnImGui() override;
		void OnEvent(Event& event);
	private:
		std::filesystem::path m_SelectedFolder = "";
	};
}