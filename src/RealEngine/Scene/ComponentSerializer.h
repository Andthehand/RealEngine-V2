#pragma once
#include <ryml.hpp>
#include <ryml_std.hpp>

#include <entt/entt.hpp>

#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Components.h"
#include "RealEngine/Formatter/RealEngineFormatter.h"

namespace RealEngine {
	// Primary (fallback) template
	template<typename T>
	struct ComponentSerializer {
		static void Serialize(ryml::NodeRef&, const T&) {
			RE_CORE_ASSERT(false, "Serialize for type {} not implemented", typeid(T).name());
		}

		static void Deserialize(const ryml::ConstNodeRef&, T*) {
			RE_CORE_ASSERT(false, "Deserialize for type {} not implemented", typeid(T).name());
		}
	};

    template<>
    struct ComponentSerializer<TagComponent> {
        static void Serialize(ryml::NodeRef& node, const TagComponent& comp) {
            ryml::NodeRef transformNode = node["TagComponent"];
            transformNode |= ryml::MAP;
            transformNode["Tag"] << comp.Tag;
        }

        static void Deserialize(const ryml::ConstNodeRef& node, TagComponent* comp) {
            const auto tagNode = node["TagComponent"];
            if (tagNode.has_child("Tag")) {
                tagNode["Tag"] >> comp->Tag;
            } else {
				RE_CORE_ASSERT(false, "TagComponent does not have a 'Tag' child node");
            }
        }
    };

    template<>
    struct ComponentSerializer<IDComponent> {
        static void Serialize(ryml::NodeRef& node, const IDComponent& comp) {
            ryml::NodeRef transformNode = node["IDComponent"];
            transformNode << comp.ID;
        }

        static void Deserialize(const ryml::ConstNodeRef& node, IDComponent* comp) {
            const auto idNode = node["IDComponent"];
            idNode >> comp->ID;
        }
    };

    template<>
    struct ComponentSerializer<TransformComponent> {
        static void Serialize(ryml::NodeRef& node, const TransformComponent& comp) {
            ryml::NodeRef transformNode = node["TransformComponent"];
            transformNode |= ryml::MAP;
            transformNode.append_child() << ryml::key("Position") << comp.Position;
        }

        static void Deserialize(const ryml::ConstNodeRef& node, TransformComponent* comp) {
            const auto transformNode = node["TransformComponent"];
            if (transformNode.has_child("Position")) {
                transformNode["Position"] >> comp->Position;
            } else {
				RE_CORE_ASSERT(false, "TransformComponent does not have a 'Position' child node");
            }
        }
    };

	template<typename T>
	void SerializeComponent(ryml::NodeRef& node, Entity& entity) {
		ComponentSerializer<T>::Serialize(node, entity.GetComponent<T>());
	}

	template<typename T>
	void DeserializeComponent(const ryml::ConstNodeRef& node, Entity& entity) {
		ComponentSerializer<T>::Deserialize(node, entity.GetComponent<T>());
	}

	template<typename... Components>
	void SerializeComponents(ComponentList::ComponentGroup<Components...>, Entity& entity, ryml::NodeRef& node) {
		((SerializeComponent<Components>(node, entity)), ...);
	}
}
