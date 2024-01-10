/**
 * @file sfml.hpp
 * @brief Header file for the SFML library encapsulation
 * @date 28-12-2023
 */

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../../../engine/includes/network_library/boost_udp.hpp"
#include "../../../engine/includes/ECS.hpp"
#include "../../includes/input.hpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_NAME "R-Type"

#define HALF_WINDOW_WIDTH WINDOW_WIDTH / 2
#define HALF_WINDOW_HEIGHT WINDOW_HEIGHT / 2

namespace rtype
{
    class IGraphical {
        public:
            virtual ~IGraphical() = default;

            virtual void loadAssets() = 0;
            virtual void drawSprite(std::string sprite, int x, int y, float scale, int rotation, int size_x, int size_y) = 0;
            virtual void drawText(std::string text, int x, int y, int size) = 0;
            virtual void clear() = 0;
            virtual void display() = 0;
            virtual KeyState handleEvents() = 0;
    };

    class SFML: public IGraphical {
        public:
            SFML();
            ~SFML();

            void loadAssets() override;
            void drawSprite(std::string sprite, int x, int y, float scale, int rotation, int size_x, int size_y) override;
            void drawText(std::string text, int x, int y, int size) override;
            void clear() override;
            void display() override;
            KeyState handleEvents() override;

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
