#pragma once
#include <spdlog/fmt/ostr.h>

#include <filesystem>

template<>
struct fmt::formatter<std::filesystem::path> : fmt::formatter<std::string> {
	auto format(const std::filesystem::path& path, format_context& ctx) const -> decltype(ctx.out()) {
		return fmt::format_to(ctx.out(), "{}", path.string());
	}
};