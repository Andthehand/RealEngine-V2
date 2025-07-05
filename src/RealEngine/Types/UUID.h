#pragma once

namespace RealEngine{
	/**
	 * @class UUID
	 * @brief Represents a universally unique identifier using a 64-bit unsigned integer.
	 *
	 * Provides comparison operators and conversion to uint64_t.
	 */
	class UUID {
	public:
		UUID();

		/**
		 * @brief Conversion operator to uint64_t.
		 * @return The 64-bit unsigned integer representation of the UUID.
		 */
		operator uint64_t() const { return m_UUID; }

		bool operator==(const UUID& other) const { return m_UUID == other.m_UUID; }
		bool operator!=(const UUID& other) const { return m_UUID != other.m_UUID; }
	private:
		uint64_t m_UUID;
	};
}

namespace std {
	/**
	 * @brief Hash specialization for RealEngine::UUID to enable usage in standard containers.
	 */
	template<>
	struct hash<RealEngine::UUID> {
		/**
		 * @brief Hashes the UUID by returning its underlying uint64_t value.
		 * @param uuid The UUID to hash.
		 * @return The hash value.
		 */
		std::size_t operator()(const RealEngine::UUID& uuid) const {
			return (uint64_t)uuid;
		}
	};
}