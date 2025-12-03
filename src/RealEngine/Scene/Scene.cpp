#include "Scene.h"

#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Components.h"
#include "RealEngine/Scene/ComponentSerializer.h"

#include "RealEngine/Types/HashMap.h"

#include <ryml.hpp>

namespace RealEngine {
	namespace Utils {
		template<typename... Component>
		static void CopyComponent(entt::registry& dst, entt::registry& src, const HashMap<UUID, entt::entity>& enttMap) {
			RE_PROFILE_FUNCTION();

			([&]() {
				auto view = src.view<Component>();
				for (auto srcEntity : view) {
					entt::entity dstEntity = enttMap.at(src.get<IDComponent>(srcEntity).ID);

					auto& srcComponent = src.get<Component>(srcEntity);
					dst.emplace_or_replace<Component>(dstEntity, srcComponent);
				}
				}(), ...);
		}

		template<typename... Component>
		static void CopyComponent(ComponentList::ComponentGroup<Component...>, entt::registry& dst, entt::registry& src, const HashMap<UUID, entt::entity>& enttMap) {
			RE_PROFILE_FUNCTION();

			CopyComponent<Component...>(dst, src, enttMap);
		}

		template<typename... Component>
		static void CopyComponentIfExists(Entity dst, Entity src) {
			RE_PROFILE_FUNCTION();

			([&]() {
				if (src.HasComponent<Component>())
					dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
				}(), ...);
		}

		template<typename... Component>
		static void CopyComponentIfExists(ComponentList::ComponentGroup<Component...>, Entity dst, Entity src) {
			CopyComponentIfExists<Component...>(dst, src);
		}
	}

	Scene::Scene(const std::filesystem::path& filepath)
		: m_SceneRenderer(this) {
		RE_PROFILE_FUNCTION();

		Load(filepath);
	}

	Scene::Scene()
		: m_SceneRenderer(this) { }

	Ref<Scene> Scene::Copy(Ref<Scene> other) {
		RE_PROFILE_FUNCTION();

		Ref<Scene> newScene = CreateRef<Scene>();

		auto& srcSceneRegistry = other->m_Registry;
		auto& dstSceneRegistry = newScene->m_Registry;
		HashMap<UUID, entt::entity> enttMap;

		// Create entities in new scene
		auto idView = srcSceneRegistry.view<IDComponent>();
		for (auto entity : idView) {
			UUID uuid = srcSceneRegistry.get<IDComponent>(entity).ID;
			const auto& name = srcSceneRegistry.get<TagComponent>(entity).Tag;
			Entity newEntity = newScene->CreateEntity(uuid, name);
			enttMap[uuid] = (entt::entity)newEntity;
		}

		Utils::CopyComponent(ComponentList::GetAllComponents(), dstSceneRegistry, srcSceneRegistry, enttMap);

		return newScene;
	}

	void Scene::OnRuntimeStart() {
		RE_PROFILE_FUNCTION();
		m_IsRunning = true;

		auto view = m_Registry.view<IDComponent, ScriptComponent>();
		for (auto entity : view) {
			auto [id, script] = view.get<IDComponent, ScriptComponent>(entity);

			script.Instance = Project::GetScriptEngine()->CreateObject(id.ID, script.ClassName);
		}
	}

	void Scene::OnRuntimeStop() {
		RE_PROFILE_FUNCTION();
		m_IsRunning = false;

		Project::GetScriptEngine()->UpdateGC();
	}

	void Scene::OnUpdateEditor(float deltaTime, const EditorCamera& camera) {
		RE_PROFILE_FUNCTION();

		RenderScene(camera.GetViewProjection());
	}

	void Scene::OnUpdateRuntime(float deltaTime, const EditorCamera& camera) {
		RE_PROFILE_FUNCTION();

		// TODO: Add a runtime camera
		RenderScene(camera.GetViewProjection());
	}

	void Scene::RenderScene(const glm::mat4 cameraProjection) {
		RE_PROFILE_FUNCTION();

		{
			RE_PROFILE_SCOPE("Draw Sprites");
			m_SceneRenderer.OnRender(cameraProjection);
		}
	}

	Entity Scene::CreateEntity(std::string_view name) {
		RE_PROFILE_FUNCTION();

		UUID entityID;
		Entity entity = CreateEntity(entityID, name);

		return entity;
	}

	Entity Scene::CreateEntity(UUID id, std::string_view name) {
		Entity entity(m_Registry.create(), this);
		entity.AddComponent<IDComponent>(id);
		entity.AddComponent<TagComponent>(name);

		// Add to lookup for later retrieval
		m_EntityMap.insert({ id, entity });
		return entity;
	}

	Entity Scene::CloneEntity(const Entity& entity) {
		RE_PROFILE_FUNCTION();

		std::string_view name = entity.GetName();
		Entity newEntity = CreateEntity(name);
		Utils::CopyComponentIfExists(ComponentList::GetAllComponents(), newEntity, entity);

		return newEntity;
	}

	void Scene::DestroyEntity(const Entity& entity) {
		RE_PROFILE_FUNCTION();
		UUID id = entity.GetComponent<IDComponent>().ID;

		// Remove from lookup
		m_Registry.destroy(entity);
		m_EntityMap.erase(id);
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

	void Scene::Save() {
		RE_PROFILE_FUNCTION();
		if (m_FilePath.empty()) {
			RE_CORE_ERROR("Scene file path is empty!");
			return;
		}

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
		FileHelper fileHelper(m_FilePath, "w");
		FILE* file = fileHelper.GetFileHandle();
		ryml::emit_yaml(tree, file);

		RE_CORE_INFO("Scene was serialized into {}", m_FilePath);
	}

	void Scene::Load(const std::filesystem::path& filePath) {
		RE_PROFILE_FUNCTION();
		RE_CORE_ASSERT(std::filesystem::is_regular_file(filePath), "Scene file does not exist: {0}", filePath.string());
		m_FilePath = filePath;

		RE_CORE_INFO("Deserializing scene from {0}", m_FilePath.string());

		// Read in file
		FileHelper fileHelper(m_FilePath, "r");
		std::string fileContents = fileHelper.ReadAllText();

		// Parse the YAML file
		ryml::Tree tree = ryml::parse_in_place(ryml::to_csubstr(m_FilePath.filename().string()), ryml::to_substr(fileContents));
		RE_CORE_ASSERT(!tree.empty(), "Failed to parse scene file: Tree is empty");

		ryml::ConstNodeRef root = tree.crootref();
		ryml::ConstNodeRef entitiesNode = root["Entities"];
		RE_CORE_ASSERT(entitiesNode.is_map(), "Invalid scene file format: 'Entities' node is not a map");

		// Deserialize each entity
		for (ryml::ConstNodeRef entityNode : entitiesNode.children()) {
			c4::csubstr entityTag = entityNode.key();
			std::string entityTagStr(entityTag.str, entityTag.len);

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
