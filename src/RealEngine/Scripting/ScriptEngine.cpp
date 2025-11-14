#include "ScriptEngine.h"

#include "ScriptGlue.h"
#include "RealEngine/Core/Project.h"

#include <Coral/TypeCache.hpp>

namespace RealEngine {
	static void ExceptionCallback(std::string_view InMessage) {
		RE_CORE_ASSERT(false, "Unhandled native exception: {0}", InMessage);
	}

	static void DefaultMessageCallback(std::string_view InMessage, Coral::MessageLevel InLevel) {
		switch (InLevel) {
			case Coral::MessageLevel::Trace:
				RE_CORE_TRACE("{0}", InMessage);
				break;
			case Coral::MessageLevel::Info:
				RE_CORE_INFO("{0}", InMessage);
				break;
			case Coral::MessageLevel::Warning:
				RE_CORE_WARN("{0}", InMessage);
				break;
			case Coral::MessageLevel::Error:
				RE_CORE_ERROR("{0}", InMessage);
				break;
			default:
				RE_CORE_ASSERT(false, "Unknown message level!");
				break;
		}
	}

	void ScriptEngine::Init() {
		RE_PROFILE_FUNCTION();
		std::filesystem::path projectScriptsPath = Project::GetScriptsPath() / "Build";

		Coral::HostSettings settings = {
			.CoralDirectory = (projectScriptsPath).string(),
			.MessageCallback = DefaultMessageCallback,
			.MessageFilter = Coral::MessageLevel::All,
			.ExceptionCallback = ExceptionCallback
		};

		if (s_CoralInstance.Initialize(settings) != Coral::CoralInitStatus::Success) {
			RE_CORE_ASSERT(false, "Coral failed to initialize");
			return;
		}

		s_AppLoadContext = s_CoralInstance.CreateAssemblyLoadContext("AppContext");
		
		// Load RealEngine assembly first to register internal calls
		std::filesystem::path realEngineAssemblyPath = projectScriptsPath / "RealEngine.dll";
		Coral::ManagedAssembly& realEngineAssembly = s_AppLoadContext.LoadAssembly(realEngineAssemblyPath.string());
		ScriptGlue::RegisterFunctions(realEngineAssembly);

		std::filesystem::path assemblyPath = projectScriptsPath / (Project::GetProjectName() + ".dll");
		s_Assembly = s_AppLoadContext.LoadAssembly(assemblyPath.string());

		isInitialized = true;
	}

	void ScriptEngine::Shutdown() {
		if (isInitialized) {
			s_CoralInstance.UnloadAssemblyLoadContext(s_AppLoadContext);
			s_CoralInstance.Shutdown();

			isInitialized = false;
		}
	}

	Coral::ManagedObject ScriptEngine::CreateObject(uint64_t entityID, std::string_view className) {
		Coral::ManagedObject entityObject = s_Assembly.GetType(className).CreateInstance(entityID);
		entityObject.InvokeMethod("OnCreate");

		return entityObject;
	}

	std::vector<std::string> ScriptEngine::GetValidScriptClasses() {
		std::vector<std::string> classNames;
		Coral::Type entityType = *Coral::TypeCache::Get().GetTypeByName("RealEngine.Entity");

		for (const Coral::Type* type : s_Assembly.GetTypes()) {
			if (type->IsSubclassOf(entityType)) {
				classNames.push_back(std::string(type->GetFullName()));
			}
		}

		return classNames;
	}
}
