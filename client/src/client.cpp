/**
 * @file client.cpp
 * @brief
 * @date 04-12-2023
 */

#include "client.hpp"


/**
 * @brief Constructs a new rtype::Client::Client object
 */
rtype::Client::Client()
: _isRunning(true), _start(std::chrono::system_clock::now()), _ecs(initECS()), _graphical(std::make_unique<SFML>()), _currentScene(MAIN_MENU), fps(60), _drawClock(std::chrono::system_clock::now())
{
    std::cout << "This is the R-Type Client" << std::endl;
    srand(std::time(0));

    _parallaxPos.push_back(std::make_pair(HALF_WINDOW_WIDTH, HALF_WINDOW_HEIGHT));
    _parallaxPos.push_back(std::make_pair(HALF_WINDOW_WIDTH + WINDOW_WIDTH, HALF_WINDOW_HEIGHT));
    _parallaxPos.push_back(std::make_pair(HALF_WINDOW_WIDTH, HALF_WINDOW_HEIGHT));
    _parallaxPos.push_back(std::make_pair(HALF_WINDOW_WIDTH + WINDOW_WIDTH, HALF_WINDOW_HEIGHT));
    _parallaxPos.push_back(std::make_pair(HALF_WINDOW_WIDTH, HALF_WINDOW_HEIGHT));
    _parallaxPos.push_back(std::make_pair(HALF_WINDOW_WIDTH + WINDOW_WIDTH, HALF_WINDOW_HEIGHT));
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
void rtype::Client::gameLoop(ISender& sender, IReceiver& receive, int port)
{
    KeyState keys;

    while (_isRunning) {
        keys = _graphical->handleEvents();

        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start).count();
        handleKeys(keys);

        if (elapsed > 1000) {
            _start = now;
            std::string data = std::to_string(_ecs.getComponent<Position>(_players[0])->x) + " "
                             + std::to_string(_ecs.getComponent<Position>(_players[0])->y) + " "
                             + std::to_string(port);

            sender.send(data);
        }
        sceneManager();
    }
}
