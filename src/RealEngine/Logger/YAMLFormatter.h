#pragma once
#include "quill/DeferredFormatCodec.h"

#include <ryml.hpp>

//template <>
//struct fmtquill::formatter<ryml::csubstr> {
//    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
//
//    auto format(::ryml::csubstr const& str, format_context& ctx) const {
//        return fmtquill::format_to(ctx.out(), "{}", "{}", std::string_view(str.begin(), str.end()));
//    }
//};
//
//template <>
//struct quill::Codec<ryml::csubstr> : quill::DeferredFormatCodec<ryml::csubstr> {
//};
