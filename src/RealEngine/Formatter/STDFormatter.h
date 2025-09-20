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

namespace std::filesystem {
    /**
     * @brief Enables reading std::filesystem::path from YAML using ryml.
     *
     * This allows deserialization of filesystem paths from YAML nodes.
     */
    inline bool read(const ryml::ConstNodeRef& node, std::filesystem::path* val) {
        std::string pathStr;
        node >> pathStr;
        *val = std::filesystem::path(pathStr);
        return true;
    }
    /**
     * @brief Enables writing std::filesystem::path to YAML using ryml.
     *
     * This allows serialization of filesystem paths to YAML nodes.
     */
    inline bool write(ryml::NodeRef* node, const std::filesystem::path& val) {
        *node |= ryml::VAL;
        *node << val.string();
        return true;
    }
}
