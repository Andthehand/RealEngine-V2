#pragma once
#include "RealEngine/Types/PathHash.h"

namespace RealEngine {
	template<typename T>
	class GeneralManager {
	public:
		GeneralManager() = delete;

		static Ref<T> LoadResource(const std::filesystem::path& path) { 
			PathHash hash = PathHash(path);

			auto it = s_Resources.find(hash);
			if (it != s_Resources.end()) {
				Ref<T> resource = it->second.lock();
				if (resource) {
					return resource;
				}
			}
			Ref<T> resource = CreateRef<T>(path);
			s_Resources[hash] = resource;
			return resource;
		}
	private:
		static inline std::unordered_map<PathHash, Weak_Ref<T>> s_Resources;
	};
}