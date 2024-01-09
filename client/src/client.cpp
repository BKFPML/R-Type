/**
 * @file client.cpp
 * @brief
 * @date 04-12-2023
 */

#include "client.hpp"

#define HALF_WINDOW_WIDTH WINDOW_WIDTH / 2
#define HALF_WINDOW_HEIGHT WINDOW_HEIGHT / 2

/**
 * @brief Construct a new rtype::Client::Client object
 */
rtype::Client::Client()
: _running(true), _start(std::chrono::system_clock::now()), _ecs(initECS()), _graphical(std::make_unique<SFML>()), _scene(GAME), fps(60), _drawClock(std::chrono::system_clock::now())
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
 * @brief maps the keys returned by the graphical lib to the game keys
 *
 * @param keys KeyState returned by the graphical lib
 */
void rtype::Client::handleKeys(KeyState keys)
{
    if(keys.up)
        std::cout << "UP" << std::endl;
    if(keys.down)
        std::cout << "DOWN" << std::endl;
    if(keys.left)
        std::cout << "LEFT" << std::endl;
    if(keys.right)
        std::cout << "RIGHT" << std::endl;
    if(keys.space)
        std::cout << "SPACE" << std::endl;
    if(keys.shift)
        std::cout << "SHIFT" << std::endl;
    if(keys.a)
        std::cout << "A" << std::endl;
    if(keys.eight)
        std::cout << "8" << std::endl;
}

/**
 * @brief Draw the menu
 *
 */
void rtype::Client::drawMenu()
{
    _graphical->clear();
    _graphical->draw("outerSpace", 960, 540, 1, 0, 0, 0);
    _graphical->draw("logo", 960, 250, 2, 0, 0, 0);
    _graphical->drawText("Singleplayer", 960, 450, 30);
    _graphical->drawText("Multiplayer", 960, 550, 30);
    _graphical->drawText("Settings", 960, 650, 30);
    _graphical->drawText("Quit", 960, 750, 30);
    _graphical->display();
}

/**
 * @brief Draw the multiplayer menu
 *
 */
void rtype::Client::drawMultiplayer()
{
    _graphical->clear();
    _graphical->display();
}

/**
 * @brief Draw the game
 *
 */
void rtype::Client::drawGame()
{
    _graphical->clear();

    drawParallax();

    //! TEMP
    _graphical->draw("player_red", _ecs.getComponent<Position>(_players[0])->x, _ecs.getComponent<Position>(_players[0])->y, 3, 180, 34, 34);

    _graphical->display();
}

/**
 * @brief Draw the background Parallax (three layers)
 *
 */
void rtype::Client::drawParallax()
{
    _parallaxPos[0].first -= 1;
    _parallaxPos[1].first -= 1;
    _parallaxPos[2].first -= 2;
    _parallaxPos[3].first -= 2;
    _parallaxPos[4].first -= 3;
    _parallaxPos[5].first -= 3;

    if (_parallaxPos[0].first <= -HALF_WINDOW_WIDTH)
        _parallaxPos[0].first = HALF_WINDOW_WIDTH + WINDOW_WIDTH;
    if (_parallaxPos[1].first <= -HALF_WINDOW_WIDTH)
        _parallaxPos[1].first = HALF_WINDOW_WIDTH + WINDOW_WIDTH;
    if (_parallaxPos[2].first <= -HALF_WINDOW_WIDTH)
        _parallaxPos[2].first = HALF_WINDOW_WIDTH + WINDOW_WIDTH;
    if (_parallaxPos[3].first <= -HALF_WINDOW_WIDTH)
        _parallaxPos[3].first = HALF_WINDOW_WIDTH + WINDOW_WIDTH;
    if (_parallaxPos[4].first <= -HALF_WINDOW_WIDTH)
        _parallaxPos[4].first = HALF_WINDOW_WIDTH + WINDOW_WIDTH;
    if (_parallaxPos[5].first <= -HALF_WINDOW_WIDTH)
        _parallaxPos[5].first = HALF_WINDOW_WIDTH + WINDOW_WIDTH;

    _graphical->draw("parallax100", _parallaxPos[0].first, _parallaxPos[0].second, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->draw("parallax100", _parallaxPos[1].first, _parallaxPos[1].second, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->draw("parallax80", _parallaxPos[2].first, _parallaxPos[2].second, 1, 1, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->draw("parallax80", _parallaxPos[3].first, _parallaxPos[3].second, 1, 1, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->draw("parallax60", _parallaxPos[4].first, _parallaxPos[4].second, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->draw("parallax60", _parallaxPos[5].first, _parallaxPos[5].second, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
}

/**
 * @brief Draw the settings
 *
 */
void rtype::Client::drawSettings()
{
    _graphical->clear();
    _graphical->draw("spaceGarage", 960, 540, 1, 0, 0, 0);
    _graphical->drawText("Settings", 960, 100, 50);
    _graphical->drawText("Keys", 350, 300, 30);
    _graphical->drawText("Difficulty", 1570, 300, 30);
    _graphical->display();
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
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _drawClock).count() > 1000 / fps) {
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
        _drawClock = std::chrono::system_clock::now();
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
    KeyState keys;

    while (_running) {
        keys = _graphical->handleEvents();

        auto now = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start).count();
        handleKeys(keys);

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
