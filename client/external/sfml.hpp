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

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_NAME "R-Type"

namespace rtype
{
    class IGraphical {
        public:
            virtual ~IGraphical() = default;

            virtual void loadTextures() = 0;
            virtual void draw(std::string sprite, int x, int y, float scale, int rotation, int size_x, int size_y) = 0;
            virtual void drawText(std::string text, int x, int y, int size) = 0;
            virtual void clear() = 0;
            virtual void display() = 0;
            virtual KeyState handleEvents() = 0;
    };

    class SFML: public IGraphical {
        public:
            SFML();
            ~SFML();

            KeyState handleEvents() override;
            void loadTextures() override;
            void draw(std::string sprite, int x, int y, float scale, int rotation, int size_x, int size_y) override;
            void drawText(std::string text, int x, int y, int size) override;
            void clear() override;
            void display() override;
            void initTextures(std::string name, unsigned char const *sheet, unsigned int size);

            sf::RenderWindow& getWindow() { return _window; };

        private:
            sf::RenderWindow _window;

            std::vector<std::pair<std::string, sf::Texture*>> textures;
            std::vector<std::pair<std::string, sf::Sprite*>> sprites;
            sf::Font font;
            sf::Text text;
    };
}
