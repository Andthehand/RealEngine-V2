#pragma once
#include <filesystem>

#include "Panel.h"

namespace RealEngine {
	class FileExplorerPanel : public Panel {
	public:
		FileExplorerPanel();
		~FileExplorerPanel() = default;

		virtual void OnImGui() override;
	private:
		std::filesystem::path m_CurrentDirectory;
	};
}