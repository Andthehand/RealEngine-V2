#include "Project.h"

#include <ryml.hpp>
#include <ryml_std.hpp>

namespace RealEngine {
	Project::Project(const std::filesystem::path& filePath)
		: m_ProjectPath(std::filesystem::absolute(filePath.parent_path())), m_ProjectName(filePath.stem().string()) {
		Load(filePath);
	}

	void Project::Save() {
		Save(m_ProjectName);

		if(m_CurrentScene) {
			m_CurrentScene->Save();
		}
	}

	// TODO: Implement project saving (e.g. to a .reproj file)
	void Project::Save(const std::string& projectName) {
		std::filesystem::path filePath = m_ProjectPath / (projectName + ".reproj");
		m_ProjectName = projectName;

		ryml::Tree tree;
		ryml::NodeRef root = tree.rootref();
		root |= ryml::MAP;

		root["ProjectName"] << m_ProjectName;

		// Serialize the current scene
		if (m_CurrentScene) {
			root["CurrentScene"] << m_CurrentScene->GetFilePath().lexically_relative(m_ProjectPath);
		}

		// Write the YAML tree to a file
		FileHelper fileHelper(filePath, "w");
		FILE* file = fileHelper.GetFileHandle();
		ryml::emit_yaml(tree, file);

		RE_CORE_WARN("Project was serialized into {}", filePath);
	}

	// TODO: Implement project loading (e.g. from a .reproj file)
	void Project::Load(const std::filesystem::path& filePath) {
		RE_CORE_ASSERT(std::filesystem::exists(filePath), "Project file does not exist!");

		// Read in file
		FileHelper fileHelper(filePath, "r");
		std::string fileContents = fileHelper.ReadAllText();

		ryml::Tree tree = ryml::parse_in_place(ryml::to_csubstr(filePath.filename().string()), ryml::to_substr(fileContents));
		ryml::ConstNodeRef root = tree.rootref();
		RE_CORE_ASSERT(!tree.empty(), "Failed to parse project file: Tree is empty");

		if (root.has_child("ProjectName")) {
			root["ProjectName"] >> m_ProjectName;
		} else {
			RE_CORE_WARN("Project file missing 'ProjectName'");
		}

		if (root.has_child("CurrentScene")) {
			std::filesystem::path scenePath;

			root["CurrentScene"] >> scenePath;
			scenePath = m_ProjectPath / scenePath;

			if (std::filesystem::exists(scenePath)) {
				m_CurrentScene = CreateRef<Scene>(scenePath);
			} else {
				RE_CORE_WARN("Current scene file does not exist: {}", scenePath.string());
			}
		} else {
			RE_CORE_WARN("Project file missing 'CurrentScene'");
		}
	}
}

