#pragma once
#include <ryml.hpp>
#include <ryml_std.hpp>

#include <entt/entt.hpp>

#include "RealEngine/Core/Project.h"

#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Components.h"

#include "RealEngine/Formatter/RealEngineFormatter.h"

namespace RealEngine {
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
        (*node)["Position"] << comp.GetPosition();
        (*node)["Rotation"] << comp.GetRotationQuat();
        (*node)["Scale"]    << comp.GetScale();
        return true;
    }

    inline bool read(const ryml::ConstNodeRef& node, TransformComponent* out) {
        if (node.invalid()) {
            RE_CORE_ASSERT(false, "Invalid node for TransformComponent");
            return false;
        }

        glm::vec3 position{ 0.0f };
        glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
        glm::vec3 scale{ 1.0f };

        if (node.has_child("Position")) node["Position"] >> position;
        else RE_CORE_WARN("TransformComponent missing 'Position' - using default (0,0,0)");

        if (node.has_child("Rotation")) node["Rotation"] >> rotation;
        else RE_CORE_WARN("TransformComponent missing 'Rotation' - using default (0,0,0)");

        if (node.has_child("Scale")) node["Scale"] >> scale;
        else RE_CORE_WARN("TransformComponent missing 'Scale' - using default (1,1,1)");

        out->SetPosition(position);
        out->SetRotationQuat(rotation);
        out->SetScale(scale);

        return true;
    }

    inline bool write(ryml::NodeRef* node, const SpriteRendererComponent& comp) {
        *node |= ryml::MAP;
        (*node)["Color"] << comp.Color;
        
        if(comp.Texture)
            (*node)["Texture"] << comp.Texture->GetHandle();

        return true;
	}

    inline bool read(const ryml::ConstNodeRef& node, SpriteRendererComponent* out) {
        if (!node.has_child("Color")) {
            RE_CORE_ASSERT(false, "SpriteRendererComponent does not have a 'Color' child node");
            return false;
        }
        node["Color"] >> out->Color;

        if (node.has_child("Texture")) {
            AssetHandle handle;
            node["Texture"] >> handle;
            Ref<Asset> asset = RealEngine::Project::GetAssetManager().GetAsset<Texture2D>(handle);
            if (asset) {
                out->Texture = std::dynamic_pointer_cast<Texture2D>(asset);
            } else {
                RE_CORE_WARN("Failed to load Texture2D asset with handle: {}", (uint64_t)handle);
            }
		}

        return true;
	}

    inline bool write(ryml::NodeRef* node, const ScriptComponent& comp) {
        *node |= ryml::MAP;
        (*node)["ClassName"] << comp.Instance.m_Type->GetFullName();

		return true;
    }

    inline bool read(const ryml::ConstNodeRef& node, ScriptComponent* out) {
        if (!node.has_child("ClassName")) {
            RE_CORE_ASSERT(false, "ScriptComponent does not have a 'ClassName' child node");
            return false;
        }

        std::string className;
        node["ClassName"] >> className;
        
        out->Instance = ScriptEngine::CreateObject(100, className);
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
                entity.AddComponent<T>(std::move(component));
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
