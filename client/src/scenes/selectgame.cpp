/**
 * @file selectgame.cpp
 * @brief 
 * @date 11-01-2024
 */

#include "client.hpp"

/**
 * @brief Draws the select game scene
 * 
 */
void rtype::Client::drawSelectGame()
{
    _graphical->clear();
    _graphical->drawSprite("outerSpace", 0, 0, 1, 0, 0, 0);
    _graphical->drawText("Select a game", 960, 250, 30);
    _graphical->drawText("Game 1", 960, 500, 30);
    _graphical->drawText("Game 2", 960, 600, 30);
    _graphical->drawText("Game 3", 960, 700, 30);
    _graphical->display();
}