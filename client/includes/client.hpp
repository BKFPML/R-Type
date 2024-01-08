/**
 * @file client.hpp
 * @brief Client class header file
 * @date 29-11-2023
 */

# pragma once

#include <iostream>
#include <chrono>
#include "../external/sfml.hpp"

namespace rtype
{
    class Client {
        public:
            Client();
            ~Client();

            ECS initECS();
            void initPlayer();
            void gameLoop(ISender& sender, IReceiver& receive, int port);
            void handleKeys(KeyState keys);

        private:
            std::unique_ptr<IGraphical> _graphical;
            bool _running;
            std::chrono::_V2::system_clock::time_point _start;
            ECS _ecs;
            std::vector<ECS::Entity> _players;
    };
}
