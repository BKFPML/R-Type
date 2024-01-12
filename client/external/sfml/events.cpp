/**
 * @file events.cpp
 * @brief Implementation of the events functions in SFML
 * @date 09-01-2024
 */

#include "sfml.hpp"

/**
 * @brief Initializes the key bindings
 */
void rtype::SFML::init_key_bindings()
{
    keyState.mouse.x = 0;
    keyState.mouse.y = 0;
    keyState.mouse.left = false;
    keyState.mouse.right = false;
    keyState.up = false;
    keyState.down = false;
    keyState.left = false;
    keyState.right = false;
    keyState.space = false;
    keyState.shift = false;
    keyState.ctrl = false;
    keyState.alt = false;
    keyState.enter = false;
    keyState.escape = false;
    keyState.tab = false;
    keyState.backspace = false;
    keyState.a = false;
    keyState.b = false;
    keyState.c = false;
    keyState.d = false;
    keyState.e = false;
    keyState.f = false;
    keyState.g = false;
    keyState.h = false;
    keyState.i = false;
    keyState.j = false;
    keyState.k = false;
    keyState.l = false;
    keyState.m = false;
    keyState.n = false;
    keyState.o = false;
    keyState.p = false;
    keyState.q = false;
    keyState.r = false;
    keyState.s = false;
    keyState.t = false;
    keyState.u = false;
    keyState.v = false;
    keyState.w = false;
    keyState.x = false;
    keyState.y = false;
    keyState.z = false;
    keyState.zero = false;
    keyState.one = false;
    keyState.two = false;
    keyState.three = false;
    keyState.four = false;
    keyState.five = false;
    keyState.six = false;
    keyState.seven = false;
    keyState.eight = false;
    keyState.nine = false;
}

/**
 * @brief Handles the events from the SFML window
 *
 * @return KeyState the state of the keys on the keyboard and of the mouse
 */
std::pair<KeyState, KeyState> rtype::SFML::handleEvents()
{
    sf::Event event;

    _window.pollEvent(event);

    KeyState previousKeyState = keyState;

    keyState.mouse.x = sf::Mouse::getPosition(_window).x;
    keyState.mouse.y = sf::Mouse::getPosition(_window).y;
    keyState.mouse.left = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    keyState.mouse.right = sf::Mouse::isButtonPressed(sf::Mouse::Right);

    keyState.up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    keyState.down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    keyState.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    keyState.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    keyState.space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    keyState.shift = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    keyState.ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
    keyState.alt = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
    keyState.enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
    keyState.escape = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    keyState.tab = sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
    keyState.backspace = sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
    keyState.a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    keyState.b = sf::Keyboard::isKeyPressed(sf::Keyboard::B);
    keyState.c = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
    keyState.d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    keyState.e = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    keyState.f = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
    keyState.g = sf::Keyboard::isKeyPressed(sf::Keyboard::G);
    keyState.h = sf::Keyboard::isKeyPressed(sf::Keyboard::H);
    keyState.i = sf::Keyboard::isKeyPressed(sf::Keyboard::I);
    keyState.j = sf::Keyboard::isKeyPressed(sf::Keyboard::J);
    keyState.k = sf::Keyboard::isKeyPressed(sf::Keyboard::K);
    keyState.l = sf::Keyboard::isKeyPressed(sf::Keyboard::L);
    keyState.m = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
    keyState.n = sf::Keyboard::isKeyPressed(sf::Keyboard::N);
    keyState.o = sf::Keyboard::isKeyPressed(sf::Keyboard::O);
    keyState.p = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
    keyState.q = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    keyState.r = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    keyState.s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    keyState.t = sf::Keyboard::isKeyPressed(sf::Keyboard::T);
    keyState.u = sf::Keyboard::isKeyPressed(sf::Keyboard::U);
    keyState.v = sf::Keyboard::isKeyPressed(sf::Keyboard::V);
    keyState.w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    keyState.x = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
    keyState.y = sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
    keyState.z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    keyState.dot = sf::Keyboard::isKeyPressed(sf::Keyboard::Period);
    keyState.zero = sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0);
    keyState.one = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1);
    keyState.two = sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2);
    keyState.three = sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3);
    keyState.four = sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4);
    keyState.five = sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5);
    keyState.six = sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6);
    keyState.seven = sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7);
    keyState.eight = sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8);
    keyState.nine = sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9);

    return std::make_pair(keyState, previousKeyState);
}
