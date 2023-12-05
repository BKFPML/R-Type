/**
 * @file ECS.cpp
 * @brief Implementation of the ECS manager class
 * @date 05-12-2023
 */

#include "../includes/ECS.hpp"

// * This is ugly, but it's the only way to make the compiler happy
template void ECS::registerComponent<Pos>();
template void ECS::addComponent<Pos>(ECS::Entity, Pos);
template Pos* ECS::getComponent<Pos>(ECS::Entity);

/**
 * @brief Creates a new entity
 * 
 * @return ECS::Entity 
 */
ECS::Entity ECS::createEntity()
{
    return _nextEntityID++;
}

/**
 * @brief Registers a new component type and adds it to the component list
 * 
 * @tparam T The component type, defined in components.hpp
 */
template<typename T> void ECS::registerComponent()
{
    _componentTypeToIndex[std::type_index(typeid(T))] = _components.size();
    _components.emplace_back();
}

/**
 * @brief Adds a component to an entity
 * 
 * @tparam T The component type, defined in components.hpp
 * @param entity The entity to add the component to
 * @param component The component to add
 */
template<typename T> void ECS::addComponent(Entity entity, T component)
{
    auto componentIndex = _componentTypeToIndex[std::type_index(typeid(T))];
    _components[componentIndex][entity] = std::make_shared<T>(component);
}

/**
 * @brief Gets a component from an entity
 * 
 * @tparam T The component type, defined in components.hpp
 * @param entity The entity to get the component from
 * @return T* A pointer to the component
 */
template<typename T> T* ECS::getComponent(Entity entity)
{
    auto index = _componentTypeToIndex[std::type_index(typeid(T))];
    auto it = _components[index].find(entity);
    if (it != _components[index].end()) {
        return static_cast<T*>(it->second.get());
    }
    return nullptr;
}
