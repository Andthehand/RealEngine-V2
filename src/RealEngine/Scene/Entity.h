#pragma once

#include "RealEngine/Scene/Scene.h"

namespace RealEngine {
	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene)
			: m_EntityHandle(handle), m_Scene(scene) {}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			RE_PROFILE_FUNCTION();
			RE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component of type {0}", typeid(T).name());
			
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args) {
			RE_PROFILE_FUNCTION();
			
			return m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent() {
			RE_PROFILE_FUNCTION();
			RE_CORE_ASSERT(HasComponent<T>(), "Entity does not have component of type {0}", typeid(T).name());

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent() {
			RE_PROFILE_FUNCTION();
			RE_CORE_ASSERT(HasComponent<T>(), "Entity does not have component of type {0}", typeid(T).name());

			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() const {
			RE_PROFILE_FUNCTION();
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}
	private:
		Scene* m_Scene;
		entt::entity m_EntityHandle;
	};
}
