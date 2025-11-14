#pragma once

#include <Coral/String.hpp>

#include <quill/DeferredFormatCodec.h>
#include <ryml.hpp>

template <>
struct fmtquill::formatter<Coral::String> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::Coral::String const& str, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", std::string(str));
    }
};

template <>
struct quill::Codec<Coral::String> : quill::DeferredFormatCodec<Coral::String> {
};

namespace Coral {
	// DO NOT IMPLEMENT!!!!! 
    // Coral::String has to be memory managed via Coral::String::New and Coral::String::Free
    /*inline bool read(const ryml::ConstNodeRef& node, Coral::String* val) {
    }*/

    inline bool write(ryml::NodeRef* node, const Coral::String& val) {
        *node |= ryml::VAL;
        (*node) << std::string(val);
        return true;
    }
}
