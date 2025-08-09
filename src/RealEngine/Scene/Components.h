#pragma once

#include <glm/glm.hpp>

#include "RealEngine/Types/UUID.h"

// Has to be a function so that the compiler actually compiles it
#define RE_REGISTER_COMPONENT() void DummyFunction() { ::RealEngine::ComponentList::Append<std::remove_reference<decltype(*this)>::type>(); }

namespace RealEngine {
    /*
     * @brief Namespace for component management and type lists.
     *
     * This namespace provides utilities for adding components to a
	 * compile time type list, allowing for efficient storage and retrieval
     */
    namespace ComponentList {
        // The type list
        template<class...> struct ComponentGroup {};

        // Friend injection machinery
        namespace Detail {
            template<auto N> struct Nth {
                friend consteval auto Get(Nth<N>);
            };

            template<auto N, class T> struct Set {
                friend consteval auto Get(Nth<N>) { return T{}; }
            };

            template<class T, template<class...> class List, class... Ts>
            auto AppendType(List<Ts...>) -> List<Ts..., T>;
        }

        // Append logic
        template<class T, auto N = 0, auto Unique = [] {} >
        consteval void Append() {
            if constexpr (requires { Get(Detail::Nth<N>{}); }) {
                Append<T, N + 1, Unique>();
            }
            else if constexpr (N == 0) {
                (void)Detail::Set<N, ComponentGroup<T>>{};
            }
            else {
                using Prev = decltype(Get(Detail::Nth<N - 1>{}));
                using NewGroup = decltype(Detail::AppendType<T>(Prev{}));
                (void)Detail::Set<N, NewGroup>{};
            }
        }

        // Retrieve the component group
        template<auto unique = [] {}, auto N = 0 >
        consteval auto GetAllComponents() {
            if constexpr (requires { Get(Detail::Nth<N>{}); }) {
                return GetAllComponents<unique, N + 1>();
            }
            else if constexpr (N == 0) {
                return ComponentGroup<>{};
            }
            else {
                return Get(Detail::Nth<N - 1>{});
            }
        }
	}


    struct IDComponent {
        UUID ID;

        IDComponent() = default;
        IDComponent(UUID id)
            : ID(id) { }

        bool operator==(const IDComponent& other) const {
            return ID == other.ID;
        }

        RE_REGISTER_COMPONENT()
    };

    struct TagComponent {
        std::string Tag;

        TagComponent(const std::string& tag = "Entity")
            : Tag(tag) { }

        bool operator==(const TagComponent& other) const {
            return Tag == other.Tag;
        }

        RE_REGISTER_COMPONENT()
    };

    struct TransformComponent {
        glm::vec3 Position = { 0.0f, 0.0f, 0.0f };

        TransformComponent() = default;
        TransformComponent(const glm::vec3& position)
            : Position(position) { }

        bool operator==(const TransformComponent& other) const {
            return Position == other.Position;
        }

        RE_REGISTER_COMPONENT()
    };
}
