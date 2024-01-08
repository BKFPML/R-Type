/**
 * @file sfml.hpp
 * @brief Header file for the SFML library encapsulation
 * @date 28-12-2023
 */

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../../engine/includes/network_library/boost_udp.hpp"
#include "../../engine/includes/ECS.hpp"

namespace rtype
{
    class IGraphical {
        public:
            virtual ~IGraphical() = default;

            virtual void loadTextures() = 0;
            virtual void handleEvents(Sender& sender) = 0;
            virtual void drawWindow() = 0;
            virtual void drawParallax(sf::RenderWindow &window) = 0;
    };

    class SFML: public IGraphical {
        public:
            SFML();
            ~SFML();

            void loadTextures() override;
            void handleEvents(Sender& sender) override;
            void drawParallax(sf::RenderWindow &window) override;
            void drawWindow() override;

            sf::RenderWindow& getWindow() { return _window; };

        private:
            sf::RenderWindow _window;

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
