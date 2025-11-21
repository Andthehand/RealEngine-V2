#pragma once

#pragma warning(push)
#pragma warning(disable : 4146)
#include <Coral/HostInstance.hpp>
#pragma warning(pop)

namespace RealEngine {
	class ScriptEngine {
	public:
		ScriptEngine(const std::filesystem::path& scriptPath, const std::string& libName);
		~ScriptEngine();

		Coral::ManagedObject CreateObject(uint64_t entityID, std::string_view className);

		std::vector<std::string> GetValidScriptClasses();
	private:
		Coral::HostInstance m_CoralInstance;
		Coral::AssemblyLoadContext m_AppLoadContext;
		Coral::ManagedAssembly m_Assembly;
	};
}
