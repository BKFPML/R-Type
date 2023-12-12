/**
 * @file components.hpp
 * @brief Declaration of the components used in the ECS
 * @date 11-12-2023
 */

#pragma once

#include <cmath>

/**
 * @brief Position component
 * @param x X position
 * @param y Y position
 */
struct Position {
    float x, y;
    Position(float x, float y) : x(x), y(y) {}
};

/**
 * @brief Velocity component
 * @param x X velocity
 * @param y Y velocity
 * @param magnitude Magnitude of the velocity vector
 */
struct Velocity {
    float x, y;
    float magnitude;
    // Constructor
    Velocity(float x, float y, float magnitude) : x(x), y(y), magnitude(magnitude) {
        normalize();
    }
    // Method to normalize the vector
    void normalize() {
        float len = std::sqrt(x * x + y * y);
        // Check if length is not zero to avoid division by zero
        if (len != 0) {
            x /= len;
            y /= len;
        }
    }
};

/**
 * @brief Rotation component
 * @param angle Angle of rotation
 */
struct Rotation {
    float angle;
    Rotation(float angle) : angle(angle) {}
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

/**
 * @brief Enum that defines the status of an entity
 * Used with the Status component
 */
enum class StatusType {
    ALLY,
    ENEMY
};

/**
 * @brief Status component
 * @param status StatusType (ALLY or ENEMY)
 */
struct Status {
    StatusType status;
    Status(StatusType status) : status(status) {}
};

