#pragma once
#include "quill/DeferredFormatCodec.h"

#include <ryml.hpp>

/**
 * @brief Formatter for ryml::csubstr to enable logging with fmtquill and Quill.
 *
 * Allows usage like:
 * RE_CORE_INFO("YAML string: {}", yamlNode.key());
 */
template <>
struct fmtquill::formatter<ryml::csubstr> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::ryml::csubstr const& str, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", "{}", std::string_view(str.begin(), str.end()));
    }
};

/**
 * @brief Enables deferred formatting support in Quill for ryml::csubstr.
 */
template <>
struct quill::Codec<ryml::csubstr> : quill::DeferredFormatCodec<ryml::csubstr> {
};
