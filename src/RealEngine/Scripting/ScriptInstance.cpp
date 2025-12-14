#include "ScriptInstance.h"

namespace RealEngine {
	void ScriptInstance::InvokeOnCreate() {
		m_Instance.InvokeMethod("OnCreate");
	}

	void ScriptInstance::InvokeOnUpdate(float deltaTime) {
		m_Instance.InvokeMethod("OnUpdate", deltaTime);
	}
}