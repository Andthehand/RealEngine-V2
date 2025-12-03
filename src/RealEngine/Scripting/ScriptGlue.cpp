#include "ScriptGlue.h"

#include "RealEngine/Scene/Components.h"
#include "RealEngine/Scene/Entity.h"

#include "RealEngine/Core/Project.h"

#define RE_ADD_INTERNAL_CALL(functionName) \
	assembly.AddInternalCall("RealEngine.InternalCalls", #functionName, reinterpret_cast<void*>(&functionName));

namespace RealEngine {
	struct ComponentFuncs {
		std::function<bool(Entity)> HasComponent;
		std::function<void*(Entity)> GetComponent;
		std::function<void*(Entity)> AddComponent;
	};
	static HashMap<Coral::Type*, ComponentFuncs> s_EntityComponentFuncs;

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
		RE_CORE_ASSERT(s_EntityComponentFuncs.find(&componentType) != s_EntityComponentFuncs.end());
		return s_EntityComponentFuncs.at(&componentType).HasComponent(entity);
	}

	static void* Entity_GetComponent(UUID entityID, Coral::ReflectionType componentReflectionType) {
		RE_PROFILE_FUNCTION();
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		Coral::Type& componentType = componentReflectionType;
		RE_CORE_ASSERT(s_EntityComponentFuncs.find(&componentType) != s_EntityComponentFuncs.end());
		return s_EntityComponentFuncs.at(&componentType).GetComponent(entity);
	}

	static void* Entity_AddComponent(UUID entityID, Coral::ReflectionType componentReflectionType) {
		RE_PROFILE_FUNCTION();
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		Coral::Type& componentType = componentReflectionType;
		RE_CORE_ASSERT(s_EntityComponentFuncs.find(&componentType) != s_EntityComponentFuncs.end());
		return s_EntityComponentFuncs.at(&componentType).AddComponent(entity);
	}

	static UUID Entity_Instantiate(UUID entityID) {
		RE_PROFILE_FUNCTION();
		Ref<Scene> scene = Project::GetCurrentScene();
		RE_CORE_ASSERT(scene);
		Entity entity = scene->GetEntity(entityID);
		RE_CORE_ASSERT(entity);

		return scene->CloneEntity(entity).GetUUID();
	}

	void ScriptGlue::RegisterFunctions(Coral::ManagedAssembly& assembly) {
		RegisterComponents(assembly);

		RE_ADD_INTERNAL_CALL(Entity_HasComponent);
		RE_ADD_INTERNAL_CALL(Entity_GetComponent);
		RE_ADD_INTERNAL_CALL(Entity_AddComponent);
		RE_ADD_INTERNAL_CALL(Entity_Instantiate);

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
			auto& funcs = s_EntityComponentFuncs[&componentType];
			funcs.HasComponent = [](Entity entity) { return entity.HasComponent<Component>(); };
			funcs.GetComponent = [](Entity entity) { return entity.TryGetComponent<Component>(); };
			funcs.AddComponent = [](Entity entity) { return &entity.AddOrReplaceComponent<Component>(); };
		}(), ...);
	}

	template<typename... Component>
	static void RegisterComponent(Coral::ManagedAssembly& assembly, ComponentList::ComponentGroup<Component...>) {
		RE_PROFILE_FUNCTION();

		RegisterComponent<Component...>(assembly);
	}

	void ScriptGlue::RegisterComponents(Coral::ManagedAssembly& assembly) {
		RE_PROFILE_FUNCTION();

		s_EntityComponentFuncs.clear();
		RegisterComponent(assembly, ComponentList::GetAllComponents());
	}
}