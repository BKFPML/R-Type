/**
 * @file ECS.hpp
 * @brief Declaration of the ECS manager class
 * @date 05-12-2023
 */

#pragma once

#include "components.hpp"

#include <map>
#include <memory>
#include <typeindex>
#include <vector>

/**
 * @brief The Entity Component System manager class
 */
class ECS {
    public:
        using Entity = size_t;

    private:
        std::vector<std::map<Entity, std::shared_ptr<void>>> _components;
        std::map<std::type_index, size_t> _componentTypeToIndex;
        Entity _nextEntityID = 0;

    public:

        /**
         * @brief Creates a new entity
         *
         * @return ECS::Entity
         */
        Entity createEntity()
        {
            return _nextEntityID++;
        };

        /**
         * @brief Registers a new component type and adds it to the component list
         *
         * @tparam T The component type, defined in components.hpp
         */
        template<typename T> void registerComponent()
        {
            _componentTypeToIndex[std::type_index(typeid(T))] = _components.size();
            _components.emplace_back();
        };

        /**
         * @brief Adds a component to an entity
         *
         * @tparam T The component type, defined in components.hpp
         * @param entity The entity to add the component to
         * @param component The component to add
         */
        template<typename T> void addComponent(Entity entity, T component)
        {
            auto componentIndex = _componentTypeToIndex[std::type_index(typeid(T))];
            _components[componentIndex][entity] = std::make_shared<T>(component);
        };
        template<typename ...T> void addComponent(Entity entity, T... components)
        {
            (addComponent(entity, components), ...);
        }

        /**
         * @brief Gets a component from an entity
         *
         * @tparam T The component type, defined in components.hpp
         * @param entity The entity to get the component from
         * @return T* A pointer to the component
         */
        template<typename T> T* getComponent(Entity entity)
        {
            auto index = _componentTypeToIndex[std::type_index(typeid(T))];
            auto it = _components[index].find(entity);
            if (it != _components[index].end()) {
                return static_cast<T*>(it->second.get());
            }
            return nullptr;
        };
};
