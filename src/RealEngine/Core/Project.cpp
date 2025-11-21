#include "Project.h"
#include "ProjectSerializer.h"

#include "RealEngine/Events/ProjectEvents.h"

#include <algorithm>

namespace RealEngine {
	Project::~Project() {
		m_CurrentScene.reset();
		m_ScriptEngine.reset();
	}

	void Project::CreateNewProject() {
		s_ActiveProject = CreateRef<Project>();

		s_ActiveProject->m_ProjectPath = "";
		s_ActiveProject->m_ProjectName = "NewProject";
		s_ActiveProject->m_CurrentScene = CreateRef<Scene>();
	}

	void Project::Delete() {
		s_ActiveProject->m_CurrentScene.reset();
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

		Save(s_ActiveProject->m_ProjectName);
		s_ActiveProject->m_CurrentScene->Save();
	}

	void Project::Load(const std::filesystem::path& filePath) {
		RE_CORE_ASSERT(std::filesystem::is_regular_file(filePath), "Project file does not exist!");
		ProjectSerializer::Deserialize(s_ActiveProject, filePath);
	}

	void Project::Save(const std::string& projectName) {
		RE_CORE_ASSERT(!projectName.empty(), "Project name cannot be empty");

		std::filesystem::path filePath = s_ActiveProject->m_ProjectPath / (projectName + ".reproj");
		ProjectSerializer::Serialize(s_ActiveProject, filePath);
	}

	void Project::SetCurrentScene(const Ref<Scene>& scene) {
		SceneChangedEvent event;
		RE_RAISE_EVENT(event);
		s_ActiveProject->m_CurrentScene = scene;

		// Clean up assets from previous scene
		s_ActiveProject->m_AssetManager.ClearUnusedAssets();
	}

	std::filesystem::path Project::GetRelativePathToAssetFolder(const std::filesystem::path& absolutePath) {
		RE_CORE_ASSERT(IsFullyInitialized(), "Project is not fully initialized!");

		return std::filesystem::relative(absolutePath, GetAssetsPath());
	}

	std::filesystem::path Project::ResolveAssetPathFromAssetFolder(const std::filesystem::path& relativePath) {
		RE_CORE_ASSERT(IsFullyInitialized(), "Project is not fully initialized!");

		return GetAssetsPath() / relativePath;
	}

	void Project::SetupProject(const std::filesystem::path& projectFilePath) {
		s_ActiveProject->m_ProjectPath = std::filesystem::absolute(projectFilePath.parent_path());
		s_ActiveProject->m_ProjectName = projectFilePath.stem().string();

		std::filesystem::path assetsPath = s_ActiveProject->m_ProjectPath / "assets";
		std::filesystem::path scriptsPath = assetsPath / "Scripts";

		// This will create the directories if they do not already exist
		std::filesystem::create_directory(assetsPath);
		std::filesystem::create_directory(scriptsPath);
	}
}
