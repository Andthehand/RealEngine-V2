#pragma once
#define ANKERL_UNORDERED_DENSE_HASH 1

#if ANKERL_UNORDERED_DENSE_HASH
	#define ANKERL_UNORDERED_DENSE_STD_MODULE 1
	#include "unordered_dense.h"
#else
	#include <unordered_map>
	#include <unordered_set>
#endif

namespace RealEngine {
#if ANKERL_UNORDERED_DENSE_HASH
	template<typename TKey, typename TValue>
	using HashMap = ankerl::unordered_dense::map<TKey, TValue>;

	template<typename TKey>
	using HashSet = ankerl::unordered_dense::set<TKey>;
#else
	template<typename TKey, typename TValue>
	using HashMap = std::unordered_map<TKey, TValue>;

	template<typename TKey>
	using HashSet = std::unordered_set<TKey>;
#endif
}
