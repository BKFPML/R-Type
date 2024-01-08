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
#include "../includes/keystates.hpp"

namespace rtype
{
    class IGraphical {
        public:
            virtual ~IGraphical() = default;

            virtual void loadTextures() = 0;
            virtual void draw(std::string sprite, int x, int y, float scale, int rotation, int size_x, int size_y) = 0;
            virtual void clear() = 0;
            virtual void display() = 0;
            virtual void handleEvents() = 0;

    };

    class SFML: public IGraphical {
        public:
            SFML();
            ~SFML();

            void loadTextures() override;
            void handleEvents() override;
            void draw(std::string sprite, int x, int y, float scale, int rotation, int size_x, int size_y) override;
            void clear() override;
            void display() override;
            void initTextures(std::string name, unsigned char const *sheet, unsigned int size);

            sf::RenderWindow& getWindow() { return _window; };

        private:
            sf::RenderWindow _window;

            std::vector<std::pair<std::string, sf::Texture*>> textures;
            std::vector<std::pair<std::string, sf::Sprite*>> sprites;

            int fps;
            sf::Clock DrawClock;
    };
}
