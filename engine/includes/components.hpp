/**
 * @file components.hpp
 * @brief Declaration of the components used in the ECS
 * @date 11-12-2023
 */

#pragma once

#include <cmath>
#include <string>

/**
 * @brief HealthPack Component
 * @param hp Health points
 */
struct HealthPack {
    int hp;
    HealthPack(int hp) : hp(hp) {}
};

/**
 * @brief Spawn Time component
 * @param time Time of the spawn
 */
struct SpawnTime {
    float time;
    SpawnTime(float time) : time(time) {}
};

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
    Velocity(float x, float y) : x(x), y(y) {
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
 * @brief Freeze component
 * @param frames Number of frames of freeze
 */
struct Freeze {
    int frames;
    Freeze(int frames) : frames(frames) {}
};

/**
 * @brief Player component
 * @param id ID of the player
 */
struct Player{
    int id;
    std::string name;
    Player(int id, std::string name) : id(id), name(name) {}
};

/**
 * @brief Types of different bullets
 *
 * ALLY: Bullet shot by a player
 * ENEMY: Bullet shot by an enemy
 * DESTROYED: Bullet that has been destroyed
 */
enum BulletTeam {
    ALLY,
    ENEMY,
    DESTROYED
};

/**
 * @brief Bullet component
 *
 * @param id ID of the bullet
 * @param team BulletTeam (ALLY, ENEMY or DESTROYED)
 */
struct Bullet {
    size_t id;
    BulletTeam team;
    Bullet(size_t id, BulletTeam team) : id(id), team(team) {}
};

/**
 * @brief Enemy component
 * @param name Name of the enemy
 */
struct Enemy {
    std::string name;
    Enemy(std::string name) : name(name) {}
};

// *Graphical components

/**
 * @brief Enum that defines the type of graphical entity used with the GraphicalType component
 */
enum class GraphicalType {
    Sprite,
    Text
};

/**
 * @brief Enum that defines the type of collision used with the Collision component
 *
 * ATTACK: The entity is an attack
 * DEFEND: The entity is a defense
 * HEALTH_PACK: The entity is a health pack
 */
enum CollisionType {
    ATTACK,
    DEFEND,
    HEALTH_PACK
};

/**
 * @brief Collision component
 * @param type CollisionType (ATTACK, DEFEND or HEALTH_PACK)
 */
struct Collision {
    CollisionType type;
    Collision(CollisionType type) : type(type) {}
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
 * @brief Sprite component, stores sprites and related data
 */
struct Sprite {
    std::string texture;
    int width, height, startX, startY;
    float scale;
    /**
     * @brief Construct a new Sprite object
     *
     * @param texture Texture of the sprite
     * @param width Width of the sprite
     * @param height Height of the sprite
     * @param startX X position of the texture in the sprite sheet
     * @param startY Y position of the texture in the sprite sheet
     * @param scale Scale of the sprite
     */
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
