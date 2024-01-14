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
    _graphical->drawSprite("spaceGarage", 0, 0, 0, 0, 1, 0, 0, 0);
    _graphical->drawText("Settings", 760, 100, 50);
    for (int i = 2; i < 7; i++) {
        if (_input_frames_state.at(i).first == true) {
            _graphical->drawSprite("letter_box", 660, 140 + i * 100, 0, 0, 0.6, 0, 90, 4);
        }
        if (_input_frames_state.at(i).second == " ")
            _graphical->drawText("Space", 675, 100 + i * 100, 30);
        else
            _graphical->drawText(_input_frames_state.at(i).second, 675, 100 + i * 100, 30);
    }

    _graphical->drawText("Up", 350, 300, 30);
    _graphical->drawText("Down", 350, 400, 30);
    _graphical->drawText("Left", 350, 500, 30);
    _graphical->drawText("Right", 350, 600, 30);
    _graphical->drawText("Shoot", 350, 700, 30);

    _graphical->drawText("FPS", 1350, 300, 30);
    if (fps == 30)
        _graphical->drawSprite("fps_30_60", 1210, 390, 0, 0, 0.6, 0, 0, 0);
    else if (fps == 60)
        _graphical->drawSprite("fps_30_60", 1345, 390, 0, 0, 0.6, 0, 0, 0);
    else
        _graphical->drawSprite("fps_120", 1485, 390, 0, 0, 0.6, 0, 0, 0);
    _graphical->drawText("30", 1225, 400, 30);
    _graphical->drawText("60", 1360, 400, 30);
    _graphical->drawText("120", 1495, 400, 30);

    _graphical->drawText("Music/SFX", 1275, 500, 30);
    _graphical->drawSprite("bar", 1175, 600, 0, 0, 0.45, 0, 0, 0);
    _graphical->drawSprite("button", 1183 + soundVolume * 4, 585, 4.05, 585, 0.2, 0, 0, 0);
    _graphical->drawText("Exit", 920, 800, 30);

    _graphical->display();
}
