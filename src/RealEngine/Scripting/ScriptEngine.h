#pragma once

#pragma warning(push)
#pragma warning(disable : 4146)
#include <Coral/HostInstance.hpp>
#pragma warning(pop)

namespace RealEngine {
	class ScriptEngine {
	public:
		ScriptEngine() = delete;

		static void Init();
		static void Shutdown();

		static Coral::ManagedObject CreateObject(uint64_t entityID, std::string_view className);

		static std::vector<std::string> GetValidScriptClasses();
	private:
		static inline Coral::HostInstance s_CoralInstance;
		static inline Coral::AssemblyLoadContext s_AppLoadContext;
		static inline Coral::ManagedAssembly s_Assembly;

		static inline bool isInitialized = false;
	};
}
