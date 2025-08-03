#pragma once

#include "RealEngine/Types/UUID.h"

#include <entt/entt.hpp>

namespace RealEngine {
	class Entity;

	class Scene {
	public:
		Scene(const std::filesystem::path& filepath);
		Scene() = default;
		~Scene() = default;

		void OnUpdate(float deltaTime);

		Entity CreateEntity(std::string name);
		Entity GetEntity(UUID id);

		void Serialize(const std::filesystem::path& filepath);
		void Deserialize(const std::filesystem::path& filepath);

		template<typename T>
		auto GetAllEntitiesWithComponent() {
			return m_Registry.view<T>();
		}
	private:
		entt::registry m_Registry;
		std::unordered_map<UUID, Entity> m_EntityMap;
		
		friend class Entity;
	};
}
