#pragma once

#pragma warning(push)
#pragma warning(disable : 4146)
#include <Coral/HostInstance.hpp>
#pragma warning(pop)

namespace RealEngine {
	class ScriptEngine {
	public:
		static void Init();
		static void Shutdown();

	private:
		static inline Coral::HostInstance s_CoralInstance;
		static inline Coral::AssemblyLoadContext s_AppLoadContext;
	};
}
