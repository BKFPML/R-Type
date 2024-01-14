/**
 * @file enemies.hpp
 * @brief Header file for enemies
 * @date 14-01-2024
 */

#pragma once

#include "../../engine/includes/ECS.hpp"
#include "../../engine/includes/components.hpp"

/**
 * @brief Attributes of an enemy
 */
struct Attributes {
    int health;
    float rotation;
    std::string texture;
    int width, height, startX, startY;
    float scale;
    float speed;

    Attributes(int health, float rotation, std::string texture, int width, int height, int startX, int startY, float scale, float speed) : health(health), texture(texture), width(width), height(height), startX(startX), startY(startY), scale(scale), speed(speed) {}
    Attributes() : health(0), rotation(0), texture(""), width(0), height(0), startX(0), startY(0), scale(0.0f), speed(0.0f) {}
};

std::map<std::string, Attributes> createEnemyTypes()
{
    std::map<std::string, Attributes> associations;
    associations["crawler"] = Attributes(100, 180, "r_typesheet8", 32, 32, 0, 0, 3, 2);
    associations["shooter"] = Attributes(200, 180, "r_typesheet9", 55, 55, 0, 0, 3, 1);
    associations["spaceshipBoss"] = Attributes(1000, 0, "r_typesheet38", 185, 160, 0, 0, 3, 1);

    return associations;
}
