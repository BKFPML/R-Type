/**
 * @file sfml.cpp
 * @brief Implementation of the SFML library encapsulation
 * @date 28-12-2023
 */

#include "sfml.hpp"
#include "player_red.h"
#include "parallax100.h"
#include "parallax80.h"
#include "parallax60.h"
#include "logo.h"
#include "r_type_font.h"

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
}

/**
 * @brief Destroy the rtype::SFML::SFML object
 */
rtype::SFML::~SFML()
{
    std::cout << "Goodbye" << std::endl;
}

/**
 * @brief load the textures for the client's sprites
 * 
 */
void rtype::SFML::initTextures(std::string name, unsigned char const *sheet, unsigned int size)
{
    textures.push_back(std::make_pair(name, new sf::Texture()));
    if (!textures.back().second->loadFromMemory(sheet, size)) {
        std::cerr << "Error loading texture" << std::endl;
        exit(84);
    }
    sprites.push_back(std::make_pair(name, new sf::Sprite(*textures.back().second)));
}


/**
 * @brief Load the textures for the client's sprites
 */
void rtype::SFML::loadTextures()
{
    initTextures("logo", logo, logo_len);
    initTextures("parallax100", parallax100, parallax100_len);
    initTextures("parallax80", parallax80, parallax80_len);
    initTextures("parallax60", parallax60, parallax60_len);
    initTextures("player_red", player_red, player_red_len);

    if (!font.loadFromMemory(r_type_font, r_type_font_len)) {
        std::cerr << "Error loading font" << std::endl;
        exit(84);
    }
    text.setFont(font);


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
 * @brief Draw a sprite on the SFML window
 *
 * @param sprite std::string path to the sprite
 * @param x int x position of the sprite
 * @param y int y position of the sprite
 */
void rtype::SFML::draw(std::string sprite, int x, int y, float scale = 1.0, int rotation = 0, int size_x = 0, int size_y = 0)
{
    for (auto& s : sprites) {
        // std::cout << s.first << ":" <<sprite <<std::endl;
        if (s.first == sprite) {
            s.second->setPosition(x, y);
            s.second->setScale(scale, scale);
            s.second->setRotation(rotation);
            if (size_x != 0 && size_y != 0)
                s.second->setTextureRect(sf::IntRect(0, 0, size_x, size_y));
            _window.draw(*s.second);
        }
    }
}

/**
 * @brief Draw a text on the SFML window
 *
 * @param text std::string text to draw
 * @param x int x position of the text
 * @param y int y position of the text
 */
void rtype::SFML::drawText(std::string text, int x, int y, int size)
{
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setPosition(x, y);
    _window.draw(this->text);
}

/**
 * @brief Clear the SFML window
 */
void rtype::SFML::clear()
{
    _window.clear(sf::Color::Black);
}

/**
 * @brief Display the SFML window
 */
void rtype::SFML::display()
{
    _window.display();
}