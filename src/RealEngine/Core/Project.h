#pragma once
#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Scene.h"
#include "RealEngine/Asset/AssetManager.h"
#include "RealEngine/Scripting/ScriptEngine.h"

#include <filesystem>

namespace RealEngine {
	/**
	 * @class Project
	 * @brief Static-only class that manages all project-level data in RealEngine.
	 *
	 * The Project class is responsible for creating, loading, and saving project files,
	 * as well as managing the currently active scene and asset manager. It provides
	 * static accessors and utility methods to interact with the current project context.
	 *
	 * Since all members and methods are static, this class cannot be instantiated.
	 */
	class Project {
	public:
		/** @brief Deleted constructor to prevent instantiation. */
		Project() = delete;

		//-------------------------------------------------------------------------
		// Project Lifecycle
		//-------------------------------------------------------------------------

		/**
		 * @brief Initializes a new empty project in memory.
		 *
		 * This sets up a default project state with an empty name and new scene,
		 * but does not save anything to disk.
		 */
		static void CreateNewProject();

		/**
		 * @brief Clears all project data.
		 *
		 * Resets static variables, unloads the current scene, and clears assets.
		 * Effectively acts as a destructor for static project data.
		 */
		static void ClearProject();

		/**
		 * @brief Loads an existing project from a file.
		 * @param filePath Path to the `.reproj` project file.
		 *
		 * Reads project metadata, restores the project path and name, and loads
		 * the current scene and asset data.
		 */
		static void Load(const std::filesystem::path& filePath);

		/**
		 * @brief Saves the current project using its existing name and path.
		 *
		 * If the project is not yet initialized, prompts the user for a save location.
		 */
		static void Save();

		/**
		 * @brief Saves the current project under a specified name.
		 * @param projectName The desired project name (without extension).
		 */
		static void Save(const std::string& projectName);

		//-------------------------------------------------------------------------
		// Getters
		//-------------------------------------------------------------------------

		static Ref<Scene>& GetCurrentScene() { return s_CurrentScene; }

		/**
		 * @brief Sets the currently active scene.
		 * @param scene Reference to the scene to activate.
		 *
		 * Also clears unused assets from the asset manager when switching scenes.
		 */
		static void SetCurrentScene(const Ref<Scene>& scene);

		/**
		 * @brief Provides access to the global asset manager.
		 * @return Reference to the static AssetManager instance.
		 */
		static AssetManager& GetAssetManager() { return s_AssetManager; }
		
		//-------------------------------------------------------------------------
		// Project Metadata Accessors
		//-------------------------------------------------------------------------

		/**
		 * @brief Gets the current project name.
		 * @return The project name as a string reference.
		 */
		static const std::string& GetProjectName() { return s_ProjectName; }

		/**
		 * @brief Gets the absolute path to the current project folder.
		 * @return The project path as a std::filesystem::path reference.
		 */
		static const std::filesystem::path& GetProjectPath() { return s_ProjectPath; }

		/**
		 * @brief Gets the absolute path to the project's asset folder.
		 * @return Path to the "assets" subfolder of the project directory.
		 */
		static std::filesystem::path GetAssetsPath() { return s_ProjectPath / "assets"; }

		static std::filesystem::path GetScriptsPath() { return GetAssetsPath() / "Scripts"; }


		//-------------------------------------------------------------------------
		// Path Utilities
		//-------------------------------------------------------------------------

		/**
		 * @brief Converts an absolute path into a path relative to the asset folder.
		 * @param absolutePath Absolute path to a file within the project.
		 * @return Path relative to the "assets" directory.
		 */
		static std::filesystem::path GetRelativePathToAssetFolder(const std::filesystem::path& absolutePath);

		/**
		 * @brief Resolves a relative asset path to an absolute one.
		 * @param relativePath Path relative to the asset directory.
		 * @return Absolute filesystem path to the asset.
		 */
		static std::filesystem::path ResolveAssetPathFromAssetFolder(const std::filesystem::path& relativePath);

		//-------------------------------------------------------------------------
		// Status Checks
		//-------------------------------------------------------------------------

		/**
		 * @brief Checks whether the project has been fully initialized.
		 * @return True if the project path is set, false otherwise.
		 */
		static bool IsFullyInitialized() { return !s_ProjectPath.empty(); }

	private:
		/**
		 * @brief Sets up internal state for a new project given its file path.
		 * @param projectFilePath Path to the project file (.reproj).
		 *
		 * Extracts the project name, initializes directories, and prepares
		 * the environment for scene and asset loading.
		 */
		static void SetupProject(const std::filesystem::path& projectFilePath);

	private:
		// Project metadata
		inline static std::string s_ProjectName;
		inline static std::filesystem::path s_ProjectPath;
		inline static Ref<Scene> s_CurrentScene;

		// Asset management
		inline static AssetManager s_AssetManager;
	};
}
