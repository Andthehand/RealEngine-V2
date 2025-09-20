#pragma once
#include "quill/DeferredFormatCodec.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <ryml.hpp>


// -------------------------
// Vector Formatter & Codec
// -------------------------

/**
 * @brief Enables fmtquill formatting for glm::vec types.
 * Example: glm::vec3(1, 2, 3) → "vec3(1.000000, 2.000000, 3.000000)"
 */
template<glm::length_t L, typename T, glm::qualifier Q>
struct fmtquill::formatter<glm::vec<L, T, Q>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::glm::vec<L, T, Q> const& vertex, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", glm::to_string(vertex));
    }
};

/**
 * @brief Enables Quill to defer-format glm::vec types for logging.
 */
template<glm::length_t L, typename T, glm::qualifier Q>
struct quill::Codec<glm::vec<L, T, Q>> : quill::DeferredFormatCodec<glm::vec<L, T, Q>> {
};

namespace glm {
	/**
	 * @brief Enables reading glm::vec types from YAML sequences.
	 */
	template<glm::length_t L, typename T, glm::qualifier Q>
	bool read(const ryml::ConstNodeRef& node, glm::vec<L, T, Q>* val) {
		if (!node.has_children() || node.num_children() < L) {
			RE_CORE_ASSERT(false, "Expected a sequence with at least {} elements, got {}", L, node.num_children());
			return false;
		}

		for (glm::length_t i = 0; i < L; ++i)
			node[i] >> (*val)[i];
		return true;
	}

	/**
	 * @brief Enables writing glm::vec types to YAML.
	 */
	template<glm::length_t L, typename T, glm::qualifier Q>
	bool write(ryml::NodeRef* node, const glm::vec<L, T, Q>& val) {
		*node |= ryml::SEQ;
		*node |= ryml::FLOW_SL;

		for (glm::length_t i = 0; i < L; ++i)
			node->append_child() << val[i];

		return true;
	};

	/**
	 * @brief Enables reading glm::quat types from YAML sequences.
	 */
	template<typename T, glm::qualifier Q>
	bool read(const ryml::ConstNodeRef& node, glm::qua<T, Q>* val) {
		if (!node.has_children() || node.num_children() < 4) {
			RE_CORE_ASSERT(false, "Expected a sequence with at least 4 elements, got {}", node.num_children());
			return false;
		}
		
		for (glm::length_t i = 0; i < 4; ++i)
			node[i] >> (*val)[i];

		return true;
	}

	/**
	 * @brief Enables writing glm::quat types to YAML.
	 */
	template<typename T, glm::qualifier Q>
	bool write(ryml::NodeRef* node, const glm::qua<T, Q>& val) {
		*node |= ryml::SEQ;
		*node |= ryml::FLOW_SL;

		for (glm::length_t i = 0; i < 4; ++i)
			node->append_child() << val[i];
		
		return true;
	};
}

// -------------------------
// Matrix Formatter & Codec
// -------------------------

/**
 * @brief Enables fmtquill formatting for glm::mat types (e.g., mat4).
 */
template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct fmtquill::formatter<glm::mat<C, R, T, Q>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::glm::mat<C, R, T, Q> const& matrix, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", glm::to_string(matrix));
    }
};

/**
 * @brief Enables Quill to defer-format glm::mat types for logging.
 */
template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct quill::Codec<glm::mat<C, R, T, Q>> : quill::DeferredFormatCodec<glm::mat<C, R, T, Q>> {
};

// -----------------------------
// Quaternion Formatter & Codec
// -----------------------------

/**
 * @brief Enables fmtquill formatting for glm::qua (quaternion) types.
 */
template<typename T, glm::qualifier Q>
struct fmtquill::formatter<glm::qua<T, Q>> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(::glm::qua<T, Q> const& quaternion, format_context& ctx) const {
        return fmtquill::format_to(ctx.out(), "{}", glm::to_string(quaternion));
    }
};

/**
 * @brief Enables Quill to defer-format glm::qua types for logging.
 */
template<typename T, glm::qualifier Q>
struct quill::Codec<glm::qua<T, Q>> : quill::DeferredFormatCodec<glm::qua<T, Q>> {
};
