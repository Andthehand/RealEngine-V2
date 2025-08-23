#pragma once
#include "quill/DeferredFormatCodec.h"

#include "RealEngine/Types/UUID.h"

#include <ryml.hpp>

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

namespace RealEngine {
    /**
     * @brief Enables reading RealEngine::UUID from YAML.
     */
    inline bool read(const ryml::ConstNodeRef& node, RealEngine::UUID* val) {
        if (!node.has_child("ID")) {
            RE_CORE_ASSERT(false, "Expected a node with 'ID' child");
            return false;
        }

        uint64_t id;
        node["ID"] >> id;
        *val = RealEngine::UUID(id);
        return true;
    }

    /**
     * @brief Enables writing RealEngine::UUID to YAML.
     */
    inline bool write(ryml::NodeRef* node, const RealEngine::UUID& val) {
        *node |= ryml::MAP;
        (*node)["ID"] << (uint64_t)val;
        return true;
	}
}
