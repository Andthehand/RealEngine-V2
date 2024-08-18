#pragma once

namespace RealEngine{
	class UUID {
	public:
		UUID();

		operator uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};
}