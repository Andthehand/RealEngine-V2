#pragma once
#include "ScriptInstance.h"

#pragma warning(push)
#pragma warning(disable : 4146)
#include <Coral/HostInstance.hpp>
#pragma warning(pop)


namespace RealEngine {
	struct ScriptField {
		std::string Name;
		ScriptFieldType Type;
	};

	class ScriptEngine {
	public:
		ScriptEngine(const std::filesystem::path& scriptPath, const std::string& libName);
		~ScriptEngine();

		void UpdateGC();

		Scope<ScriptInstance> CreateObject(UUID entityID, std::string_view className);

		std::vector<std::string> GetValidScriptClasses();
		HashMap<std::string, std::vector<ScriptField>> GetAllClassFields();
	private:
		Coral::HostInstance m_CoralInstance;
		Coral::AssemblyLoadContext m_AppLoadContext;
		Coral::ManagedAssembly m_Assembly;
	};
}
