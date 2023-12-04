/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ECS.cpp
*/

#include "../includes/ECS.hpp"


// * ENTITY
entity::~entity()
{
}

entity::entity(size_t id)
{
    _id = id;
}


// * ECS
ECS::~ECS()
{
}

ECS::ECS()
{
}

ECS::createEntity()
{
    _entities.push_back(entity(_entities.size()));
}

ECS::destroyEntity(size_t id)
{
    _entities.erase(_entities.begin() + id);
}