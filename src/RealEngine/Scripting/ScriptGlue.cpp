#include "ScriptGlue.h"

namespace RealEngine {
	static void NativeLog(Coral::String message) {
		RE_WARN("{}", std::string(message));
	}

	void ScriptGlue::RegisterFunctions(Coral::ManagedAssembly& assembly) {
		assembly.AddInternalCall("RealEngine.InternalCalls", "NativeLog", reinterpret_cast<void*>(&NativeLog));

		assembly.UploadInternalCalls();
	}
}