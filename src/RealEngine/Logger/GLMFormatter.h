#pragma once
#include "quill/DeferredFormatCodec.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


// -------------------------
// Vector Formatter & Codec
// -------------------------

/**
 * @brief Enables fmtquill formatting for glm::vec types.
 * Example: glm::vec3(1, 2, 3) → "vec3(1.000000, 2.000000, 3.000000)"
 */
template<glm::length_t L, typename T, glm::qualifier Q>
struct fmtquill::formatter<glm::vec<L, T, Q>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::glm::vec<L, T, Q> const& vertex, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", glm::to_string(vertex));
    }
};

/**
 * @brief Enables Quill to defer-format glm::vec types for logging.
 */
template<glm::length_t L, typename T, glm::qualifier Q>
struct quill::Codec<glm::vec<L, T, Q>> : quill::DeferredFormatCodec<glm::vec<L, T, Q>> {
};

// -------------------------
// Matrix Formatter & Codec
// -------------------------

/**
 * @brief Enables fmtquill formatting for glm::mat types (e.g., mat4).
 */
template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct fmtquill::formatter<glm::mat<C, R, T, Q>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::glm::mat<C, R, T, Q> const& matrix, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", glm::to_string(matrix));
    }
};

/**
 * @brief Enables Quill to defer-format glm::mat types for logging.
 */
template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct quill::Codec<glm::mat<C, R, T, Q>> : quill::DeferredFormatCodec<glm::mat<C, R, T, Q>> {
};

// -----------------------------
// Quaternion Formatter & Codec
// -----------------------------

/**
 * @brief Enables fmtquill formatting for glm::qua (quaternion) types.
 */
template<typename T, glm::qualifier Q>
struct fmtquill::formatter<glm::qua<T, Q>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::glm::qua<T, Q> const& quaternion, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", glm::to_string(quaternion));
    }
};

/**
 * @brief Enables Quill to defer-format glm::qua types for logging.
 */
template<typename T, glm::qualifier Q>
struct quill::Codec<glm::qua<T, Q>> : quill::DeferredFormatCodec<glm::qua<T, Q>> {
};
