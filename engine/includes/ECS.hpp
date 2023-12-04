/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ECS.hpp
*/

#pragma once
#include <vector>


class entity {
    public:
        entity(size_t id);
        ~entity();
    private:
        size_t _id;
};

class ECS {
    public:
        ECS();
        ~ECS();
        createEntity();
        destroyEntity();
    private:
        std::vector<entity> _entities;
}