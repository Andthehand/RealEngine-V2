#include "ProjectSerializer.h"

#include <ryml.hpp>
#include <ryml_std.hpp>

namespace RealEngine {
	bool ProjectSerializer::Serialize(Ref<Project> project, const std::filesystem::path& filepath) {
		if (project->m_ProjectName.empty())
			return false;

		// Use project instance members instead of undefined statics
		project->m_AssetManager.Save();
		const std::string& projectName = project->m_ProjectName;
		const std::filesystem::path& projectPath = project->m_ProjectPath;
		std::filesystem::path filePath = projectPath / (projectName + ".reproj");

		ryml::Tree tree;
		ryml::NodeRef root = tree.rootref();
		root |= ryml::MAP;

		root["ProjectName"] << projectName;

		if (project->m_CurrentScene && !project->m_CurrentScene->GetFilePath().empty()) {
			auto relative = project->m_CurrentScene->GetFilePath().lexically_relative(projectPath);
			root["CurrentScene"] << relative;
		}

		FileHelper fileHelper(filePath, "w");
		FILE* file = fileHelper.GetFileHandle();
		ryml::emit_yaml(tree, file);

		RE_CORE_WARN("Project was serialized into {}", filePath);
		return true;
	}

	bool ProjectSerializer::Deserialize(Ref<Project> project, const std::filesystem::path& filepath) {
		RE_CORE_ASSERT(std::filesystem::is_regular_file(filepath), "Project file does not exist!");
		Project::SetupProject(filepath);

		// Read in file
		FileHelper fileHelper(filepath, "r");
		std::string fileContents = fileHelper.ReadAllText();

		ryml::Tree tree = ryml::parse_in_place(ryml::to_csubstr(filepath.filename().string()), ryml::to_substr(fileContents));
		ryml::ConstNodeRef root = tree.rootref();
		RE_CORE_ASSERT(!tree.empty(), "Failed to parse project file: Tree is empty");

		if (root.has_child("ProjectName")) {
			root["ProjectName"] >> project->m_ProjectName;
		}
		else {
			RE_CORE_WARN("Project file missing 'ProjectName'");
		}

		// Needs to be loaded before the scene but after project path is set
		project->m_AssetManager.Load();

		std::filesystem::path projectScriptsPath = Project::GetScriptsPath() / "Build";
		project->m_ScriptEngine.reset();
		project->m_ScriptEngine = CreateRef<ScriptEngine>(projectScriptsPath, project->m_ProjectName);

		if (root.has_child("CurrentScene")) {
			std::string scenePath;
			root["CurrentScene"] >> scenePath;
			RE_CORE_ASSERT(!scenePath.empty(), "Current scene path in project file is empty");
			std::filesystem::path absScenePath = project->m_ProjectPath / scenePath;

			// Ensure path uses forward slashes for consistency across platforms
			std::string absScenePathStr = absScenePath.string();
			std::replace(absScenePathStr.begin(), absScenePathStr.end(), '\\', '/');

			if (std::filesystem::is_regular_file(absScenePathStr)) {
				project->SetCurrentScene(RealEngine::CreateRef<Scene>(std::filesystem::path(absScenePathStr)));
			}
			else {
				RE_CORE_WARN("Current scene file does not exist: {}", absScenePathStr);
			}
		}
		else {
			RE_CORE_WARN("Project file missing 'CurrentScene'");
		}
		return true;
	}
}