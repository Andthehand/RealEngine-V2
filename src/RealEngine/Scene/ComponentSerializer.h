#pragma once
#include <ryml.hpp>
#include <ryml_std.hpp>

#include <entt/entt.hpp>

#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Components.h"

#include "RealEngine/Formatter/GLMFormatter.h"

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

		static void Deserialize(const ryml::ConstNodeRef& node, TagComponent& comp) {
			node["Tag"] >> comp.Tag;
		}
	};

	template<>
	struct ComponentSerializer<IDComponent> {
		static void Serialize(ryml::NodeRef& node, const IDComponent& comp) {
			//TODO: Make UUID serializable
			ryml::NodeRef transformNode = node["IDComponent"];
			transformNode |= ryml::MAP;
			transformNode["ID"] << (uint64_t)comp.ID;
		}

		static void Deserialize(const ryml::ConstNodeRef& node, IDComponent& comp) {
			//TODO: Make UUID serializable
			uint64_t id;
			node["ID"] >> id;
			comp.ID = RealEngine::UUID(id);
		}
	};

	template<>
	struct ComponentSerializer<TransformComponent> {
		static void Serialize(ryml::NodeRef& node, const TransformComponent& comp) {
			ryml::NodeRef transformNode = node["TransformComponent"];
			transformNode |= ryml::MAP;
			transformNode.append_child() << ryml::key("Position") << comp.Position;
		}

		static void Deserialize(const ryml::ConstNodeRef& node, TransformComponent& comp) {
			node["Position"] >> comp.Position;
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
