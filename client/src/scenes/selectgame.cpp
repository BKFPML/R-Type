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
    _graphical->drawSprite("outerSpace", 0, 0, 0, 0, 1, 0, 0, 0);
    _graphical->drawText("Connected to server " + _input_frames_state.at(1).second, 50, 50, 16);
    _graphical->drawText("username " + _input_frames_state.at(0).second, 50, 100, 16);
    _graphical->drawText("Select Mode", 770, 400, 30);
    _graphical->drawText("Singleplayer", 750, 500, 30);
    _graphical->drawText("Multiplayer", 760, 600, 30);
    _graphical->display();
}