#include "Scene.h"

#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Components.h"
#include "RealEngine/Scene/ComponentSerializer.h"

#include "RealEngine/Render/Renderer.h"

#include <ryml.hpp>

namespace RealEngine {
	Scene::Scene(const std::filesystem::path& filepath) {
		RE_PROFILE_FUNCTION();

		Deserialize(filepath);
	}

	void Scene::OnUpdate(float deltaTime) {
		RE_PROFILE_FUNCTION();

		Serialize("temp.yaml");
		{
			RE_PROFILE_SCOPE("Draw Quads");
			
			auto view = m_Registry.view<TransformComponent>();
			for (auto entity : view) {
				auto& transform = view.get<TransformComponent>(entity);
				Renderer::DrawQuad(transform.Position);
			}
		}

	}

	Entity Scene::CreateEntity(std::string name) {
		RE_PROFILE_FUNCTION();

		UUID entityID;
		Entity entity(m_Registry.create(), this);
		entity.AddComponent<IDComponent>(entityID);
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>(glm::vec3(0.0f));

        m_EntityMap.insert({ entityID, entity });
		return entity;
	}

	Entity Scene::GetEntity(UUID id) {
		RE_PROFILE_FUNCTION();

		auto it = m_EntityMap.find(id);
		if (it != m_EntityMap.end()) {
			return it->second;
		}

		RE_CORE_ERROR("Entity with ID {0} not found", id);
		return Entity();
	}



	void Scene::Serialize(const std::filesystem::path& filepath) {
		RE_PROFILE_FUNCTION();

		ryml::Tree tree;
		ryml::NodeRef root = tree.rootref();
		root |= ryml::MAP; // mark root as a map
		ryml::NodeRef entitiesNode = root["Entities"];
		entitiesNode |= ryml::MAP;

		for (entt::entity entity : m_Registry.view<entt::entity>()) {
			Entity ent(entity, this);
			SerializeComponents(ComponentList::GetAllComponents(), ent, entitiesNode);
		}

		FILE* file = nullptr;
		fopen_s(&file, filepath.string().c_str(), "wb");
		ryml::emit_yaml(tree, file);

		if (file) {
			std::fclose(file);
		}
		else {
			RE_CORE_ASSERT(false, "Failed to open file");
		}
	}

	void Scene::Deserialize(const std::filesystem::path& filepath) {

	}
}
