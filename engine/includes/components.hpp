/**
 * @file components.hpp
 * @brief Declaration of the components used in the ECS
 * @date 11-12-2023
 */

#pragma once

#include <cmath>
#include <string>

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
 * @brief Velocity component, normalized
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

/**
 * @brief Damage component
 * @param damage Damage points dealt by the attack
 */
struct Damage {
    int damage;
    Damage(int damage) : damage(damage) {}
};

/**
 * @brief Immunity component
 * @param frames Number of frames of immunity
 */
struct Immunity {
    int frames;
    Immunity(int frames) : frames(frames) {}
};

/**
 * @brief Player component
 * @param id ID of the player
 */
struct Player{
    int id;
    Player(int id) : id(id) {}
};

struct Npc {
    //TODO
};

// *Graphical components

/**
 * @brief Enum that defines the type of graphical entity
 * Used with the GraphicalType component
 */
enum class GraphicalType {
    Sprite,
    Text
};

/**
 * @brief GraphicalType component
 * @param type GraphicalType (Sprite or Text)
 */
struct Graphical {
    GraphicalType type;
    Graphical(GraphicalType type) : type(type) {}
};

/**
 * @brief Sprite component
 * @param texture Texture of the sprite
 * @param width Width of the sprite
 * @param height Height of the sprite
 * @param startX X position of the texture in the sprite sheet
 * @param startY Y position of the texture in the sprite sheet
 * @param scale Scale of the sprite
 */
struct Sprite {
    std::string texture;
    int width, height, startX, startY;
    float scale;
    Sprite(std::string texture, int width, int height, int startX, int startY, float scale) : texture(texture), width(width), height(height), startX(startX), startY(startY), scale(scale) {}
};

/**
 * @brief Text component
 * @param text Text of the entity
 * @param font Font of the text
 * @param size Size of the text
 */
struct Text {
    std::string text;
    std::string font;
    int size;
    Text(std::string text, std::string font, int size) : text(text), font(font), size(size) {}
};
