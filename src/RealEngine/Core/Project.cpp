#include "Project.h"

#include <ryml.hpp>
#include <ryml_std.hpp>
#include <algorithm>

namespace RealEngine {
	void Project::Initialize(const std::filesystem::path& filePath) {
		s_ProjectPath = std::filesystem::absolute(filePath.parent_path());
		s_ProjectName = filePath.stem().string();
		Load(filePath);
	}

	void Project::Shutdown() {
		s_CurrentScene.reset();
		s_ProjectName.clear();
		s_ProjectPath.clear();
	}

	void Project::Save() {
		if (s_ProjectName.empty())
			return;
		Save(s_ProjectName);
		if (s_CurrentScene) {
			s_CurrentScene->Save();
		}
	}

	void Project::Save(const std::string& projectName) {
		RE_CORE_ASSERT(!projectName.empty(), "Project name cannot be empty");
		if (projectName.empty())
			return;

		s_ProjectName = projectName;
		std::filesystem::path filePath = s_ProjectPath / (projectName + ".reproj");

		ryml::Tree tree;
		ryml::NodeRef root = tree.rootref();
		root |= ryml::MAP;

		root["ProjectName"] << s_ProjectName;

		if (s_CurrentScene) {
			auto relative = s_CurrentScene->GetFilePath().lexically_relative(s_ProjectPath);
			root["CurrentScene"] << relative;
		}

		FileHelper fileHelper(filePath, "w");
		FILE* file = fileHelper.GetFileHandle();
		ryml::emit_yaml(tree, file);

		RE_CORE_WARN("Project was serialized into {}", filePath.string());
	}

	void Project::Load(const std::filesystem::path& filePath) {
		RE_CORE_ASSERT(std::filesystem::exists(filePath), "Project file does not exist!");

		// Read in file
		FileHelper fileHelper(filePath, "r");
		std::string fileContents = fileHelper.ReadAllText();

		ryml::Tree tree = ryml::parse_in_place(ryml::to_csubstr(filePath.filename().string()), ryml::to_substr(fileContents));
		ryml::ConstNodeRef root = tree.rootref();
		RE_CORE_ASSERT(!tree.empty(), "Failed to parse project file: Tree is empty");

		if (root.has_child("ProjectName")) {
			root["ProjectName"] >> s_ProjectName;
		} else {
			RE_CORE_WARN("Project file missing 'ProjectName'");
		}

		if (root.has_child("CurrentScene")) {
			std::string scenePath;

			root["CurrentScene"] >> scenePath;
			scenePath = (s_ProjectPath / scenePath).string();

			// Ensure path uses forward slashes for consistency across platforms
			std::replace(scenePath.begin(), scenePath.end(), '\\', '/');

			if (std::filesystem::exists(scenePath)) {
				s_CurrentScene = CreateRef<Scene>(std::filesystem::path(scenePath));
			} else {
				RE_CORE_WARN("Current scene file does not exist: {}", scenePath);
			}
		} else {
			RE_CORE_WARN("Project file missing 'CurrentScene'");
		}
	}
}

