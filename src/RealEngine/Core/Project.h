#pragma once
#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Scene.h"

#include <filesystem>

namespace RealEngine {

	// Static-only Project manager
	class Project {
	public:
		Project() = delete;

		// Initialize project data (replaces constructor/Create())
		static void Initialize(const std::filesystem::path& filePath);
		static void Shutdown(); // Optional cleanup (clears state)

		static void Save();
		static void Save(const std::string& projectName);

		static Ref<Scene>& GetCurrentScene() { return s_CurrentScene; }
		static void SetCurrentScene(const Ref<Scene>& scene) { s_CurrentScene = scene; }

		static const std::string& GetProjectName() { return s_ProjectName; }
		static const std::filesystem::path& GetProjectPath() { return s_ProjectPath; }
		static std::filesystem::path GetAssetsPath() { return s_ProjectPath / "assets"; }

	private:
		static void Load(const std::filesystem::path& filePath);

	private:
		// Project name is the project file name without extension
		inline static std::string s_ProjectName;
		inline static std::filesystem::path s_ProjectPath;
		inline static Ref<Scene> s_CurrentScene;
	};
}
