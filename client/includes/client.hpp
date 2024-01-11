/**
 * @file client.hpp
 * @brief Client class header file
 * @date 29-11-2023
 */

# pragma once

#include <iostream>
#include <chrono>
#include "./input.hpp"
#include "../external/sfml/sfml.hpp"
#include "../../../engine/includes/ECS.hpp"
#include "../../../engine/includes/network_library/boost_udp.hpp"
#include "./IGraphical.hpp"

enum ClientScene {
    MAIN_MENU,
    CONNECTION,
    SELECT_GAME,
    GAME,
    SETTINGS,
    GAME_OVER
};

namespace rtype
{
    class Client {
        public:
            Client(std::string ip, int port);
            ~Client();

            ECS initECS();
            void initPlayer();
            void gameLoop(IReceiver& receive);
            void performAction(Action action);
            void sceneManager();
            void drawMainMenu();
            void drawConnection();
            void drawGame();
            void drawParallax();
            void drawSettings();
            void drawSelectGame();
            void drawEnd();
            void handleInput();
            void resetKeyBindings();
            void drawEntities();

        private:
            bool _isRunning;
            int fps;
            ECS _ecs;
            std::unique_ptr<IGraphical> _graphical;
            std::chrono::_V2::system_clock::time_point _start;
            std::chrono::_V2::system_clock::time_point _drawClock;
            std::vector<ECS::Entity> _players;
            std::vector<std::pair<int, int>> _parallaxPos;
            ClientScene _currentScene;
            KeyBinding _keyBindings;
            KeyState _keys;
            KeyState _previousKeys;
            std::string _ip;
            std::string _username;
            std::vector<bool> _input_frames_state;
            UDPBoostNetwork::UDPSender sender;
            std::string _received_ip;
            int _received_port;

    };
}
