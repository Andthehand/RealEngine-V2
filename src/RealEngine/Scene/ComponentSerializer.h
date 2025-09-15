#pragma once
#include <ryml.hpp>
#include <ryml_std.hpp>

#include <entt/entt.hpp>

#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Components.h"
#include "RealEngine/Formatter/RealEngineFormatter.h"

namespace RealEngine {
	// TODO: Comeback and maybe change this to just using read and write ryml callbacks

    // Free read/write for components (replaces ComponentSerializer)

    inline bool write(ryml::NodeRef* node, const TagComponent& comp) {
        *node |= ryml::MAP;
        (*node)["Tag"] << comp.Tag;
        return true;
    }

    inline bool read(const ryml::ConstNodeRef& node, TagComponent* out) {
        if (!node.has_child("Tag")) {
            RE_CORE_ASSERT(false, "TagComponent does not have a 'Tag' child node");
            return false;
        }
        node["Tag"] >> out->Tag;
        return true;
    }

    inline bool write(ryml::NodeRef* node, const IDComponent& comp) {
        // Delegate to UUID write
        return RealEngine::write(node, comp.ID);
    }

    inline bool read(const ryml::ConstNodeRef& node, IDComponent* out) {
        // Delegate to UUID read
        UUID id{};
        if (!RealEngine::read(node, &id)) return false;
        *out = IDComponent(id);
        return true;
    }

    inline bool write(ryml::NodeRef* node, const TransformComponent& comp) {
        *node |= ryml::MAP;
        (*node)["Position"] << comp.Position;
        return true;
    }

    inline bool read(const ryml::ConstNodeRef& node, TransformComponent* out) {
        if (!node.has_child("Position")) {
            RE_CORE_ASSERT(false, "TransformComponent does not have a 'Position' child node");
            return false;
        }
        node["Position"] >> out->Position;
        return true;
    }

    inline bool write(ryml::NodeRef* node, const SpriteRendererComponent& comp) {
        *node |= ryml::MAP;
        (*node)["Color"] << comp.Color;
        return true;
	}

    inline bool read(const ryml::ConstNodeRef& node, SpriteRendererComponent* out) {
        if (!node.has_child("Color")) {
            RE_CORE_ASSERT(false, "SpriteRendererComponent does not have a 'Color' child node");
            return false;
        }
        node["Color"] >> out->Color;
        return true;
	}

	template<typename T>
	void SerializeComponent(ryml::NodeRef node, Entity& entity) {
        if (entity.HasComponent<T>()) {
            ryml::NodeRef componentNode = node[T::GetName()];
            write(&componentNode, entity.GetComponent<T>());
        }
	}

	template<typename T>
	void DeserializeComponent(ryml::ConstNodeRef node, Entity& entity) {
        if (node.has_child(T::GetName())) {
            const auto componentNode = node[T::GetName()];
            T component{};
            if (read(componentNode, &component)) {
                entity.AddComponent<T>(component);
            } else {
                RE_CORE_ASSERT(false, "Failed to read component {}", T::GetName());
            }
        }
	}

	template<typename... Components>
	void SerializeComponents(ComponentList::ComponentGroup<Components...>, Entity& entity, ryml::NodeRef node) {
		((SerializeComponent<Components>(node, entity)), ...);
	}

	template<typename... Components>
    void DeserializeComponents(ComponentList::ComponentGroup<Components...>, Entity& entity, ryml::ConstNodeRef node) {
        ((DeserializeComponent<Components>(node, entity)), ...);
	}
}
