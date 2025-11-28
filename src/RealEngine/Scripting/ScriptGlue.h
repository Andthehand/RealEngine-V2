#pragma once

#include <Coral/Assembly.hpp>

namespace RealEngine {
	class ScriptGlue {
	public:
		static void RegisterFunctions(Coral::ManagedAssembly& assembly);
	private:
		static void RegisterComponents(Coral::ManagedAssembly& assembly);
	};
}