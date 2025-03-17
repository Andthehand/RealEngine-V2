#pragma once
#include <spdlog/fmt/ostr.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// Vector
template<glm::length_t L, typename T, glm::qualifier Q>
struct fmt::formatter<glm::vec<L, T, Q>> : fmt::formatter<std::string> {
	auto format(const glm::vec<L, T, Q>& vector, format_context& ctx) const -> decltype(ctx.out()) {
		return fmt::format_to(ctx.out(), "{}", glm::to_string(vector));
	}
};

// Matrix
template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct fmt::formatter<glm::mat<C, R, T, Q>> : fmt::formatter<std::string> {
	auto format(const glm::mat<C, R, T, Q>& matrix, format_context& ctx) const -> decltype(ctx.out()) {
		return fmt::format_to(ctx.out(), "{}", glm::to_string(matrix));
	}
};

// Quaternion
template<typename T, glm::qualifier Q>
struct fmt::formatter<glm::qua<T, Q>> : fmt::formatter<std::string> {
	auto format(const glm::qua<T, Q>& quaternion, format_context& ctx) const -> decltype(ctx.out()) {
		return fmt::format_to(ctx.out(), "{}", glm::to_string(quaternion));
	}
};