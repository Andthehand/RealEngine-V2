#pragma once

#include "RealEngine/Render/EditorCamera.h"
#include "RealEngine/Render/SceneRenderer.h"

#include "RealEngine/Types/UUID.h"

#include <entt/entt.hpp>

namespace RealEngine {
	class Entity;

	class Scene {
	public:
		Scene(const std::filesystem::path& filepath);
		Scene();
		~Scene() = default;

		static Ref<Scene> Copy(Ref<Scene> other);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnUpdateEditor(float deltaTime, const EditorCamera& camera);

		// TODO: Remove camera parameter, use camera component from scene
		void OnUpdateRuntime(float deltaTime, const EditorCamera& camera);

		void RenderScene(const glm::mat4 cameraProjection);

		Entity CreateEntity(const std::string& name);
		Entity CreateEntity(UUID id, const std::string& name);

		// Returns the iterator to the next element after the erased one
		void DestroyEntity(const Entity& entity);

		Entity GetEntity(UUID id);

		void SetFilePath(const std::filesystem::path& filePath) { m_FilePath = filePath; }
		const std::filesystem::path& GetFilePath() const { return m_FilePath; }

		void Save();
		void Load(const std::filesystem::path& filePath);

		template<typename T>
		auto GetAllEntitiesWithComponent() {
			return m_Registry.view<T>();
		}

		template<typename... Component>
		auto GetAllEntitiesWithComponents() {
			return m_Registry.group<Component...>();
		}

	private:
		entt::registry m_Registry;
		std::unordered_map<UUID, Entity> m_EntityMap;

		std::filesystem::path m_FilePath;

		SceneRenderer m_SceneRenderer;
		
		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}
