/**
 * @file settings.cpp
 * @brief Handles the rendering of the settings scene
 * @date 09-01-2024
 */

#include "client.hpp"

/**
 * @brief Draws the settings
 *
 */
void rtype::Client::drawSettings()
{
    _graphical->clear();
    _graphical->draw("spaceGarage", 960, 540, 1, 0, 0, 0);
    _graphical->drawText("Settings", 960, 100, 50);
    _graphical->drawText("Keys", 350, 300, 30);
    _graphical->drawText("Difficulty", 1570, 300, 30);
    _graphical->display();
}
