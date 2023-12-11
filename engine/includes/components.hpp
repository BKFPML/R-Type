/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** components.hpp
*/

#pragma once

/**
 * @brief Position component
 * @param x X position
 * @param y Y position
 */
struct Pos {
    float x, y;
    Pos(float x, float y) : x(x), y(y) {}
};

/**
 * @brief Health component
 * @param hp Health points
 */
struct Health {
    int hp;
    Health(int hp) : hp(hp) {}
};

/**
 * @brief Attack component
 * @param damage Damage points dealt by the attack
 */
struct Attack {
    int damage;
    Attack(int damage) : damage(damage) {}
};
