#include "ScriptEngine.h"

#include "ScriptGlue.h"
#include "RealEngine/Core/Project.h"

#include <Coral/TypeCache.hpp>
#include <Coral/GC.hpp>

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

	ScriptEngine::ScriptEngine(const std::filesystem::path& scriptPath, const std::string& libName) {
		RE_PROFILE_FUNCTION();

		Coral::HostSettings settings = {
			.CoralDirectory = (scriptPath).string(),
			.MessageCallback = DefaultMessageCallback,
			.MessageFilter = Coral::MessageLevel::All,
			.ExceptionCallback = ExceptionCallback
		};

		if (m_CoralInstance.Initialize(settings) != Coral::CoralInitStatus::Success) {
			RE_CORE_ASSERT(false, "Coral failed to initialize");
			return;
		}

		m_AppLoadContext = m_CoralInstance.CreateAssemblyLoadContext("AppContext");
		
		// Load RealEngine assembly first to register internal calls
		std::filesystem::path realEngineAssemblyPath = scriptPath / "RealEngine.dll";
		Coral::ManagedAssembly& realEngineAssembly = m_AppLoadContext.LoadAssembly(realEngineAssemblyPath.string());
		ScriptGlue::RegisterFunctions(realEngineAssembly);

		std::filesystem::path assemblyPath = scriptPath / (libName + ".dll");
		m_Assembly = m_AppLoadContext.LoadAssembly(assemblyPath.string());
	}

	ScriptEngine::~ScriptEngine() {
		RE_PROFILE_FUNCTION();

		m_CoralInstance.UnloadAssemblyLoadContext(m_AppLoadContext);
		m_CoralInstance.Shutdown();
	}

	void ScriptEngine::UpdateGC() {
		RE_PROFILE_FUNCTION();

		Coral::GC::Collect();
		Coral::GC::WaitForPendingFinalizers();
	}

	Coral::ManagedObject ScriptEngine::CreateObject(UUID entityID, std::string_view className) {
		RE_PROFILE_FUNCTION();

		Coral::Type& entityType = m_Assembly.GetType(className);
		if (entityType) {
			Coral::ManagedObject entityObject = entityType.CreateInstance((uint64_t)entityID);
			entityObject.InvokeMethod("OnCreate");

			return entityObject;
		}
		else {
			RE_CORE_ERROR("Failed to create script object of class '{0}' - class not found! (Maybe Renamed?)", className);

			return Coral::ManagedObject();
		}
	}

	std::vector<std::string> ScriptEngine::GetValidScriptClasses() {
		RE_PROFILE_FUNCTION();

		std::vector<std::string> classNames;
		Coral::Type entityType = *Coral::TypeCache::Get().GetTypeByName("RealEngine.Entity");

		for (const Coral::Type* type : m_Assembly.GetTypes()) {
			if (type->IsSubclassOf(entityType)) {
				classNames.push_back(std::string(type->GetFullName()));
			}
		}

		return classNames;
	}
}
