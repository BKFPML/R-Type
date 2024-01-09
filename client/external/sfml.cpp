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
#include "outerSpace.h"
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
    initTextures("outerSpace", outerSpace, outerSpace_len);
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
void rtype::SFML::handleEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        }
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            _window.close();
    }
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
        if (s.first == sprite) {
            s.second->setPosition(x, y);
            s.second->setScale(scale, scale);
            s.second->setRotation(rotation);
            if (size_x != 0 && size_y != 0)
                s.second->setTextureRect(sf::IntRect(0, 0, size_x, size_y));
            sf::FloatRect bounds = s.second->getLocalBounds();
            s.second->setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

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
    sf::FloatRect bounds = this->text.getLocalBounds();
    this->text.setOrigin(bounds.width / 2, bounds.height / 2);
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
