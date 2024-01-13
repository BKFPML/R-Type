/**
 * @file client.hpp
 * @brief Client class header file
 * @date 29-11-2023
 */

# pragma once

#include <iostream>
#include <chrono>
#include <cmath>
#include "./input.hpp"
#include "../external/sfml/sfml.hpp"
#include "../../../engine/includes/ECS.hpp"
#include "../../../engine/includes/network_library/boost_udp.hpp"
#include "./IGraphical.hpp"

enum ClientScene {
    MAIN_MENU,
    CONNECTION,
    WAITING_ROOM,
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
            void initPlayer(std::vector<std::string> data_split);
            void deletePlayer(std::vector<std::string> data_split);
            void gameLoop(IReceiver& receive);
            void performAction(Action action, bool performAction);
            void sceneManager();
            void drawMainMenu();
            void drawConnection();
            void drawGame();
            void drawParallax();
            void drawSky();
            void drawSettings();
            void drawEnd();
            void drawWaitingRoom();
            void handleInput();
            void resetKeyBindings();
            void drawEntities();
            void doMovement(Action direction);
            void rebind(int setting, std::string key);
            void unbind(Action action);
            void doShooting();
            void parse_data_received(IReceiver& receive);
            int nbPlayersInRoom();
            void launchSinglePlayer();
            std::string ecsToJsonString ();
            std::vector<std::string> split(const std::string& str, const std::string& delim);

        private:
            bool _isRunning;
            int fps;
            ECS _ecs;
            std::unique_ptr<IGraphical> _graphical;
            std::chrono::system_clock::time_point _start;
            std::chrono::system_clock::time_point _drawClock;
            std::chrono::system_clock::time_point _start_bind;
            ECS::Entity _player;
            std::vector<std::pair<int, int>> _parallaxPos;
            std::vector<std::pair<int, int>> _skyPos;
            ClientScene _currentScene;
            KeyBinding _keyBindings;
            KeyBinding _gameKeyBindings;
            KeyState _keys;
            KeyState _previousKeys;
            std::vector<std::pair<bool, std::string>> _input_frames_state;
            UDPBoostNetwork::UDPSender sender;
            std::string _received_ip;
            int _received_port;
            int soundVolume;
            int level_selected;
            int id;
            bool _singlePlayer;
    };
}
