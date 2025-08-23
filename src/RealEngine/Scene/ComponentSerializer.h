#pragma once
#include <ryml.hpp>
#include <ryml_std.hpp>

#include <entt/entt.hpp>

#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Components.h"
#include "RealEngine/Formatter/RealEngineFormatter.h"

namespace RealEngine {
	// TODO: Comeback and maybe change this to just using read and write ryml callbacks
	// Primary (fallback) template
	template<typename T>
	struct ComponentSerializer {
		static void Serialize(ryml::NodeRef, const T&) {
			RE_CORE_ASSERT(false, "Serialize for type {} not implemented", typeid(T).name());
		}

		static T Deserialize(ryml::ConstNodeRef) {
			RE_CORE_ASSERT(false, "Deserialize for type {} not implemented", typeid(T).name());
		}
	};

    template<>
    struct ComponentSerializer<TagComponent> {
        static void Serialize(ryml::NodeRef node, const TagComponent& comp) {
            ryml::NodeRef transformNode = node["TagComponent"];
            transformNode |= ryml::MAP;
            transformNode["Tag"] << comp.Tag;
        }

        static TagComponent Deserialize(ryml::ConstNodeRef componentNode) {
            if (componentNode.has_child("Tag")) {
                std::string tagValue;
                componentNode["Tag"] >> tagValue;

                return TagComponent(tagValue);
            } else {
                RE_CORE_ASSERT(false, "TagComponent does not have a 'Tag' child node");
                return {};
            }
        }
    };

    template<>
    struct ComponentSerializer<IDComponent> {
        static void Serialize(ryml::NodeRef node, const IDComponent& comp) {
            ryml::NodeRef transformNode = node["IDComponent"];
            transformNode << comp.ID;
        }

        static IDComponent Deserialize(ryml::ConstNodeRef componentNode) {
            UUID idValue;
            componentNode >> idValue;

            return IDComponent(idValue);
        }
    };

    template<>
    struct ComponentSerializer<TransformComponent> {
        static void Serialize(ryml::NodeRef node, const TransformComponent& comp) {
            ryml::NodeRef transformNode = node["TransformComponent"];
            transformNode |= ryml::MAP;
            transformNode.append_child() << ryml::key("Position") << comp.Position;
        }

        static TransformComponent Deserialize(ryml::ConstNodeRef componentNode) {
            if (componentNode.has_child("Position")) {
                TransformComponent transform;
                componentNode["Position"] >> transform.Position;
                return transform;
            }
            else {
                RE_CORE_ASSERT(false, "TransformComponent does not have a 'Position' child node");
                return {};
            }
        }
    };

	template<typename T>
	void SerializeComponent(ryml::NodeRef node, Entity& entity) {
        if(entity.HasComponent<T>())
		    ComponentSerializer<T>::Serialize(node, entity.GetComponent<T>());
	}

	template<typename T>
	void DeserializeComponent(ryml::ConstNodeRef node, Entity& entity) {
        if (node.has_child(T::GetName())) {
            const auto componentNode = node[T::GetName()];

            auto component = ComponentSerializer<T>::Deserialize(componentNode);
            entity.AddComponent<T>(component);
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
