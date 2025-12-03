#pragma once

#include "unordered_dense.h"

namespace RealEngine {
	template<typename TKey, typename TValue>
	using HashMap = ankerl::unordered_dense::map<TKey, TValue>;
}
