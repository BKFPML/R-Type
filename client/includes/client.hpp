/**
 * @file client.hpp
 * @brief Client class header file
 * @date 29-11-2023
 */

# pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../../engine/includes/network.hpp"

namespace rtype
{
    const std::string WINDOW_NAME = "R-Type";
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    class Client {
        public:
            Client();
            ~Client();

            void run();
            void loadTextures();
            void drawParallax(sf::RenderWindow &window);

        private:
            sf::Texture parallaxTexture1;
            sf::Texture parallaxTexture2;
            sf::Texture parallaxTexture3;

            sf::Sprite parallaxSprite1;
            sf::Sprite parallaxSprite1b;
            sf::Sprite parallaxSprite2;
            sf::Sprite parallaxSprite2b;
            sf::Sprite parallaxSprite3;
            sf::Sprite parallaxSprite3b;
    };
}
