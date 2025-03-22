#pragma once
#include "quill/DeferredFormatCodec.h"

#include <filesystem>

template <>
struct fmtquill::formatter<std::filesystem::path> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::std::filesystem::path const& path, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", path.string());
    }
};

template <>
struct quill::Codec<std::filesystem::path> : quill::DeferredFormatCodec<std::filesystem::path> {
};