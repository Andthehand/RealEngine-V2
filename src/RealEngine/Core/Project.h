#pragma once
#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Scene.h"

#include <filesystem>

namespace RealEngine {
	class Project {
	public:
		Project(const std::filesystem::path& filePath);
		~Project() = default;

		void Save();
		void Save(const std::string& projectName);

		const Ref<Scene>& GetCurrentScene() const { return m_CurrentScene; }
		void SetCurrentScene(const Ref<Scene>& scene) { m_CurrentScene = scene; }

		const std::string& GetProjectName() const { return m_ProjectName; }
		const std::filesystem::path& GetProjectPath() const { return m_ProjectPath; }
		std::filesystem::path GetAssetsPath() const { return m_ProjectPath / "assets"; }

		static Ref<Project> Create(const std::filesystem::path& filePath) { return CreateRef<Project>(filePath); }

	private:
		void Load(const std::filesystem::path& filePath);
	private:
		// Project name is the project file name without extension
		std::string m_ProjectName;
		std::filesystem::path m_ProjectPath;

		Ref<Scene> m_CurrentScene;
	};
}
