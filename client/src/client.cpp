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
: _isRunning(true), _start(std::chrono::system_clock::now()), _ecs(initECS()), _graphical(std::make_unique<SFML>()), _currentScene(MAIN_MENU), fps(60), _drawClock(std::chrono::system_clock::now()), _received_port(port), _received_ip(ip), sender(0, "1.1.1.1"), soundVolume(50), _start_bind(std::chrono::system_clock::now()), level_selected(-1), _parser()
{
    std::cout << "This is the R-Type Client" << std::endl;
    srand(std::time(0));
    _parallaxPos.push_back(std::make_pair(0, 0));
    _parallaxPos.push_back(std::make_pair(WINDOW_WIDTH, 0));
    _parallaxPos.push_back(std::make_pair(0, 0));
    _parallaxPos.push_back(std::make_pair(WINDOW_WIDTH, 0));
    _parallaxPos.push_back(std::make_pair(0, 0));
    _parallaxPos.push_back(std::make_pair(WINDOW_WIDTH, 0));
    _skyPos.push_back(std::make_pair(0, 973));
    _skyPos.push_back(std::make_pair(WINDOW_WIDTH, 973));

    for (int i = 0; i < 7; i++)
        _input_frames_state.push_back(std::make_pair(false, ""));

    _input_frames_state.at(0).second = "durbaon";
    _input_frames_state.at(1).second = "192.168.0.138";
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
 * @brief splits a string into a vector of strings based on a delimiter
 *
*/
std::vector<std::string> rtype::Client::split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

/**
 * @brief Destroys the rtype::Client::Client object
 */
rtype::Client::~Client()
{
    std::cout << "Goodbye" << std::endl;
}


void rtype::Client::parse_data_received(IReceiver& receive) {
    try {
        std::vector<std::string> data = receive.get_received_data();

        for (auto& u : data) {
            try {
                for (auto& d : split(u, ";")) {
                    std::cout << "Received: " << d << std::endl;
                    if (split(d, " ").front() == "new") {
                        std::vector<std::string> data_split = split(d, " ");
                        initPlayer(data_split);
                        if (data_split.at(1) == "bullet") {
                            _ecs.createEntity();
                            _ecs.addComponent<Bullet>(_ecs.getEntities().back(), {size_t(std::stoi(data_split.at(2))), ALLY});
                            _ecs.addComponent<Position>(_ecs.getEntities().back(), {std::stof(data_split.at(3)), std::stof(data_split.at(4))});
                            _ecs.addComponent<Sprite>(_ecs.getEntities().back(), {data_split.at(5), std::stoi(data_split.at(6)), std::stoi(data_split.at(7)), std::stoi(data_split.at(8)), std::stoi(data_split.at(9)), std::stof(data_split.at(10))});
                        }
                    }
                    else if (split(d, " ").front() == "delete") {
                        std::vector<std::string> data_split = split(d, " ");
                        deletePlayer(data_split);
                        deleteBullet(data_split);
                    }
                    else if (split(d, " ").front() == "start") {
                        std::vector<std::string> data_split = split(d, " ");
                        _currentScene = GAME;
                    } else if (d.at(0) == '[') {
                        try {
                            auto json = _parser.parseMessage(d);
                            if (json.empty())
                                continue;
                            updatePlayer(json);
                            updateBullet(json);
                        } catch (const std::exception& e) {
                            std::cerr << d << std::endl;
                            std::cerr << "Error parsing message: " << e.what() << std::endl;
                        }
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << u << std::endl;
                std::cerr << "Error split message: " << e.what() << std::endl;
            }
        }
        receive.clear_received_data();
    } catch (const std::exception& e) {
        std::cerr << "Error loop message: " << e.what() << std::endl;
    }
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
        try {
            auto now = std::chrono::system_clock::now();
            parse_data_received(receive);
            std::pair<KeyState, KeyState> keyState = _graphical->handleEvents();
            _keys = keyState.first;
            _previousKeys = keyState.second;
            handleInput();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _start).count() > 1000 && _currentScene == GAME) {
                for (auto& entity : _ecs.getEntities()) {
                    std::cout << "Entity: " << entity << std::endl;
                    if (_ecs.hasComponent<Bullet>(entity)) {
                        std::cout << "Bullet: " << _ecs.getComponent<Bullet>(entity)->id << " " << _ecs.getComponent<Bullet>(entity)->team << std::endl;
                    }
                    if (_ecs.hasComponent<Player>(entity)) {
                        std::cout << "Player: " << _ecs.getComponent<Player>(entity)->id << " " << _ecs.getComponent<Player>(entity)->name << std::endl;
                    }
                    if (_ecs.hasComponent<Position>(entity)) {
                        std::cout << "Position: " << _ecs.getComponent<Position>(entity)->x << " " << _ecs.getComponent<Position>(entity)->y << std::endl;
                    }
                    std::cout << std::endl;
                }
                _start = now;
                sender.send(_parser.playerToJson(_ecs, id));

            }
            sceneManager();
        } catch (const std::exception& e) {
            std::cerr << "Error processing message: " << e.what() << std::endl;
        }
    }
    receive.set_running(false);
    _graphical->stopMusic("mainTheme");
}
