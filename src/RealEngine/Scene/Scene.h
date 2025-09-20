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

		void OnUpdateEditor(float deltaTime, const EditorCamera& camera);
		void OnUpdateRuntime(float deltaTime);

		void RenderScene(const glm::mat4 cameraProjection);

		Entity CreateEntity(const std::string& name);
		Entity CreateEntity(UUID id, const std::string& name);

		// Returns the iterator to the next element after the erased one
		void DestroyEntity(const Entity& entity);

		Entity GetEntity(UUID id);

		void Serialize(const std::filesystem::path& filepath);
		void Deserialize(const std::filesystem::path& filepath);

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

		SceneRenderer m_SceneRenderer;
		
		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}
