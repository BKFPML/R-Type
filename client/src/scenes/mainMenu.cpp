/**
 * @file mainMenu.cpp
 * @brief Handles the rendering of the main menu scene
 * @date 09-01-2024
 */

#include "client.hpp"

/**
 * @brief Draws the main menu
 *
 */
void rtype::Client::drawMainMenu()
{
    _graphical->clear();
    _graphical->drawSprite("outerSpace", 0, 0, 0, 0, 1, 0, 0, 0);
    _graphical->drawSprite("logo", 500, 200, 0, 0, 2, 0, 0, 0);
    _graphical->drawText("Play", 930, 500, 30);
    _graphical->drawText("Settings", 870, 600, 30);
    _graphical->drawText("Quit", 930, 700, 30);
    _graphical->display();
}
