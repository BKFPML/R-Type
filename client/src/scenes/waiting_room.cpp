/**
 * @file waiting_room.cpp
 * @brief 
 * @date 12-01-2024
 */

#include "client.hpp"

/**
 * @brief Draws the waiting room
 * 
 */
void rtype::Client::drawWaitingRoom()
{
    _graphical->clear();
    _graphical->drawSprite("spaceGarage", 0, 0, 1, 0, 0, 0);
    _graphical->drawText("Waiting room", 660, 100, 50);
    _graphical->drawText("Connected to server " + _input_frames_state.at(1).second, 50, 900, 16);
    _graphical->drawText("username " + _input_frames_state.at(0).second, 50, 950, 16);
    _graphical->drawText("Players", 260, 300, 30);
    for (auto& entity : _ecs.getEntities()) {
        if (_ecs.hasComponent<Player>(entity)) {
            _graphical->drawText(_ecs.getComponent<Player>(entity)->name, 260, 400 + _ecs.getComponent<Player>(entity)->id * 100, 30);
        }
    }
    if (id == 0) {
    _graphical->drawText("Difficulty", 1200, 300, 30);
    if (level_selected == 0)
        _graphical->drawSprite("letter_box", 1256, 440, 0.6, 0, 90, 4);
    else if (level_selected == 1)
        _graphical->drawSprite("letter_box", 1256, 540, 0.6, 0, 90, 4);
    else if (level_selected == 2)
        _graphical->drawSprite("letter_box", 1256, 640, 0.6, 0, 90, 4);
    _graphical->drawText("Easy", 1260, 400, 30);
    _graphical->drawText("Medium", 1260, 500, 30);
    _graphical->drawText("Hard", 1260, 600, 30);
    }
    if (id == 0 && nbPlayersInRoom() > 1)
        _graphical->drawText("Start", 860, 800, 30);
    else if (id == 0 && nbPlayersInRoom() == 1)
        _graphical->drawText("Waiting for players", 660, 800, 30);
    else if (id != 0)
        _graphical->drawText("Waiting for host to start", 560, 800, 30);
    _graphical->display();
}