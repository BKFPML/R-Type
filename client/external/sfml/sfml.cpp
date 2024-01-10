/**
 * @file sfml.cpp
 * @brief Implementation of the SFML library encapsulation
 * @date 28-12-2023
 */

#include "sfml.hpp"

/**
 * @brief Constructs a new rtype::SFML::SFML object
 */
rtype::SFML::SFML()
: _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME)
{
    std::cout << "SFML Client" << std::endl;
    loadAssets();
}

/**
 * @brief Destroys the rtype::SFML::SFML object
 */
rtype::SFML::~SFML()
{
    std::cout << "Goodbye" << std::endl;
}

/**
 * @brief Clears the SFML window
 */
void rtype::SFML::clear()
{
    _window.clear(sf::Color::Black);
}

/**
 * @brief Displays the SFML window
 */
void rtype::SFML::display()
{
    _window.display();
}
