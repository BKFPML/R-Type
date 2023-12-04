/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ECS.hpp
*/

#pragma once
#include <vector>
#include components.hpp

class entity {
    public:
        entity(size_t UID);
        ~entity();
    private:
        size_t _UID;
};

class ECS {
    public:
        ECS();
        ~ECS();
        createEntity();
        destroyEntity(size_t UID);
    private:
        std::vector<entity> _entities;
        std::size_t _UIDs;
}