#pragma once
#include <Coral/ManagedObject.hpp>

namespace RealEngine {
	enum class ScriptFieldType {
		Unknown = 0,

		Float, Double,
		Bool, String, Char, Byte, Short, Int, Long,
		UByte, UShort, UInt, ULong,
		Vector2, Vector3, Vector4,
		Color,
		Entity
	};

	class ScriptInstance {
	public:
		ScriptInstance() = delete;
		ScriptInstance(Coral::ManagedObject&& instance) noexcept : m_Instance(std::move(instance)) {}
		~ScriptInstance() {
			RE_CORE_INFO("ScriptInstance destroyed");
		}

		void InvokeOnCreate();
		void InvokeOnUpdate(float deltaTime);

		template<typename T>
		T GetFieldValue(std::string_view name) {
			return m_Instance.GetFieldValue<T>(name);
		}

		template<typename T>
		void SetFieldValue(std::string_view name, T value) {
			m_Instance.SetFieldValue<T>(name, value);
		}
	private:
		Coral::ManagedObject m_Instance;
	};
}