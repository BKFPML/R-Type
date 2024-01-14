/**
 * @file input.cpp
 * @brief Implementation of the inputs handling
 * @date 09-01-2024
 */

#include "../includes/client.hpp"

bool check_ip_format(std::string ip) {
    int count = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    //max 255.255.255.255
    for (char c : ip) {
        if (c == '.')
            count++;
        if (count == 0 && c != '.')
            i++;
        if (count == 1 && c != '.')
            j++;
        if (count == 2 && c != '.')
            k++;
        if (count == 3 && c != '.')
            l++;
    }
    if (stoi(ip.substr(0, i)) > 255 || stoi(ip.substr(i + 1, j)) > 255 || stoi(ip.substr(i + j + 2, k)) > 255 || stoi(ip.substr(i + j + k + 3, l)) > 255)
        return false;
    if (count != 3 || i > 3 || j > 3 || k > 3 || l > 3 || i == 0 || j == 0 || k == 0 || l == 0)
        return false;
    return true;
}

void rtype::Client::unbind(Action action) {
    _gameKeyBindings.removeAction(action);
}

void rtype::Client::rebind(int setting, std::string key)
{
    Action action;
    switch (setting) {
        case 2:
            unbind(MOVE_UP);
            action = MOVE_UP;
            break;
        case 3:
            unbind(MOVE_DOWN);
            action = MOVE_DOWN;
            break;
        case 4:
            unbind(MOVE_LEFT);
            action = MOVE_LEFT;
            break;
        case 5:
            unbind(MOVE_RIGHT);
            action = MOVE_RIGHT;
            break;
        case 6:
            unbind(SHOOT);
            action = SHOOT;
            break;
    }
    if(key == "a") {_gameKeyBindings.aAction = action;}
    else if(key == "b") {_gameKeyBindings.bAction = action;}
    else if(key == "c") {_gameKeyBindings.cAction = action;}
    else if(key == "d") {_gameKeyBindings.dAction = action;}
    else if(key == "e") {_gameKeyBindings.eAction = action;}
    else if(key == "f") {_gameKeyBindings.fAction = action;}
    else if(key == "g") {_gameKeyBindings.gAction = action;}
    else if(key == "h") {_gameKeyBindings.hAction = action;}
    else if(key == "i") {_gameKeyBindings.iAction = action;}
    else if(key == "j") {_gameKeyBindings.jAction = action;}
    else if(key == "k") {_gameKeyBindings.kAction = action;}
    else if(key == "l") {_gameKeyBindings.lAction = action;}
    else if(key == "m") {_gameKeyBindings.mAction = action;}
    else if(key == "n") {_gameKeyBindings.nAction = action;}
    else if(key == "o") {_gameKeyBindings.oAction = action;}
    else if(key == "p") {_gameKeyBindings.pAction = action;}
    else if(key == "q") {_gameKeyBindings.qAction = action;}
    else if(key == "r") {_gameKeyBindings.rAction = action;}
    else if(key == "s") {_gameKeyBindings.sAction = action;}
    else if(key == "t") {_gameKeyBindings.tAction = action;}
    else if(key == "u") {_gameKeyBindings.uAction = action;}
    else if(key == "v") {_gameKeyBindings.vAction = action;}
    else if(key == "w") {_gameKeyBindings.wAction = action;}
    else if(key == "x") {_gameKeyBindings.xAction = action;}
    else if(key == "y") {_gameKeyBindings.yAction = action;}
    else if(key == "z") {_gameKeyBindings.zAction = action;}
    else if(key == "UP") {_gameKeyBindings.upAction = action;}
    else if(key == "DOWN") {_gameKeyBindings.downAction = action;}
    else if(key == "LEFT") {_gameKeyBindings.leftAction = action;}
    else if(key == "RIGHT") {_gameKeyBindings.rightAction = action;}
    else if(key == " ") {_gameKeyBindings.spaceAction = action;}
}

void rtype::Client::doMovement(Action direction)
{
    switch (direction) {
        case MOVE_UP:
            if (_ecs.getComponent<Position>(_player)->y > 90) {
                _ecs.updateComponent<Position>(_player, [](Position& pos) {
                    pos.y -= 5;
                });
            }
            break;
        case MOVE_DOWN:
            if (_ecs.getComponent<Position>(_player)->y < 1080) {
                _ecs.updateComponent<Position>(_player, [](Position& pos) {
                    pos.y += 5;
                });
            }
            break;
        case MOVE_LEFT:
            if (_ecs.getComponent<Position>(_player)->x > 84) {
                _ecs.updateComponent<Position>(_player, [](Position& pos) {
                    pos.x -= 5;
                });
            }
            break;
        case MOVE_RIGHT:
            if (_ecs.getComponent<Position>(_player)->x < 1920) {
                _ecs.updateComponent<Position>(_player, [](Position& pos) {
                    pos.x += 5;
                });
            }
            break;
        default:
            break;
    }
}

/**
 * @brief tell the server we just shot
 * 
 */
void rtype::Client::doShooting()
{
    Position *pos = _ecs.getComponent<Position>(_player);
    Velocity *vel = _ecs.getComponent<Velocity>(_player);
    Sprite *sprite = _ecs.getComponent<Sprite>(_player);

    // sender.send("new bullet " + std::to_string(pos->x) + " " + std::to_string(pos->y) + " " + std::to_string(vel->x) + " " + std::to_string(vel->y) + " " + sprite->texture + " " + std::to_string(sprite->width) + " " + std::to_string(sprite->height) + " " + std::to_string(sprite->startX) + " " + std::to_string(sprite->startY) + " " + std::to_string(sprite->scale));
    sender.send("new bullet " + std::to_string(pos->x - 50) + " " + std::to_string(pos->y - 85) + " 10 0 bullet 20 14 200 0 4");
}

/**
 * @brief perform the set actions
 *
 * @param action
 */
void rtype::Client::performAction(Action action, bool game_bind_pressed) {
    switch (action) {
        case EMPTY:
            break;
        case MOVE_UP:
            if (game_bind_pressed) {
                doMovement(MOVE_UP);
            }
            break;
        case MOVE_DOWN:
            if (game_bind_pressed) {
                doMovement(MOVE_DOWN);
            }
            break;
        case MOVE_LEFT:
            if (game_bind_pressed) {
                doMovement(MOVE_LEFT);
            }
            break;
        case MOVE_RIGHT:
            if (game_bind_pressed) {
                doMovement(MOVE_RIGHT);
            }
            break;
        case SHOOT:
            if (_keys.space && !_previousKeys.space) {
                doShooting();
            }
            break;
        case CLICK_PRESS:
            if (_keys.mouse.left && !_previousKeys.mouse.left) {
                _graphical->playMusic("click", false);
                if (_currentScene == MAIN_MENU) {
                    if (_keys.mouse.x >= 773 && _keys.mouse.x <= 1146 && _keys.mouse.y >= 498 && _keys.mouse.y <= 534) {
                        _graphical->stopMusic("menu");
                        _currentScene = GAME;
                        launchSinglePlayer();
                    } else if (_keys.mouse.x >= 789 && _keys.mouse.x <= 1134 && _keys.mouse.y >= 599 && _keys.mouse.y <= 635) {
                        _graphical->stopMusic("menu");
                        _currentScene = CONNECTION;
                    }
                    else if (_keys.mouse.x >= 834 && _keys.mouse.x <= 1092 && _keys.mouse.y >= 699 && _keys.mouse.y <= 733) {
                        _graphical->stopMusic("menu");
                        _currentScene = SETTINGS;
                    }
                    else if (_keys.mouse.x >= 889 && _keys.mouse.x <= 1022 && _keys.mouse.y >= 800 && _keys.mouse.y <= 835) {
                        _isRunning = false;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        _graphical->stop();
                    }
                }
                if (_currentScene == WAITING_ROOM) {
                    if (_keys.mouse.x >= 1256 && _keys.mouse.x <= 1377 && _keys.mouse.y >= 400 && _keys.mouse.y <= 432) {
                        level_selected = 0;
                    } else if (_keys.mouse.x >= 1256 && _keys.mouse.x <= 1443 && _keys.mouse.y >= 500 && _keys.mouse.y <= 532) {
                        level_selected = 1;
                    } else if (_keys.mouse.x >= 1256 && _keys.mouse.x <= 1383 && _keys.mouse.y >= 600 && _keys.mouse.y <= 632) {
                        level_selected = 2;
                    } else if (_keys.mouse.x >= 850 && _keys.mouse.x <= 1000 && _keys.mouse.y >= 795 && _keys.mouse.y <= 835 && level_selected != -1 && nbPlayersInRoom() > 0) {
                        sender.send("start " + std::to_string(level_selected));
                    }
                }
                if (_currentScene == CONNECTION) {
                    if (_keys.mouse.x >= 642 && _keys.mouse.x <= 1505 && _keys.mouse.y >= 582 && _keys.mouse.y <= 668) {
                        _input_frames_state.at(1).first = true;
                        _input_frames_state.at(0).first = false;
                    } else if (_keys.mouse.x >= 642 && _keys.mouse.x <= 1505 && _keys.mouse.y >= 719 && _keys.mouse.y <= 811) {
                        _input_frames_state.at(0).first = true;
                        _input_frames_state.at(1).first = false;
                    } else if (_keys.mouse.x >= 842 && _keys.mouse.x <= 1078 && _keys.mouse.y >= 895 && _keys.mouse.y <= 935 && _input_frames_state.at(0).second.size() > 0 && _input_frames_state.at(1).second.size() > 0 && check_ip_format(_input_frames_state.at(1).second)) {
                        _input_frames_state.at(0).first = false;
                        _input_frames_state.at(1).first = false;
                        sender = UDPBoostNetwork::UDPSender(13152, _input_frames_state.at(1).second);
                        sender.send("new player " + _input_frames_state.at(0).second + " " + _received_ip + ":" + std::to_string(_received_port));
                        _currentScene = WAITING_ROOM;
                    }
                     else {
                        _input_frames_state.at(0).first = false;
                        _input_frames_state.at(1).first = false;
                    }
                }
                if (_currentScene == SETTINGS) {
                    if (_keys.mouse.x >= 914 && _keys.mouse.x <= 1040 && _keys.mouse.y >= 799 && _keys.mouse.y <= 833) {
                        int x = 0;
                        for (int i = 2; i < 7; i++) {
                            if (_input_frames_state.at(i).second.size() > 0) {
                                for (int j = 2; j < 7; j++) {
                                    if (_input_frames_state.at(i).second == _input_frames_state.at(j).second && i != j) {
                                        // std::cout << "Please enter different keys" << std::endl;
                                        x = 1;
                                    }
                                }
                            } else {
                                // std::cout << "Please fill all the inputs" << std::endl;
                                x = 1;
                            }
                        }
                        if (x == 0) {
                            _currentScene = MAIN_MENU;
                        }

                    }
                    else if (_keys.mouse.x >= 1233 && _keys.mouse.x <= 1288 && _keys.mouse.y >= 402 && _keys.mouse.y <= 432) {
                        fps = 30;
                    }
                    else if (_keys.mouse.x >= 1355 && _keys.mouse.x <= 1422 && _keys.mouse.y >= 402 && _keys.mouse.y <= 432) {
                        fps = 60;
                    }
                    else if (_keys.mouse.x >= 1502 && _keys.mouse.x <= 1587 && _keys.mouse.y >= 402 && _keys.mouse.y <= 432) {
                        fps = 120;
                    } else if (_keys.mouse.x >= 342 && _keys.mouse.x <= 850 && _keys.mouse.y >= 295 && _keys.mouse.y <= 355) {
                        _input_frames_state.at(2).first = true;
                        _input_frames_state.at(3).first = false;
                        _input_frames_state.at(4).first = false;
                        _input_frames_state.at(5).first = false;
                        _input_frames_state.at(6).first = false;
                    } else if (_keys.mouse.x >= 342 && _keys.mouse.x <= 850 && _keys.mouse.y >= 395 && _keys.mouse.y <= 455) {
                        _input_frames_state.at(3).first = true;
                        _input_frames_state.at(2).first = false;
                        _input_frames_state.at(4).first = false;
                        _input_frames_state.at(5).first = false;
                        _input_frames_state.at(6).first = false;
                    } else if (_keys.mouse.x >= 342 && _keys.mouse.x <= 850 && _keys.mouse.y >= 495 && _keys.mouse.y <= 555) {
                        _input_frames_state.at(4).first = true;
                        _input_frames_state.at(2).first = false;
                        _input_frames_state.at(3).first = false;
                        _input_frames_state.at(5).first = false;
                        _input_frames_state.at(6).first = false;
                    } else if (_keys.mouse.x >= 342 && _keys.mouse.x <= 850 && _keys.mouse.y >= 595 && _keys.mouse.y <= 655) {
                        _input_frames_state.at(5).first = true;
                        _input_frames_state.at(2).first = false;
                        _input_frames_state.at(3).first = false;
                        _input_frames_state.at(4).first = false;
                        _input_frames_state.at(6).first = false;
                    } else if (_keys.mouse.x >= 342 && _keys.mouse.x <= 850 && _keys.mouse.y >= 695 && _keys.mouse.y <= 755) {
                        _input_frames_state.at(6).first = true;
                        _input_frames_state.at(2).first = false;
                        _input_frames_state.at(3).first = false;
                        _input_frames_state.at(4).first = false;
                        _input_frames_state.at(5).first = false;
                    } else {
                        _input_frames_state.at(2).first = false;
                        _input_frames_state.at(3).first = false;
                        _input_frames_state.at(4).first = false;
                        _input_frames_state.at(5).first = false;
                        _input_frames_state.at(6).first = false;
                    }

                }
            }
            if (_keys.mouse.left) {
                if (_currentScene == SETTINGS) {
                    if (_keys.mouse.x >= 1203 && _keys.mouse.x <= 1615 && _keys.mouse.y >= 585 && _keys.mouse.y <= 615) {
                        soundVolume = (_keys.mouse.x - 1203) / 4.05;
                        // std::cout << "Volume: " << soundVolume << std::endl;
                        _graphical->setVolume(soundVolume);
                    }
                }
            }
            if (_keys.mouse.right) std::cout << "Right click pressed" << std::endl;
            break;
        case UP:
            if (_keys.up && !_previousKeys.up) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "UP";
                        rebind(i, "UP");
                    }
                }
            }
            break;
        case DOWN:
            if (_keys.down && !_previousKeys.down) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "DOWN";
                        rebind(i, "DOWN");
                    }
                }
            }
            break;
        case LEFT:
            if (_keys.left && !_previousKeys.left) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "LEFT";
                        rebind(i, "LEFT");
                    }
                }
            }
            break;
        case RIGHT:
            if (_keys.right && !_previousKeys.right) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "RIGHT";
                        rebind(i, "RIGHT");
                    }
                }
            }
            break;

        case SPACE:
            if (_keys.space && !_previousKeys.space) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first && _input_frames_state.at(i).second.size() < 1) {
                        _input_frames_state.at(i).second = " ";
                        rebind(i, " ");
                    }
                }
            }
            break;
        case DOT:
            if (_keys.dot && !_previousKeys.dot) {
                if (_input_frames_state.at(1).first && _input_frames_state.at(1).second.size() < 15) {
                    _input_frames_state.at(1).second += ".";
                } else if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += ".";
                }
            }
            break;
        case DEL:
            if (_keys.backspace && !_previousKeys.backspace) {
                for (int i = 0; i < 2; i++) {
                    if (_input_frames_state.at(i).first && _input_frames_state.at(i).second.size() > 0) {
                        _input_frames_state.at(i).second.pop_back();
                    }
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first && _input_frames_state.at(i).second.size() > 0) {
                        _input_frames_state.at(i).second = "";
                    }
                }
            }
            break;
        case GOBACK:
            if (_keys.escape && !_previousKeys.escape) {
                if (_currentScene == CONNECTION) {
                    _currentScene = MAIN_MENU;
                }
                else if (_currentScene == GAME) {
                    _currentScene = WAITING_ROOM;
                } else if (_currentScene == WAITING_ROOM) {
                    _currentScene = CONNECTION;
                    sender.send("delete player " + std::to_string(_ecs.getComponent<Player>(_player)->id));
                    sender = UDPBoostNetwork::UDPSender(0, "1.1.1.1");
                }
            }
            break;
        case EXIT:
            if (_keys.escape && !_previousKeys.escape) {
                std::cout << "Exit" << std::endl;
                _isRunning = false;
                _graphical->stop();
                sender.send("quit " + _received_ip + ":" + std::to_string(_received_port));
            }
            break;
        case A:
            if (_keys.a && !_previousKeys.a) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "a";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "a";
                        rebind(i, "a");
                    }
                }
            }
            break;
        case B:
            if (_keys.b && !_previousKeys.b) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "b";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "b";
                        rebind(i, "b");
                    }
                }

            }
            break;
        case C:
            if (_keys.c && !_previousKeys.c) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "c";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "c";
                        rebind(i, "c");
                    }
                }
            }
            break;
        case D:
            if (_keys.d && !_previousKeys.d) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "d";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "d";
                        rebind(i, "d");
                    }
                }
            }
            break;
        case E:
            if (_keys.e && !_previousKeys.e) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "e";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "e";
                        rebind(i, "e");
                    }
                }
            }
            break;
        case F:
            if (_keys.f && !_previousKeys.f) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "f";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "f";
                        rebind(i, "f");
                    }
                }
            }
            break;
        case G:
            if (_keys.g && !_previousKeys.g) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "g";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "g";
                        rebind(i, "g");
                    }
                }
            }
            break;
        case H:
            if (_keys.h && !_previousKeys.h) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "h";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "h";
                        rebind(i, "h");
                    }
                }
            }
            break;
        case I:
            if (_keys.i && !_previousKeys.i) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "i";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "i";
                        rebind(i, "i");
                    }
                }
            }
            break;
        case J:
            if (_keys.j && !_previousKeys.j) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "j";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "j";
                        rebind(i, "j");
                    }
                }
            }
            break;
        case K:
            if (_keys.k && !_previousKeys.k) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "k";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "k";
                        rebind(i, "k");
                    }
                }
            }
            break;
        case L:
            if (_keys.l && !_previousKeys.l) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "l";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "l";
                        rebind(i, "l");
                    }
                }
            }
            break;
        case M:
            if (_keys.m && !_previousKeys.m) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "m";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "m";
                        rebind(i, "m");
                    }
                }
            }
            break;
        case N:
            if (_keys.n && !_previousKeys.n) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "n";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "n";
                        rebind(i, "n");
                    }
                }
            }
            break;
        case O:
            if (_keys.o && !_previousKeys.o) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "o";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "o";
                        rebind(i, "o");
                    }
                }
            }
            break;
        case P:
            if (_keys.p && !_previousKeys.p) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "p";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "p";
                        rebind(i, "p");
                    }
                }
            }
            break;
        case Q:
            if (_keys.q && !_previousKeys.q) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "q";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "q";
                        rebind(i, "q");
                    }
                }
            }
            break;
        case R:
            if (_keys.r && !_previousKeys.r) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "r";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "r";
                        rebind(i, "r");
                    }
                }
            }
            break;
        case S:
            if (_keys.s && !_previousKeys.s) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "s";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "s";
                        rebind(i, "s");
                    }
                }
            }
            break;
        case T:
            if (_keys.t && !_previousKeys.t) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "t";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "t";
                        rebind(i, "t");
                    }
                }
            }
            break;
        case U:
            if (_keys.u && !_previousKeys.u) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "u";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "u";
                        rebind(i, "u");
                    }
                }
            }
            break;
        case V:
            if (_keys.v && !_previousKeys.v) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "v";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "v";
                        rebind(i, "v");
                    }
                }
            }
            break;
        case W:
            if (_keys.w && !_previousKeys.w) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "w";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "w";
                        rebind(i, "w");
                    }
                }
            }
            break;
        case X:
            if (_keys.x && !_previousKeys.x) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "x";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "x";
                        rebind(i, "x");
                    }
                }
            }
            break;
        case Y:
            if (_keys.y && !_previousKeys.y) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "y";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "y";
                        rebind(i, "y");
                    }
                }
            }
            break;
        case Z:
            if (_keys.z && !_previousKeys.z) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "z";
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "z";
                        rebind(i, "z");
                    }
                }
            }
            break;
        case ZERO:
            if (_keys.zero && !_previousKeys.zero) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "0";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "0";
                    }
                }
            }
            break;
        case ONE:
            if (_keys.one && !_previousKeys.one) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "1";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "1";
                    }
                }
            }
            break;
        case TWO:
            if (_keys.two && !_previousKeys.two) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "2";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "2";
                    }
                }
            }
            break;
        case THREE:
            if (_keys.three && !_previousKeys.three) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "3";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "3";
                    }
                }
            }
            break;
        case FOUR:
            if (_keys.four && !_previousKeys.four) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "4";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "4";
                    }
                }
            }
            break;
        case FIVE:
            if (_keys.five && !_previousKeys.five) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "5";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "5";
                    }
                }
            }
            break;
        case SIX:
            if (_keys.six && !_previousKeys.six) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "6";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "6";
                    }
                }
            }
            break;
        case SEVEN:
            if (_keys.seven && !_previousKeys.seven) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "7";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "7";
                    }
                }
            }
            break;
        case EIGHT:
            if (_keys.eight && !_previousKeys.eight) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "8";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "8";
                    }
                }
            }
            break;
        case NINE:
            if (_keys.nine && !_previousKeys.nine) {
                if (_input_frames_state.at(0).first && _input_frames_state.at(0).second.size() < 15) {
                    _input_frames_state.at(0).second += "9";
                }
                else if (_input_frames_state.at(1).first) {
                    if (_input_frames_state.at(1).second.size() < 15) {
                        _input_frames_state.at(1).second += "9";
                    }
                }
            }
            break;

        default:
            // std::cout << "Unknown action" << std::endl;
            break;
    }
}

/**
 * @brief returns default keybinds
 *
 * @return KeyBinding keybinds
 */
KeyBinding defaultKeyBindings() {
    return {
        CLICK_PRESS,      // lClickPressAction
        CLICK_PRESS,      // rClickPressAction
        EMPTY,    // upAction
        EMPTY,  // downAction
        EMPTY,  // leftAction
        EMPTY, // rightAction
        EMPTY,      // spaceAction
        EMPTY,      //shiftAction
        EMPTY,      //ctrlAction
        EMPTY,      //altAction
        EMPTY,      //enterAction
        GOBACK,      //escapeAction
        EMPTY,      //tabAction
        EMPTY,      //backspaceAction
        EMPTY,      //aAction
        EMPTY,      //bAction
        EMPTY,      //cAction
        EMPTY,      //dAction
        EMPTY,      //eAction
        EMPTY,      //fAction
        EMPTY,      //gAction
        EMPTY,      //hAction
        EMPTY,      //iAction
        EMPTY,      //jAction
        EMPTY,      //kAction
        EMPTY,      //lAction
        EMPTY,      //mAction
        EMPTY,      //nAction
        EMPTY,      //oAction
        EMPTY,      //pAction
        EMPTY,      //qAction
        EMPTY,      //rAction
        EMPTY,      //sAction
        EMPTY,      //tAction
        EMPTY,      //uAction
        EMPTY,      //vAction
        EMPTY,      //wAction
        EMPTY,      //xAction
        EMPTY,      //yAction
        EMPTY,      //zAction
        EMPTY,     //dotAction
        EMPTY,      //zeroAction
        EMPTY,      //oneAction
        EMPTY,      //twoAction
        EMPTY,      //threeAction
        EMPTY,      //fourAction
        EMPTY,      //fiveAction
        EMPTY,      //sixAction
        EMPTY,      //sevenAction
        EMPTY,      //eightAction
        EMPTY,      //nineAction
    };
}

/**
 * @brief returns connection keybinds
 *
 * @return KeyBinding keybinds
 */
KeyBinding connectionKeyBindings() {
    return {
        CLICK_PRESS,      // lClickPressAction
        CLICK_PRESS,      // rClickPressAction
        EMPTY,    // upAction
        EMPTY,  // downAction
        EMPTY,  // leftAction
        EMPTY, // rightAction
        SPACE,      // spaceAction
        EMPTY,      //shiftAction
        EMPTY,      //ctrlAction
        EMPTY,      //altAction
        EMPTY,      //enterAction
        GOBACK,      //escapeAction
        EMPTY,      //tabAction
        DEL,      //backspaceAction
        A,  //aAction
        B,      //bAction
        C,      //cAction
        D, //dAction
        E,      //eAction
        F,      //fAction
        G,      //gAction
        H,      //hAction
        I,      //iAction
        J,      //jAction
        K,      //kAction
        L,      //lAction
        M,      //mAction
        N,      //nAction
        O,      //oAction
        P,      //pAction
        Q,      //qAction
        R,      //rAction
        S,  //sAction
        T,      //tAction
        U,      //uAction
        V,      //vAction
        W,    //wAction
        X,      //xAction
        Y,      //yAction
        Z,      //zAction
        DOT,     //dotAction
        ZERO,      //zeroAction
        ONE,      //oneAction
        TWO,      //twoAction
        THREE,      //threeAction
        FOUR,      //fourAction
        FIVE,      //fiveAction
        SIX,      //sixAction
        SEVEN,      //sevenAction
        EIGHT,      //eightAction
        NINE,      //nineAction
    };
}

/**
 * @brief returns connection keybinds
 *
 * @return KeyBinding keybinds
 */
KeyBinding settingsKeyBindings() {
    return {
        CLICK_PRESS,      // lClickPressAction
        CLICK_PRESS,      // rClickPressAction
        UP,    // upAction
        DOWN,  // downAction
        LEFT,  // leftAction
        RIGHT, // rightAction
        SPACE,      // spaceAction
        EMPTY,      //shiftAction
        EMPTY,      //ctrlAction
        EMPTY,      //altAction
        EMPTY,      //enterAction
        GOBACK,      //escapeAction
        EMPTY,      //tabAction
        DEL,      //backspaceAction
        A,  //aAction
        B,      //bAction
        C,      //cAction
        D, //dAction
        E,      //eAction
        F,      //fAction
        G,      //gAction
        H,      //hAction
        I,      //iAction
        J,      //jAction
        K,      //kAction
        L,      //lAction
        M,      //mAction
        N,      //nAction
        O,      //oAction
        P,      //pAction
        Q,      //qAction
        R,      //rAction
        S,  //sAction
        T,      //tAction
        U,      //uAction
        V,      //vAction
        W,    //wAction
        X,      //xAction
        Y,      //yAction
        Z,      //zAction
        DOT,     //dotAction
        ZERO,      //zeroAction
        ONE,      //oneAction
        TWO,      //twoAction
        THREE,      //threeAction
        FOUR,      //fourAction
        FIVE,      //fiveAction
        SIX,      //sixAction
        SEVEN,      //sevenAction
        EIGHT,      //eightAction
        NINE,      //nineAction
    };
}

/**
 * @brief reset all keybinds to default setting
 */
void rtype::Client::resetKeyBindings() {
    _keyBindings = defaultKeyBindings();
}

/**
 * @brief maps the keys to the actions
 */
void rtype::Client::handleInput() {
    KeyState keys = _keys;
    KeyBinding keyBindings;

    if (_currentScene == CONNECTION )
        keyBindings = connectionKeyBindings();
    else if (_currentScene == SETTINGS)
        keyBindings = settingsKeyBindings();
    else if (_currentScene == GAME)
        keyBindings = _gameKeyBindings;
    else
        keyBindings = _keyBindings;

    auto now = std::chrono::system_clock::now();
    bool isTimeToPerformAction = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_bind).count() > 10;

    if (keys.mouse.left) performAction(keyBindings.lClickPressAction, isTimeToPerformAction);
    if (keys.mouse.right) performAction(keyBindings.rClickPressAction, isTimeToPerformAction);
    if (keys.up) performAction(keyBindings.upAction, isTimeToPerformAction);
    if (keys.down) performAction(keyBindings.downAction, isTimeToPerformAction);
    if (keys.left) performAction(keyBindings.leftAction, isTimeToPerformAction);
    if (keys.right) performAction(keyBindings.rightAction, isTimeToPerformAction);
    if (keys.space) performAction(keyBindings.spaceAction, isTimeToPerformAction);
    if (keys.shift) performAction(keyBindings.shiftAction, isTimeToPerformAction);
    if (keys.ctrl) performAction(keyBindings.ctrlAction, isTimeToPerformAction);
    if (keys.alt) performAction(keyBindings.altAction, isTimeToPerformAction);
    if (keys.enter) performAction(keyBindings.enterAction, isTimeToPerformAction);
    if (keys.escape) performAction(keyBindings.escapeAction, isTimeToPerformAction);
    if (keys.tab) performAction(keyBindings.tabAction, isTimeToPerformAction);
    if (keys.backspace) performAction(keyBindings.backspaceAction, isTimeToPerformAction);
    if (keys.a) performAction(keyBindings.aAction, isTimeToPerformAction);
    if (keys.b) performAction(keyBindings.bAction, isTimeToPerformAction);
    if (keys.c) performAction(keyBindings.cAction, isTimeToPerformAction);
    if (keys.d) performAction(keyBindings.dAction, isTimeToPerformAction);
    if (keys.e) performAction(keyBindings.eAction, isTimeToPerformAction);
    if (keys.f) performAction(keyBindings.fAction, isTimeToPerformAction);
    if (keys.g) performAction(keyBindings.gAction, isTimeToPerformAction);
    if (keys.h) performAction(keyBindings.hAction, isTimeToPerformAction);
    if (keys.i) performAction(keyBindings.iAction, isTimeToPerformAction);
    if (keys.j) performAction(keyBindings.jAction, isTimeToPerformAction);
    if (keys.k) performAction(keyBindings.kAction, isTimeToPerformAction);
    if (keys.l) performAction(keyBindings.lAction, isTimeToPerformAction);
    if (keys.m) performAction(keyBindings.mAction, isTimeToPerformAction);
    if (keys.n) performAction(keyBindings.nAction, isTimeToPerformAction);
    if (keys.o) performAction(keyBindings.oAction, isTimeToPerformAction);
    if (keys.p) performAction(keyBindings.pAction, isTimeToPerformAction);
    if (keys.q) performAction(keyBindings.qAction, isTimeToPerformAction);
    if (keys.r) performAction(keyBindings.rAction, isTimeToPerformAction);
    if (keys.s) performAction(keyBindings.sAction, isTimeToPerformAction);
    if (keys.t) performAction(keyBindings.tAction, isTimeToPerformAction);
    if (keys.u) performAction(keyBindings.uAction, isTimeToPerformAction);
    if (keys.v) performAction(keyBindings.vAction, isTimeToPerformAction);
    if (keys.w) performAction(keyBindings.wAction, isTimeToPerformAction);
    if (keys.x) performAction(keyBindings.xAction, isTimeToPerformAction);
    if (keys.y) performAction(keyBindings.yAction, isTimeToPerformAction);
    if (keys.z) performAction(keyBindings.zAction, isTimeToPerformAction);
    if (keys.dot) performAction(keyBindings.dotAction, isTimeToPerformAction);
    if (keys.zero) performAction(keyBindings.zeroAction, isTimeToPerformAction);
    if (keys.one) performAction(keyBindings.oneAction, isTimeToPerformAction);
    if (keys.two) performAction(keyBindings.twoAction, isTimeToPerformAction);
    if (keys.three) performAction(keyBindings.threeAction, isTimeToPerformAction);
    if (keys.four) performAction(keyBindings.fourAction, isTimeToPerformAction);
    if (keys.five) performAction(keyBindings.fiveAction, isTimeToPerformAction);
    if (keys.six) performAction(keyBindings.sixAction, isTimeToPerformAction);
    if (keys.seven) performAction(keyBindings.sevenAction, isTimeToPerformAction);
    if (keys.eight) performAction(keyBindings.eightAction, isTimeToPerformAction);
    if (keys.nine) performAction(keyBindings.nineAction, isTimeToPerformAction);
    if (isTimeToPerformAction) _start_bind = std::chrono::system_clock::now();
}
