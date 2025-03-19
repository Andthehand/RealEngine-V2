#pragma once
#include <spdlog/fmt/ostr.h>

#include <ryml.hpp>

template<>
struct fmt::formatter<ryml::csubstr> : fmt::formatter<std::string> {
	auto format(const ryml::csubstr& str, format_context& ctx) const -> decltype(ctx.out()) {
		return fmt::format_to(ctx.out(), "{}", std::string_view(str.begin(), str.end()));
	}
};