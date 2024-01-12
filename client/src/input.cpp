/**
 * @file inputs.cpp
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

/**
 * @brief perform the set actions
 * 
 * @param action 
 */
void rtype::Client::performAction(Action action) {
    switch (action) {
        case EMPTY:
            break;
        case CLICK_PRESS:
            if (_keys.mouse.left && !_previousKeys.mouse.left) {
                _graphical->playMusic("click", false);
                std::cout << "Left click pressed" << std::endl;
                std::cout << "X: " << _keys.mouse.x << " Y: " << _keys.mouse.y << std::endl;
                if (_currentScene == MAIN_MENU) {
                    if (_keys.mouse.x >= 928 && _keys.mouse.x <= 1052 && _keys.mouse.y >= 502 && _keys.mouse.y <= 534) {
                        _graphical->stopMusic("menu");
                        _currentScene = CONNECTION;
                    }
                    else if (_keys.mouse.x >= 869 && _keys.mouse.x <= 1111 && _keys.mouse.y >= 599 && _keys.mouse.y <= 633) {
                        _graphical->stopMusic("menu");
                        _currentScene = SETTINGS;
                    }
                    else if (_keys.mouse.x >= 924 && _keys.mouse.x <= 1045 && _keys.mouse.y >= 699 && _keys.mouse.y <= 729) {
                        _isRunning = false;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        _graphical->stop();
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
                        sender.send("new " + _received_ip + ":" + std::to_string(_received_port));

                        _currentScene = SELECT_GAME;
                    }

                     else {
                        _input_frames_state.at(0).first = false;
                        _input_frames_state.at(1).first = false;
                    }
                    
                }
                if (_currentScene == SELECT_GAME) {
                    if (_keys.mouse.x >= 748 && _keys.mouse.x <= 1122 && _keys.mouse.y >= 501 && _keys.mouse.y <= 531) {
                        _currentScene = GAME;
                    }
                    else if (_keys.mouse.x >= 748 && _keys.mouse.x <= 1110 && _keys.mouse.y >= 595 && _keys.mouse.y <= 630) {
                        _currentScene = GAME;
                    }
                }
                if (_currentScene == SETTINGS) {
                    if (_keys.mouse.x >= 914 && _keys.mouse.x <= 1040 && _keys.mouse.y >= 799 && _keys.mouse.y <= 833) {
                        int x = 0;
                        for (int i = 2; i < 7; i++) {
                            if (_input_frames_state.at(i).second.size() > 0) {
                                std::cout << "Key " << _input_frames_state.at(i).second << std::endl;
                                for (int j = 2; j < 7; j++) {
                                    std::cout << "vs Key " << _input_frames_state.at(j).second << std::endl;
                                    if (_input_frames_state.at(i).second == _input_frames_state.at(j).second && i != j) {
                                        std::cout << "Please enter different keys" << std::endl;
                                        x = 1;
                                    }
                                }
                            } else {
                                std::cout << "Please fill all the inputs" << std::endl;
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
                        std::cout << "Volume: " << soundVolume << std::endl;
                        _graphical->setVolume(soundVolume);
                    }
                }
            }
            if (_keys.mouse.right) std::cout << "Right click pressed" << std::endl;
            break;
        case MOVE_UP:
            std::cout << "Move up" << std::endl;
            break;
        case MOVE_DOWN:
            std::cout << "Move down" << std::endl;
            break;
        case MOVE_LEFT:
            std::cout << "Move left" << std::endl;
            break;
        case MOVE_RIGHT:
            std::cout << "Move right" << std::endl;
            break;
        case UP:
            if (_keys.up && !_previousKeys.up) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "UP";
                    }
                }
            }
            break;
        case DOWN:
            if (_keys.down && !_previousKeys.down) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "DOWN";
                    }
                }
            }
            break;
        case LEFT:
            if (_keys.left && !_previousKeys.left) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "LEFT";
                    }
                }
            }
            break;
        case RIGHT:
            if (_keys.right && !_previousKeys.right) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "RIGHT";
                    }
                }
            }
            break;

        case SHOOT:
            std::cout << "Shoot" << std::endl;
            break;
        case SPACE:
            if (_keys.space && !_previousKeys.space) {
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first && _input_frames_state.at(i).second.size() < 1) {
                        _input_frames_state.at(i).second += " ";
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
        case DELETE:
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
                 else if (_currentScene == SELECT_GAME) {
                    _currentScene = CONNECTION;
                    sender.send("quit " + _received_ip + ":" + std::to_string(_received_port));
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
                    }
                }
                for (int i = 2; i < 7; i++) {
                    if (_input_frames_state.at(i).first) {
                        _input_frames_state.at(i).second = "a";
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
            std::cout << "Unknown action" << std::endl;
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
        MOVE_UP,    // upAction
        MOVE_DOWN,  // downAction
        MOVE_LEFT,  // leftAction
        MOVE_RIGHT, // rightAction
        SHOOT,      // spaceAction
        EMPTY,      //shiftAction
        EMPTY,      //ctrlAction
        EMPTY,      //altAction
        SHOOT,      //enterAction
        EXIT,      //escapeAction
        EMPTY,      //tabAction
        EMPTY,      //backspaceAction
        MOVE_LEFT,  //aAction
        EMPTY,      //bAction
        EMPTY,      //cAction
        MOVE_RIGHT, //dAction
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
        MOVE_DOWN,  //sAction
        EMPTY,      //tAction
        EMPTY,      //uAction
        EMPTY,      //vAction
        MOVE_UP,    //wAction
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
        DELETE,      //backspaceAction
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
        DELETE,      //backspaceAction
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
 *
 */
void rtype::Client::resetKeyBindings() {
    _keyBindings = defaultKeyBindings();
}

/**
 * @brief maps the keys to the actions
 *
 */
void rtype::Client::handleInput() {
    KeyState keys = _keys;
    KeyBinding keyBindings;

    if (_currentScene == CONNECTION || _currentScene == SELECT_GAME)
        keyBindings = connectionKeyBindings();
    else if (_currentScene == SETTINGS)
        keyBindings = settingsKeyBindings();
    else
        keyBindings = _keyBindings;

    if (keys.mouse.left) performAction(keyBindings.lClickPressAction);
    if (keys.mouse.right) performAction(keyBindings.rClickPressAction);
    if (keys.up) performAction(keyBindings.upAction);
    if (keys.down) performAction(keyBindings.downAction);
    if (keys.left) performAction(keyBindings.leftAction);
    if (keys.right) performAction(keyBindings.rightAction);
    if (keys.space) performAction(keyBindings.spaceAction);
    if (keys.shift) performAction(keyBindings.shiftAction);
    if (keys.ctrl) performAction(keyBindings.ctrlAction);
    if (keys.alt) performAction(keyBindings.altAction);
    if (keys.enter) performAction(keyBindings.enterAction);
    if (keys.escape) performAction(keyBindings.escapeAction);
    if (keys.tab) performAction(keyBindings.tabAction);
    if (keys.backspace) performAction(keyBindings.backspaceAction);
    if (keys.a) performAction(keyBindings.aAction);
    if (keys.b) performAction(keyBindings.bAction);
    if (keys.c) performAction(keyBindings.cAction);
    if (keys.d) performAction(keyBindings.dAction);
    if (keys.e) performAction(keyBindings.eAction);
    if (keys.f) performAction(keyBindings.fAction);
    if (keys.g) performAction(keyBindings.gAction);
    if (keys.h) performAction(keyBindings.hAction);
    if (keys.i) performAction(keyBindings.iAction);
    if (keys.j) performAction(keyBindings.jAction);
    if (keys.k) performAction(keyBindings.kAction);
    if (keys.l) performAction(keyBindings.lAction);
    if (keys.m) performAction(keyBindings.mAction);
    if (keys.n) performAction(keyBindings.nAction);
    if (keys.o) performAction(keyBindings.oAction);
    if (keys.p) performAction(keyBindings.pAction);
    if (keys.q) performAction(keyBindings.qAction);
    if (keys.r) performAction(keyBindings.rAction);
    if (keys.s) performAction(keyBindings.sAction);
    if (keys.t) performAction(keyBindings.tAction);
    if (keys.u) performAction(keyBindings.uAction);
    if (keys.v) performAction(keyBindings.vAction);
    if (keys.w) performAction(keyBindings.wAction);
    if (keys.x) performAction(keyBindings.xAction);
    if (keys.y) performAction(keyBindings.yAction);
    if (keys.z) performAction(keyBindings.zAction);
    if (keys.dot) performAction(keyBindings.dotAction);
    if (keys.zero) performAction(keyBindings.zeroAction);
    if (keys.one) performAction(keyBindings.oneAction);
    if (keys.two) performAction(keyBindings.twoAction);
    if (keys.three) performAction(keyBindings.threeAction);
    if (keys.four) performAction(keyBindings.fourAction);
    if (keys.five) performAction(keyBindings.fiveAction);
    if (keys.six) performAction(keyBindings.sixAction);
    if (keys.seven) performAction(keyBindings.sevenAction);
    if (keys.eight) performAction(keyBindings.eightAction);
    if (keys.nine) performAction(keyBindings.nineAction);
}
