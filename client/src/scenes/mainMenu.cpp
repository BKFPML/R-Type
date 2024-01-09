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
    _graphical->draw("outerSpace", 960, 540, 1, 0, 0, 0);
    _graphical->draw("logo", 960, 250, 2, 0, 0, 0);
    _graphical->drawText("Singleplayer", 960, 450, 30);
    _graphical->drawText("Multiplayer", 960, 550, 30);
    _graphical->drawText("Settings", 960, 650, 30);
    _graphical->drawText("Quit", 960, 750, 30);
    _graphical->display();
}
