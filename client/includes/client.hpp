/**
 * @file client.hpp
 * @brief Client class header file
 * @date 29-11-2023
 */

# pragma once

#include <iostream>
#include <ctime>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "network.hpp"
#include "../../engine/includes/ECS.hpp"
// #include "../external/sfml.hpp"

namespace rtype
{
    const std::string WINDOW_NAME = "R-Type";
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    class Client {
        public:
            Client();
            ~Client();

            virtual void run(Network::Sender sender, Network::Receive& receive, int port) = 0;
            virtual void loadTextures() = 0;
            virtual void drawParallax(sf::RenderWindow &window) = 0;
            ECS initECS();

        private:
    };

    // TODO: put SFML in a separate file (external folder)
    class SFML: public Client {
        public:
            SFML(): window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME) {
                std::cout << "SFML Client" << std::endl;
                loadTextures();
            };
            ~SFML() {
                std::cout << "Goodbye" << std::endl;
            };
            void run(Network::Sender sender, Network::Receive& receive, int port) override;
            void loadTextures() override;
            void drawParallax(sf::RenderWindow &window) override;

            sf::RenderWindow& getWindow() { return window; };

        private:
            sf::RenderWindow window;

            sf::Texture playerTexture;
            sf::Texture parallaxTexture1;
            sf::Texture parallaxTexture2;
            sf::Texture parallaxTexture3;

            std::vector<sf::Sprite> playersSprites;
            sf::Sprite planeSprite;
            sf::Sprite parallaxSprite1;
            sf::Sprite parallaxSprite1b;
            sf::Sprite parallaxSprite2;
            sf::Sprite parallaxSprite2b;
            sf::Sprite parallaxSprite3;
            sf::Sprite parallaxSprite3b;
    };
}
