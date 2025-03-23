#pragma once
#include "quill/DeferredFormatCodec.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// Vector
template<glm::length_t L, typename T, glm::qualifier Q>
struct fmtquill::formatter<glm::vec<L, T, Q>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::glm::vec<L, T, Q> const& vertex, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", glm::to_string(vertex));
    }
};

template<glm::length_t L, typename T, glm::qualifier Q>
struct quill::Codec<glm::vec<L, T, Q>> : quill::DeferredFormatCodec<glm::vec<L, T, Q>> {
};

// Matrix
template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct fmtquill::formatter<glm::mat<C, R, T, Q>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::glm::mat<C, R, T, Q> const& matrix, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", glm::to_string(matrix));
    }
};

template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct quill::Codec<glm::mat<C, R, T, Q>> : quill::DeferredFormatCodec<glm::mat<C, R, T, Q>> {
};

// Quaternion
template<typename T, glm::qualifier Q>
struct fmtquill::formatter<glm::qua<T, Q>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::glm::qua<T, Q> const& quaternion, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", glm::to_string(quaternion));
    }
};

template<typename T, glm::qualifier Q>
struct quill::Codec<glm::qua<T, Q>> : quill::DeferredFormatCodec<glm::qua<T, Q>> {
};
