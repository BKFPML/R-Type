/**
 * @file sceneManager.cpp
 * @brief Contains the implementation of the sceneManager method.
 * @date 09-01-2024
 */

#include "client.hpp"

/**
 * @brief Manages the rendering of the different scenes based on the current game state
 *
 */
void rtype::Client::sceneManager()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _drawClock).count() > 1000 / fps) {
        switch (_currentScene) {
            case MAIN_MENU:
                drawMainMenu();
                break;
            case CONNECTION:
                drawConnection();
                break;
            case WAITING_ROOM:
                drawWaitingRoom();
                break;
            case GAME:
                drawGame();
                break;
            case SETTINGS:
                drawSettings();
                break;
            case GAME_OVER:
                drawEnd();
                break;
            default:
                break;
        }
        _drawClock = std::chrono::system_clock::now();
    }
}
