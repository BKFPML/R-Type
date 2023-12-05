/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** ECS.hpp
*/

#pragma once

#include "components.hpp"

#include <map>
#include <memory>
#include <typeindex>
#include <vector>

class ECS {
public:
    using Entity = size_t;

private:
    std::vector<std::map<Entity, std::shared_ptr<void>>> _components;
    std::map<std::type_index, size_t> _componentTypeToIndex;
    Entity _nextEntityID = 0;

public:
    Entity createEntity();
    template<typename T>
    void registerComponent();
    template<typename T>
    void addComponent(Entity entity, T component);
    template<typename T>
    T* getComponent(Entity entity);
};
