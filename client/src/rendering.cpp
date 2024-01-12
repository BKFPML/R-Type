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
        _graphical->drawSprite(sprite->texture, pos->x, pos->y, 3, 180, 34, 34); // TODO: derive the sprite size from the texture
    }
}
