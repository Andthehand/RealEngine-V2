#pragma once
#include "quill/DeferredFormatCodec.h"

#include <filesystem>

/**
 * @brief Custom formatter for std::filesystem::path using fmtquill.
 *
 * This allows std::filesystem::path to be used in log statements like:
 * RE_CORE_INFO("File path: {}", somePath);
 */
template <>
struct fmtquill::formatter<std::filesystem::path> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::std::filesystem::path const& path, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", path.string());
    }
};

/**
 * @brief Specialization of Quill's codec to support deferred formatting of std::filesystem::path.
 *
 * This enables Quill to log filesystem paths safely and efficiently.
 */
template <>
struct quill::Codec<std::filesystem::path> : quill::DeferredFormatCodec<std::filesystem::path> {
};