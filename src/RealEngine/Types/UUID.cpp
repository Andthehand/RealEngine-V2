#include "UUID.h"

#include <random>

namespace RealEngine {
	static std::mt19937_64 s_RandomEngine;
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	UUID::UUID(uint64_t uuid)
		: m_UUID(uuid) { }

	//This is very fast and very random
	UUID::UUID() {
		m_UUID = s_UniformDistribution(s_RandomEngine);
	}
}