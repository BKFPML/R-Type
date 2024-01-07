/**
 * @file sfml.hpp
 * @brief Header file for the SFML library encapsulation
 * @date 28-12-2023
 */

#pragma once

#include "../includes/client.hpp"

namespace rtype
{
    class SFML: public Client {
        public:
            SFML();
            ~SFML();

            void run(Sender& sender, Receiver& receive, int port) override;
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
