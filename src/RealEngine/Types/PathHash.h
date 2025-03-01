#pragma once
#include <filesystem>

namespace RealEngine {
	//I might come back to this to add a lookup table for the hashes for debbuging purposes
	class PathHash {
	public:
		PathHash(const std::filesystem::path& path);
		PathHash(const char* string);

		operator uint32_t() const { return m_Hash; }

		bool operator==(const PathHash& other) const { return m_Hash == other.m_Hash; }
		bool operator!=(const PathHash& other) const { return m_Hash != other.m_Hash; }
	private:
		uint32_t m_Hash;

#ifdef RE_DEBUG
		std::filesystem::path m_String;
#endif
	};
}

namespace std {
	template<>
	struct hash<RealEngine::PathHash> {
		std::size_t operator()(const RealEngine::PathHash& stringHash) const {
			return (uint32_t)stringHash;
		}
	};
}