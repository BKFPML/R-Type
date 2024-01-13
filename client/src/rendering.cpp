/**
 * @file rendering.cpp
 * @brief contains the entity rendering functions
 * @date 11-01-2024
 */

#include "../includes/client.hpp"

/**
 * @brief Draws all drawable entities
 *
 */
void rtype::Client::drawEntities()
{
    std::vector<ECS::Entity> entities = _ecs.getDrawableEntities();
    for (auto& entity : entities) {
        Position *pos = _ecs.getComponent<Position>(entity);
        Sprite *sprite = _ecs.getComponent<Sprite>(entity);
        if (_ecs.hasComponent<Rotation>(entity)) {
            Rotation *rot = _ecs.getComponent<Rotation>(entity);
            _graphical->drawSprite(sprite->texture, pos->x, pos->y, sprite->startX, sprite->startY, sprite->scale, rot->angle, sprite->width, sprite->height);
        } else
           _graphical->drawSprite(sprite->texture, pos->x, pos->y, sprite->startX, sprite->startY, sprite->scale, 0, sprite->width, sprite->height);
    }
}
