/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** rendering.cpp
*/

#include "../includes/client.hpp"

void rtype::Client::drawEntities()
{
    std::vector<ECS::Entity> entities = _ecs.getDrawableEntities();
    for (auto& entity : entities) {
        Position *pos = _ecs.getComponent<Position>(entity);
        Sprite *sprite = _ecs.getComponent<Sprite>(entity);
        _graphical->drawSprite(sprite->texture, pos->x, pos->y, 3, 180, 34, 34);
    }
}

