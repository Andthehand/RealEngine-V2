#include "ScriptGlue.h"

#include "RealEngine/Scene/Components.h"
#include "RealEngine/Scene/Entity.h"

#include "RealEngine/Core/Project.h"

#define RE_ADD_INTERNAL_CALL(functionName) \
	assembly.AddInternalCall("RealEngine.InternalCalls", #functionName, reinterpret_cast<void*>(&functionName));

namespace RealEngine {
	static std::unordered_map<Coral::Type*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;

	enum class LogLevel {
		Trace = 0,
		Info = 1,
		Warn = 2,
		Error = 3,
		Critical = 4
	};

	static void NativeLog(LogLevel level, Coral::String message) {
		switch (level) {
			case LogLevel::Trace:		RE_TRACE("{}", std::string(message)); break;
			case LogLevel::Info:		RE_INFO("{}", std::string(message)); break;
			case LogLevel::Warn:		RE_WARN("{}", std::string(message)); break;
			case LogLevel::Error:		RE_ERROR("{}", std::string(message)); break;
			case LogLevel::Critical:	RE_CRITICAL("{}", std::string(message)); break;
			default: 
				RE_CORE_ASSERT(false, "Unknown log level!"); 
				break;
		}
	}

	static bool Entity_HasComponent(UUID entityID, Coral::ReflectionType componentReflectionType) {
		RE_PROFILE_FUNCTION();
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		Coral::Type& componentType = componentReflectionType;
		RE_CORE_ASSERT(s_EntityHasComponentFuncs.find(&componentType) != s_EntityHasComponentFuncs.end());
		return s_EntityHasComponentFuncs.at(&componentType)(entity);
	}

	static void TransformComponent_GetTranslation(UUID entityID, glm::vec3* outTranslation) {
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		*outTranslation = entity ? entity.GetComponent<TransformComponent>().GetTransation() : glm::vec3(0.0f);
	}

	static void TransformComponent_SetTranslation(UUID entityID, glm::vec3* translation) {
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		entity.GetComponent<TransformComponent>().SetTransation(*translation);
	}

	static void TransformComponent_GetRotation(UUID entityID, glm::quat* outRotation) {
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		*outRotation = entity ? entity.GetComponent<TransformComponent>().GetRotationQuat() : glm::quat();
	}

	static void TransformComponent_SetRotation(UUID entityID, glm::quat* rotation) {
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		entity.GetComponent<TransformComponent>().SetRotationQuat(*rotation);
	}

	static void TransformComponent_GetScale(UUID entityID, glm::vec3* outScale) {
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		*outScale = entity ? entity.GetComponent<TransformComponent>().GetScale() : glm::vec3(0.0f);
	}

	static void TransformComponent_SetScale(UUID entityID, glm::vec3* scale) {
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		entity.GetComponent<TransformComponent>().SetScale(*scale);
	}

	static void SpriteRendererComponent_GetColor(UUID entityID, glm::vec4* outColor) {
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		*outColor = entity ? entity.GetComponent<SpriteRendererComponent>().Color : glm::vec4(0.0f);
	}

	static void SpriteRendererComponent_SetColor(UUID entityID, glm::vec4* color) {
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		entity.GetComponent<SpriteRendererComponent>().Color = *color;
	}

	void ScriptGlue::RegisterFunctions(Coral::ManagedAssembly& assembly) {
		RegisterComponents(assembly);

		auto types = assembly.GetTypes();
		for (auto& type : types) {
			RE_CORE_INFO("Found script type: {}", std::string(type->GetFullName()));
		}

		RE_ADD_INTERNAL_CALL(Entity_HasComponent);

		//TransformComponent
		RE_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
		RE_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);
		RE_ADD_INTERNAL_CALL(TransformComponent_GetRotation);
		RE_ADD_INTERNAL_CALL(TransformComponent_SetRotation);
		RE_ADD_INTERNAL_CALL(TransformComponent_GetScale);
		RE_ADD_INTERNAL_CALL(TransformComponent_SetScale);
		//TransformComponent

		//SpriteRendererComponent
		RE_ADD_INTERNAL_CALL(SpriteRendererComponent_GetColor);
		RE_ADD_INTERNAL_CALL(SpriteRendererComponent_SetColor);
		//SpriteRendererComponent

		RE_ADD_INTERNAL_CALL(NativeLog);

		assembly.UploadInternalCalls();
	}

	template<typename... Component>
	static void RegisterComponent(Coral::ManagedAssembly& assembly) {
		RE_PROFILE_FUNCTION();

		([&]() {
			std::string componentTypeName = std::string("RealEngine.") + Component::GetName();

			Coral::Type& componentType = assembly.GetType(componentTypeName);
			RE_CORE_ASSERT(componentType);
			s_EntityHasComponentFuncs[&componentType] = [](Entity entity) { return entity.HasComponent<Component>(); };
			}(), ...);
	}

	template<typename... Component>
	static void RegisterComponent(Coral::ManagedAssembly& assembly, ComponentList::ComponentGroup<Component...>) {
		RE_PROFILE_FUNCTION();

		RegisterComponent<Component...>(assembly);
	}

	void ScriptGlue::RegisterComponents(Coral::ManagedAssembly& assembly) {
		RE_PROFILE_FUNCTION();

		s_EntityHasComponentFuncs.clear();
		RegisterComponent(assembly, ComponentList::GetAllComponents());
	}
}