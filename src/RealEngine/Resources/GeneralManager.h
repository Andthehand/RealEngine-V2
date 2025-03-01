#pragma once
#include "RealEngine/Types/PathHash.h"

namespace RealEngine {
	template<typename T>
	class GeneralManager {
	public:
		GeneralManager() = delete;

		[[deprecated]]
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
		// https://stackoverflow.com/questions/19758343/how-to-initialize-a-static-stdunordered-map-of-a-type-trait
		// THIS IS BROKEN DO NOT USE!!!!
		//TODO: The biggest problem with is is that if the resrouce goes out of scope, it will not be removed from the map4
		//To fix this once we have a seen object it will hold a reference to the resource manager so that it will be destoryed after every Scene change
		static inline std::unordered_map<PathHash, Weak_Ref<T>> s_Resources;
	};
}