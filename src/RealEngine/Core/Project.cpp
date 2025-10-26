#include "Project.h"

#include <ryml.hpp>
#include <ryml_std.hpp>
#include <algorithm>

namespace RealEngine {
	void Project::CreateNewProject() {
		s_ProjectName = "NewProject";
		s_ProjectPath = ""; // Empty because we don't know where to save yet

		s_CurrentScene = CreateRef<Scene>();
		s_AssetManager.Clear();
	}

	void Project::ClearProject() {
		s_ProjectName = "";
		s_ProjectPath = "";
		s_CurrentScene = nullptr;
		s_AssetManager.Clear();
	}

	void Project::Save() {
		if (!IsFullyInitialized()) {
			// Prompt user to select save location
			std::filesystem::path filePath = FileDialogs::SaveFile("Real Engine Project (*.reproj)\0*.reproj\0");
			if (filePath.empty()) {
				RE_CORE_WARN("Project save was canceled or failed!");
				return;
			}

			SetupProject(filePath);
		}

		Save(s_ProjectName);
		s_CurrentScene->Save();
	}

	void Project::Load(const std::filesystem::path& filePath) {
		RE_CORE_ASSERT(std::filesystem::is_regular_file(filePath), "Project file does not exist!");
		SetupProject(filePath);

		// Read in file
		FileHelper fileHelper(filePath, "r");
		std::string fileContents = fileHelper.ReadAllText();

		ryml::Tree tree = ryml::parse_in_place(ryml::to_csubstr(filePath.filename().string()), ryml::to_substr(fileContents));
		ryml::ConstNodeRef root = tree.rootref();
		RE_CORE_ASSERT(!tree.empty(), "Failed to parse project file: Tree is empty");

		if (root.has_child("ProjectName")) {
			root["ProjectName"] >> s_ProjectName;
		}
		else {
			RE_CORE_WARN("Project file missing 'ProjectName'");
		}

		// Needs to be loaded before the scene but after project path is set
		s_AssetManager.Load();

		if (root.has_child("CurrentScene")) {
			std::string scenePath;

			root["CurrentScene"] >> scenePath;
			RE_CORE_ASSERT(!scenePath.empty(), "Current scene path in project file is empty");
			scenePath = (s_ProjectPath / scenePath).string();

			// Ensure path uses forward slashes for consistency across platforms
			std::replace(scenePath.begin(), scenePath.end(), '\\', '/');

			if (std::filesystem::is_regular_file(scenePath)) {
				s_CurrentScene = CreateRef<Scene>(std::filesystem::path(scenePath));
			}
			else {
				RE_CORE_WARN("Current scene file does not exist: {}", scenePath);
			}
		}
		else {
			RE_CORE_WARN("Project file missing 'CurrentScene'");
		}
	}

	void Project::Save(const std::string& projectName) {
		RE_CORE_ASSERT(!projectName.empty(), "Project name cannot be empty");
		if (projectName.empty())
			return;

		s_AssetManager.Save();
		s_ProjectName = projectName;
		std::filesystem::path filePath = s_ProjectPath / (projectName + ".reproj");

		ryml::Tree tree;
		ryml::NodeRef root = tree.rootref();
		root |= ryml::MAP;

		root["ProjectName"] << s_ProjectName;

		if (!s_CurrentScene->GetFilePath().empty()) {
			auto relative = s_CurrentScene->GetFilePath().lexically_relative(s_ProjectPath);
			root["CurrentScene"] << relative;
		}

		FileHelper fileHelper(filePath, "w");
		FILE* file = fileHelper.GetFileHandle();
		ryml::emit_yaml(tree, file);

		RE_CORE_WARN("Project was serialized into {}", filePath.string());
	}

	void Project::SetupProject(const std::filesystem::path& projectFilePath) {
		s_ProjectPath = std::filesystem::absolute(projectFilePath.parent_path());
		s_ProjectName = projectFilePath.stem().string();

		std::filesystem::path assetsPath = s_ProjectPath / "assets";
		if (!std::filesystem::is_directory(assetsPath)) {
			RE_CORE_WARN("Creating assets directory: {}", assetsPath.string());

			std::filesystem::create_directory(assetsPath);
		}
	}
}

