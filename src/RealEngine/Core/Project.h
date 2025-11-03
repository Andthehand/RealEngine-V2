#pragma once
#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Scene.h"

#include "RealEngine/Asset/AssetManager.h"

#include <filesystem>

namespace RealEngine {

	// Static-only Project manager
	class Project {
	public:
		Project() = delete;

		// Initialize project data (replaces constructor/Create())
		static void CreateNewProject(); // New project
		static void ClearProject(); // Esentially a "destructor" for the static data

		static void Load(const std::filesystem::path& filePath);

		static void Save(); // Uses current project name
		static void Save(const std::string& projectName);

		static Ref<Scene>& GetCurrentScene() { return s_CurrentScene; }
		static void SetCurrentScene(const Ref<Scene>& scene);

		static AssetManager& GetAssetManager() { return s_AssetManager; }

		static const std::string& GetProjectName() { return s_ProjectName; }
		static const std::filesystem::path& GetProjectPath() { return s_ProjectPath; }
		static std::filesystem::path GetAssetsPath() { return s_ProjectPath / "assets"; }

		static std::filesystem::path GetRelativePathToAssetFolder(const std::filesystem::path& absolutePath);
		static std::filesystem::path ResolveAssetPathFromAssetFolder(const std::filesystem::path& relativePath);

		static bool IsFullyInitialized() { return !s_ProjectPath.empty(); }
	private:
		static void SetupProject(const std::filesystem::path& projectFilePath);
	private:
		// Project name is the project file name without extension
		inline static std::string s_ProjectName;
		inline static std::filesystem::path s_ProjectPath;
		inline static Ref<Scene> s_CurrentScene;

		inline static AssetManager s_AssetManager;
	};
}
