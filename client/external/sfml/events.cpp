/**
 * @file events.cpp
 * @brief Implementation of the events functions in SFML
 * @date 09-01-2024
 */

#include "sfml.hpp"

/**
 * @brief Handles the events from the SFML window
 *
 * @return KeyState the state of the keys on the keyboard and of the mouse
 */
KeyState rtype::SFML::handleEvents()
{
    KeyState keyState;
    sf::Event event;

    _window.pollEvent(event);

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
    keyState.zero = sf::Keyboard::isKeyPressed(sf::Keyboard::Num0);
    keyState.one = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
    keyState.two = sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
    keyState.three = sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
    keyState.four = sf::Keyboard::isKeyPressed(sf::Keyboard::Num4);
    keyState.five = sf::Keyboard::isKeyPressed(sf::Keyboard::Num5);
    keyState.six = sf::Keyboard::isKeyPressed(sf::Keyboard::Num6);
    keyState.seven = sf::Keyboard::isKeyPressed(sf::Keyboard::Num7);
    keyState.eight = sf::Keyboard::isKeyPressed(sf::Keyboard::Num8);
    keyState.nine = sf::Keyboard::isKeyPressed(sf::Keyboard::Num9);

    if (keyState.escape || event.type == sf::Event::Closed) {
        keyState.escape = true;
        _window.close();
    }

    return keyState;
}
