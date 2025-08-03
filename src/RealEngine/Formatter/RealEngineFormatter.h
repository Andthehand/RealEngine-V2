#pragma once
#include "quill/DeferredFormatCodec.h"

#include "RealEngine/Types/UUID.h"

template <>
struct fmtquill::formatter<RealEngine::UUID> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::RealEngine::UUID const& id, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", (uint64_t)id);
    }
};

template <>
struct quill::Codec<RealEngine::UUID> : quill::DeferredFormatCodec<RealEngine::UUID> {
};

