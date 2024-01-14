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
    int rotation;
    std::string texture;
    int width, height, startX, startY;
    float scale;

    Attributes(int health, int rotation, std::string texture, int width, int height, int startX, int startY, float scale) : health(health), texture(texture), width(width), height(height), startX(startX), startY(startY), scale(scale) {}
};

std::map<std::string, Attributes> createEnemyTypes()
{
    std::map<std::string, Attributes> associations;
    std::string crawler = "crawler";
    std::string typesheet8 = "r_typesheet8";
    associations[crawler] = Attributes(100, 180, typesheet8, 32, 32, 0, 0, 3);
    // associations["robot"] = Attributes(100, 180, "r_typesheet9", 55, 55, 0, 0, 3);

    return associations;
}
