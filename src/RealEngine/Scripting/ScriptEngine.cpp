#include "ScriptEngine.h"

#include "ScriptGlue.h"
#include "RealEngine/Core/Project.h"

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
		Coral::HostSettings settings = {
			.CoralDirectory = CORAL_DIRECTORY,
			.MessageCallback = DefaultMessageCallback,
			.MessageFilter = Coral::MessageLevel::All,
			.ExceptionCallback = ExceptionCallback
		};

		s_CoralInstance.Initialize(settings);

		// Testing
		s_AppLoadContext = s_CoralInstance.CreateAssemblyLoadContext("AppContext");
		
		// Load RealEngine assembly first to register internal calls
		std::filesystem::path realEngineAssemblyPath = Project::GetAssetsPath() / "Scripts" / "Build" / "Debug" / "RealEngine.dll";
		Coral::ManagedAssembly& realEngineAssembly = s_AppLoadContext.LoadAssembly(realEngineAssemblyPath.string());
		ScriptGlue::RegisterFunctions(realEngineAssembly);

		std::filesystem::path assemblyPath = Project::GetAssetsPath() / "Scripts" / "Build" / "Debug" / "Example.Managed.dll";
		s_Assembly = s_AppLoadContext.LoadAssembly(assemblyPath.string());
		Coral::Type& exampleType = s_Assembly.GetType("Example.Managed.ExampleClass");
		exampleType.CreateInstance(50);
	}
	void ScriptEngine::Shutdown() {
		s_CoralInstance.UnloadAssemblyLoadContext(s_AppLoadContext);
		s_CoralInstance.Shutdown();
	}
}
