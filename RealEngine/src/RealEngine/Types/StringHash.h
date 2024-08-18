#pragma once

namespace RealEngine {
	//I might come back to this to add a lookup table for the hashes for debbuging purposes
	class StringHash {
	public:
		StringHash(std::string& string);
		StringHash(const char* string);

		operator uint32_t() const { return m_Hash; }

		bool operator==(const StringHash& other) const { return m_Hash == other.m_Hash; }
		bool operator!=(const StringHash& other) const { return m_Hash != other.m_Hash; }
	private:
		uint32_t m_Hash;
	};
}