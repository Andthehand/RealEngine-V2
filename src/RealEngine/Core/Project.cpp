#include "Project.h"
#include "ProjectSerializer.h"

#include "RealEngine/Events/ProjectEvents.h"

#include <algorithm>

namespace RealEngine {
	Project::~Project() {
		m_CurrentScene.reset();
		m_ScriptEngine.reset();
	}

	void Project::CreateNewProject(const std::string& projectName, const std::filesystem::path& path) {
		s_ActiveProject = CreateRef<Project>();

		s_ActiveProject->m_ProjectName = projectName;
		s_ActiveProject->m_ProjectPath = path / projectName;

		// Create all the necessary directories
		std::filesystem::create_directories(s_ActiveProject->m_ProjectPath);

		std::filesystem::path assetsPath = GetAssetsPath();
		std::filesystem::create_directories(assetsPath);
		std::filesystem::create_directories(assetsPath / "Scenes");
		std::filesystem::create_directories(assetsPath / "Textures");

		s_ActiveProject->m_CurrentScene = CreateRef<Scene>();
		s_ActiveProject->m_CurrentScene->SetFilePath(assetsPath / "Scenes" / "Default.rescene");

		std::filesystem::path scriptPath = GetScriptsPath();
		std::filesystem::create_directories(scriptPath);
		Save();
	}

	void Project::Delete() {
		s_ActiveProject.reset();
	}

	void Project::Save() {
		Save(s_ActiveProject->m_ProjectName);
		s_ActiveProject->m_CurrentScene->Save();
	}

	void Project::Load(const std::filesystem::path& filePath) {
		RE_CORE_ASSERT(std::filesystem::is_regular_file(filePath), "Project file does not exist!");
		
		s_ActiveProject = CreateRef<Project>();
		s_ActiveProject->m_ProjectPath = filePath.parent_path();
		s_ActiveProject->m_ProjectName = filePath.stem().string();

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
		return std::filesystem::relative(absolutePath, GetAssetsPath());
	}

	std::filesystem::path Project::ResolveAssetPathFromAssetFolder(const std::filesystem::path& relativePath) {
		return GetAssetsPath() / relativePath;
	}
}
