#pragma once
#include "quill/DeferredFormatCodec.h"

#include "RealEngine/Types/UUID.h"
#include "RealEngine/Types/StringHash.h"

#include "RealEngine/Asset/AssetImporter.h"

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

template <>
struct fmtquill::formatter<RealEngine::StringHash> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::RealEngine::StringHash const& hash, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", (uint32_t)hash);
    }
};

template <>
struct quill::Codec<RealEngine::StringHash> : quill::DeferredFormatCodec<RealEngine::StringHash> {
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

    inline bool read(const ryml::ConstNodeRef& node, RealEngine::StringHash* val) {
        uint32_t hash;
        node >> hash;
        *val = RealEngine::StringHash(hash);
        return true;
	}

    inline bool write(ryml::NodeRef* node, const RealEngine::StringHash& val) {
        *node |= ryml::VAL;
        (*node) << (uint32_t)val;
        return true;
	}

    inline bool read(const ryml::ConstNodeRef& node, RealEngine::Texture2DMetadata* val) {
        if (!node.has_child("MipLevels") || 
            !node.has_child("WrapMode") ||
            !node.has_child("FilterMode")) {
            RE_CORE_ASSERT(false, "Expected a node with 'MipLevels', 'WrapMode', and 'FilterMode' children");
            return false;
        }

		node["MipLevels"] >> val->MipLevels;

		uint32_t wrapMode, filterMode;
        node["WrapMode"] >> wrapMode;
		node["FilterMode"] >> filterMode;

        val->WrapMode = (RealEngine::TextureWrapMode)wrapMode;
		val->FilterMode = (RealEngine::TextureFilterMode)filterMode;

		return true;
    }

    inline bool write(ryml::NodeRef* node, const RealEngine::Texture2DMetadata& val) {
        *node |= ryml::MAP;
        (*node)["MipLevels"] << val.MipLevels;
        (*node)["WrapMode"] << (uint32_t)val.WrapMode;
		(*node)["FilterMode"] << (uint32_t)val.FilterMode;
        return true;
	}
}
