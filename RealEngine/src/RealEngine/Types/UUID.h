#pragma once

namespace RealEngine{
	class UUID {
	public:
		UUID();

		operator uint64_t() const { return m_UUID; }

		bool operator==(const UUID& other) const { return m_UUID == other.m_UUID; }
		bool operator!=(const UUID& other) const { return m_UUID != other.m_UUID; }
	private:
		uint64_t m_UUID;
	};
}

namespace std {
	template<>
	struct hash<RealEngine::UUID> {
		std::size_t operator()(const RealEngine::UUID& uuid) const {
			return (uint64_t)uuid;
		}
	};
}