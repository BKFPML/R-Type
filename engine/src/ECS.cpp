/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ECS.cpp
*/

#include "../includes/ECS.hpp"

// * This is ugly, but it's the only way to make the compiler happy
template void ECS::registerComponent<Pos>();
template void ECS::addComponent<Pos>(ECS::Entity, Pos);
template Pos* ECS::getComponent<Pos>(ECS::Entity);


ECS::Entity ECS::createEntity()
{
    return _nextEntityID++;
}

template<typename T> void ECS::registerComponent()
{
    _componentTypeToIndex[std::type_index(typeid(T))] = _components.size();
    _components.emplace_back();
}

template<typename T> void ECS::addComponent(Entity entity, T component)
{
    auto componentIndex = _componentTypeToIndex[std::type_index(typeid(T))];
    _components[componentIndex][entity] = std::make_shared<T>(component);
}

template<typename T> T* ECS::getComponent(Entity entity)
{
    auto index = _componentTypeToIndex[std::type_index(typeid(T))];
    auto it = _components[index].find(entity);
    if (it != _components[index].end()) {
        return static_cast<T*>(it->second.get());
    }
    return nullptr;
}
