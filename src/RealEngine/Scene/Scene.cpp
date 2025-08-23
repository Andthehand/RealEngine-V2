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

		{
			RE_PROFILE_SCOPE("Draw Quads");
			
			auto view = m_Registry.view<TransformComponent>();
			for (auto entity : view) {
				auto& transform = view.get<TransformComponent>(entity);
				Renderer::DrawQuad(transform.Position);
			}
		}

	}

	Entity Scene::CreateEntity(const std::string& name) {
		RE_PROFILE_FUNCTION();

		UUID entityID;
		Entity entity = CreateEntity(entityID, name);

		return entity;
	}

	Entity Scene::CreateEntity(UUID id, const std::string& name) {
		Entity entity(m_Registry.create(), this);
		entity.AddComponent<IDComponent>(id);
		entity.AddComponent<TagComponent>(name);

		// Add to lookup for later retrieval
		m_EntityMap.insert({ id, entity });
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

		// Create the root node
		ryml::Tree tree;
		ryml::NodeRef root = tree.rootref();
		root |= ryml::MAP;

		// Create the Entities node
		ryml::NodeRef entitiesNode = root["Entities"];
		entitiesNode |= ryml::MAP;

		// Serialize each entity
		for (entt::entity entity : m_Registry.view<entt::entity>()) {
			Entity ent(entity, this);
			
			// The root node for each entity is the tag component name
			std::string entityTag = ent.GetComponent<TagComponent>().Tag;
			ryml::NodeRef entityNode = entitiesNode.append_child() << ryml::key(entityTag);
			entityNode |= ryml::MAP;

			// Done seperatly because you need the UUID when deserializing to register the entity
			SerializeComponent<IDComponent>(entityNode, ent); 

			SerializeComponents(ComponentList::GetAllComponents(), ent, entityNode);
		}

		// Write to file
		FileHelper fileHelper(filepath, "w");
		FILE* file = fileHelper.GetFileHandle();
		ryml::emit_yaml(tree, file);

		RE_CORE_WARN("Scene was serialized into {}", filepath);
	}

	void Scene::Deserialize(const std::filesystem::path& filepath) {
		RE_PROFILE_FUNCTION();
		RE_CORE_ASSERT(std::filesystem::exists(filepath), "Scene file does not exist: {0}", filepath.string());

		RE_CORE_WARN("Deserializing scene from {0}", filepath.string());

		// Read in file
		FileHelper fileHelper(filepath, "r");
		std::string fileContents = fileHelper.ReadAllText();

		// Parse the YAML file
		ryml::Tree tree = ryml::parse_in_place(ryml::to_csubstr(filepath.filename().string()), ryml::to_substr(fileContents));
		RE_CORE_ASSERT(!tree.empty(), "Failed to parse scene file: Tree is empty");

		ryml::ConstNodeRef root = tree.crootref();
		ryml::ConstNodeRef entitiesNode = root["Entities"];
		RE_CORE_ASSERT(entitiesNode.is_map(), "Invalid scene file format: 'Entities' node is not a map");

		// Deserialize each entity
		for (ryml::ConstNodeRef entityNode : entitiesNode.children()) {
			c4::csubstr entityTag = entityNode.key();
			std::string entityTagStr(entityTag.str, entityTag.len);

			RE_CORE_INFO("Deserializing entity '{0}'", entityTagStr);

			// Get the IDComponent early to create the entity
			if(entityNode.has_child("IDComponent")) {
				const auto componentNode = entityNode[IDComponent::GetName()];

				IDComponent idComponent;
				componentNode >> idComponent;
				Entity entity = CreateEntity(idComponent.ID, entityTagStr);
				
				DeserializeComponents(ComponentList::GetAllComponents(), entity, entityNode);
			}
			else {
                RE_CORE_ASSERT(false, "Error deserializing scene: IDComponent missing for entity '{}'", entityTagStr);
			}
		}
	}
}
