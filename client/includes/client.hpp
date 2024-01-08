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
    MENU,
    MULTIPLAYER,
    GAME,
    SETTINGS,
    END
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
            void manage_draw_scene();
            void drawMenu();
            void drawMultiplayer();
            void drawGame();
            void drawSettings();
            void drawEnd();
            
            

        private:
            std::unique_ptr<IGraphical> _graphical;
            bool _running;
            std::chrono::_V2::system_clock::time_point _start;
            ECS _ecs;
            std::vector<ECS::Entity> _players;
            ClientScene _scene;
    };
}
