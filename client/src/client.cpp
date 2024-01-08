/**
 * @file client.cpp
 * @brief
 * @date 04-12-2023
 */

#include "client.hpp"

/**
 * @brief Construct a new rtype::Client::Client object
 */
rtype::Client::Client()
: _running(true), _start(std::chrono::system_clock::now()), _ecs(initECS()), _graphical(std::make_unique<SFML>())
{
    std::cout << "This is the R-Type Client" << std::endl;
    srand(std::time(0));
    _scene = MENU;
}

/**
 * @brief Destroy the rtype::Client::Client object
 */
rtype::Client::~Client()
{
    std::cout << "Goodbye" << std::endl;
}

/**
 * @brief Initialize the ECS
 *
 * @return ECS
 */
ECS rtype::Client::initECS()
{
    ECS ecs;
    ecs.registerComponent<Position>();
    ecs.registerComponent<Health>();
    ecs.registerComponent<Velocity>();
    return ecs;
}

/**
 * @brief Initialize the player and add it to the ECS
 *
 */
void rtype::Client::initPlayer()
{
    _players.push_back(_ecs.createEntity());
    _ecs.addComponent<Position>(_players[0], {100, 100});
    _ecs.addComponent<Health>(_players[0], 100);
    _ecs.addComponent<Velocity>(_players[0], {1, 1, 2});
}

/**
 * @brief Draw the menu
 *
 */
void rtype::Client::drawMenu()
{
    _graphical->clear();
    _graphical->draw("parallax80", 0,0,1,0,1980, 1080);
    _graphical->draw("logo", 600, 300, 1, 0, 0, 0);
    _graphical->display();
}

/**
 * @brief Draw the multiplayer menu
 *
 */
void rtype::Client::drawMultiplayer()
{
    _graphical->clear();
    _graphical->draw("parallax100", 0, 0, 1, 1, 1920, 1080);
    _graphical->draw("parallax80", 0, 0, 1, 1, 1920, 1080);
    _graphical->draw("parallax60", 0, 0, 1, 1, 1920, 1080);
    _graphical->draw("player_red", 100, 100, 1, 1, 100, 100);
    _graphical->display();
}

/**
 * @brief Draw the game
 *
 */
void rtype::Client::drawGame()
{
}

/**
 * @brief Draw the settings
 *
 */
void rtype::Client::drawSettings()
{
}

/**
 * @brief Draw the end screen
 *
 */
void rtype::Client::drawEnd()
{
}


/**
 * @brief Manage the draw of the scene
 *
 */
void rtype::Client::manage_draw_scene()
{
    switch (_scene) {
        case MENU:
            drawMenu();
            break;
        case MULTIPLAYER:
            drawMultiplayer();
            break;
        case GAME:
            drawGame();
            break;
        case SETTINGS:
            drawSettings();
            break;
        case END:
            drawEnd();
            break;
        default:
            break;
    }
}

/**
 * @brief Run the game loop
 *
 * @param sender Network::ISender to send data to the server
 * @param receive Network::Receive to receive data from the server
 * @param port int port to use for the client
 */
void rtype::Client::gameLoop(ISender& sender, IReceiver& receive, int port)
{
    while (_running) {
        _graphical->handleEvents();

        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start).count();

        if (elapsed > 1000) {
            _start = now;
            // std::string data = std::to_string(_players[0].getComponent<Position>().x) + " "
            //                  + std::to_string(_players[0].getComponent<Position>().y) + " "
            //                  + std::to_string(port);
            std::string data = std::to_string(_ecs.getComponent<Position>(_players[0])->x) + " "
                             + std::to_string(_ecs.getComponent<Position>(_players[0])->y) + " "
                             + std::to_string(port);

            sender.send(data);
        }
        manage_draw_scene();
    }
}
