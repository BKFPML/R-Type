/**
 * @file client.hpp
 * @brief Client class header file
 * @date 29-11-2023
 */

# pragma once

#include <iostream>
#include <chrono>
#include "../external/sfml.hpp"

enum ClientScene {
    MAIN_MENU,
    CONNECTION,
    GAME,
    SETTINGS,
    GAME_OVER
};

namespace rtype
{
    class Client {
        public:
            Client();
            ~Client();

            ECS initECS();
            void initPlayer();
            void gameLoop(ISender& sender, IReceiver& receive, int port);
            void sceneManager();
            void drawMainMenu();
            void drawConnection();
            void drawGame();
            void drawParallax();
            void drawSettings();
            void drawEnd();
            void handleKeys(KeyState keys);

        private:
            std::unique_ptr<IGraphical> _graphical;
            bool _running;
            std::chrono::_V2::system_clock::time_point _start;
            std::chrono::_V2::system_clock::time_point _drawClock;
            ECS _ecs;
            std::vector<ECS::Entity> _players;
            std::vector<std::pair<int, int>> _parallaxPos;
            ClientScene _scene;
            int fps;

    };
}
