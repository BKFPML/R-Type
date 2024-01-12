/**
 * @file client.cpp
 * @brief
 * @date 04-12-2023
 */

#include "client.hpp"

/**
 * @brief Constructs a new rtype::Client::Client object
 */
rtype::Client::Client(std::string ip, int port)
: _isRunning(true), _start(std::chrono::system_clock::now()), _ecs(initECS()), _graphical(std::make_unique<SFML>()), _currentScene(MAIN_MENU), fps(60), _drawClock(std::chrono::system_clock::now()), _received_port(port), _received_ip(ip), sender(0, "1.1.1.1"), soundVolume(50), _start_bind(std::chrono::system_clock::now())
{
    std::cout << "This is the R-Type Client" << std::endl;
    srand(std::time(0));
    _parallaxPos.push_back(std::make_pair(0, 0));
    _parallaxPos.push_back(std::make_pair(WINDOW_WIDTH, 0));
    _parallaxPos.push_back(std::make_pair(0, 0));
    _parallaxPos.push_back(std::make_pair(WINDOW_WIDTH, 0));
    _parallaxPos.push_back(std::make_pair(0, 0));
    _parallaxPos.push_back(std::make_pair(WINDOW_WIDTH, 0));

    for (int i = 0; i < 7; i++)
        _input_frames_state.push_back(std::make_pair(false, ""));

    _input_frames_state.at(2).second = "UP";
    _input_frames_state.at(3).second = "DOWN";
    _input_frames_state.at(4).second = "LEFT";
    _input_frames_state.at(5).second = "RIGHT";
    _input_frames_state.at(6).second = " ";
    resetKeyBindings();
    _gameKeyBindings = _keyBindings;
    _gameKeyBindings.upAction = MOVE_UP;
    _gameKeyBindings.downAction = MOVE_DOWN;
    _gameKeyBindings.leftAction = MOVE_LEFT;
    _gameKeyBindings.rightAction = MOVE_RIGHT;
    _gameKeyBindings.spaceAction = SHOOT;
}

/**
 * @brief Destroys the rtype::Client::Client object
 */
rtype::Client::~Client()
{
    std::cout << "Goodbye" << std::endl;
}

/**
 * @brief Runs the game loop
 *
 * @param sender Network::ISender to send data to the server
 * @param receive Network::Receive to receive data from the server
 * @param port int port to use for the client
 */
void rtype::Client::gameLoop(IReceiver& receive)
{
    _graphical->playMusic("mainTheme", true);

    while (_isRunning) {
        auto now = std::chrono::system_clock::now();
        std::pair<KeyState, KeyState> keyState = _graphical->handleEvents();
        _keys = keyState.first;
        _previousKeys = keyState.second;
        handleInput();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _start).count() > 1000) {
            _start = now;
            std::string data = std::to_string(_ecs.getComponent<Position>(_players[0])->x) + " "
                             + std::to_string(_ecs.getComponent<Position>(_players[0])->y);

            sender.send(data);
        }
        sceneManager();
    }
    _graphical->stopMusic("mainTheme");
    receive.set_running(false);
}
