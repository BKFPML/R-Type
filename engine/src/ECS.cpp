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

entity::entity(size_t UID)
{
    _UID = UID;
}


// * ECS
ECS::~ECS()
{
}

ECS::ECS()
{
    _UIDs = 0;
}

ECS::createEntity()
{
    _entities.push_back(entity(_UIDs));
    return (++_UIDs);
}

ECS::destroyEntity(size_t UID)
{
    _entities.erase(_entities.begin() + id);
}