/**
 * @file sfml.cpp
 * @brief Implementation of the SFML library encapsulation
 * @date 28-12-2023
 */

#include "sfml.hpp"
#include "../includes/keystates.hpp"
#include "r_typesheet5.h"
#include "parallax100.h"
#include "parallax80.h"
#include "parallax60.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_NAME "R-Type"

/**
 * @brief Construct a new rtype::SFML::SFML object
 */
rtype::SFML::SFML()
: _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME)
{
    std::cout << "SFML Client" << std::endl;
    loadTextures();

    // ! TEMP
    playersSprites[0].setPosition(rand() % 300 + 200, rand() % 500 + 200);
    playersSprites[0].setScale(5, 5);
    playersSprites[0].setTextureRect(sf::IntRect(0, 0, 34, 34));
    playersSprites[0].setRotation(180);
}

/**
 * @brief Destroy the rtype::SFML::SFML object
 */
rtype::SFML::~SFML()
{
    std::cout << "Goodbye" << std::endl;
}

/**
 * @brief Load the textures for the client's sprites
 */
void rtype::SFML::loadTextures()
{
    if (!parallaxTexture1.loadFromMemory(parallax100, parallax100_len))
        std::cerr << "Error loading embedded Parallax100.png" << std::endl;
    if (!parallaxTexture2.loadFromMemory(parallax80, parallax80_len))
        std::cerr << "Error loading embedded Parallax80.png" << std::endl;
    if (!parallaxTexture3.loadFromMemory(parallax60, parallax60_len))
        std::cerr << "Error loading embedded Parallax60.png" << std::endl;
    if (!playerTexture.loadFromMemory(r_typesheet5, r_typesheet5_len))
        std::cerr << "Error loading embedded r-typesheet5.gif" << std::endl;

    planeSprite.setTexture(playerTexture);
    playersSprites.push_back(planeSprite);

    parallaxSprite1.setTexture(parallaxTexture1);
    parallaxSprite1b.setTexture(parallaxTexture1);
    parallaxSprite2.setTexture(parallaxTexture2);
    parallaxSprite2b.setTexture(parallaxTexture2);
    parallaxSprite3.setTexture(parallaxTexture3);
    parallaxSprite3b.setTexture(parallaxTexture3);

    parallaxSprite1.setPosition(0, 0);
    parallaxSprite1b.setPosition(WINDOW_WIDTH, 0);
    parallaxSprite2.setPosition(0, 0);
    parallaxSprite2b.setPosition(WINDOW_WIDTH, 0);
    parallaxSprite3.setPosition(0, 0);
    parallaxSprite3b.setPosition(WINDOW_WIDTH, 0);
}

/**
 * @brief Handle the events from the SFML window
 *
 * @return KeyState the state of the keys on the keyboard
 */
KeyState rtype::SFML::handleEvents()
{
    KeyState keyState;

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

    return keyState;
}

/**
 * @brief Draw the background parallax effect
 *
 * @param window sf::RenderWindow to draw the parallax effect on
 */
void rtype::SFML::drawParallax(sf::RenderWindow &window)
{
    float parallaxSpeed1 = 0.5f;
    float parallaxSpeed2 = 0.6f;
    float parallaxSpeed3 = 0.7f;

    parallaxSprite1.move(-parallaxSpeed1, 0);
    parallaxSprite1b.move(-parallaxSpeed1, 0);
    parallaxSprite2.move(-parallaxSpeed2, 0);
    parallaxSprite2b.move(-parallaxSpeed2, 0);
    parallaxSprite3.move(-parallaxSpeed3, 0);
    parallaxSprite3b.move(-parallaxSpeed3, 0);

    if (parallaxSprite1.getPosition().x < -parallaxSprite1.getLocalBounds().width)
        parallaxSprite1.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite1b.getPosition().x < -parallaxSprite1b.getLocalBounds().width)
        parallaxSprite1b.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite2.getPosition().x < -parallaxSprite2.getLocalBounds().width)
        parallaxSprite2.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite2b.getPosition().x < -parallaxSprite2b.getLocalBounds().width)
        parallaxSprite2b.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite3.getPosition().x < -parallaxSprite3.getLocalBounds().width)
        parallaxSprite3.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite3b.getPosition().x < -parallaxSprite3b.getLocalBounds().width)
        parallaxSprite3b.setPosition(WINDOW_WIDTH, 0);

    window.draw(parallaxSprite1);
    window.draw(parallaxSprite1b);
    window.draw(parallaxSprite2);
    window.draw(parallaxSprite2b);
    window.draw(parallaxSprite3);
    window.draw(parallaxSprite3b);
}

/**
 * @brief Draw the window and its elements
 *
 */
void rtype::SFML::drawWindow()
{
    _window.clear(sf::Color::Black);
    drawParallax(_window);
    for (auto& player: playersSprites) {
        _window.draw(player);
    }
    _window.display();
}
