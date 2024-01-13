/**
 * @file sfml.hpp
 * @brief Header file for the SFML library encapsulation
 * @date 28-12-2023
 */

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../../includes/input.hpp"
#include "../../includes/IGraphical.hpp"

/**
 * @brief Window width
 */
#define WINDOW_WIDTH 1920
/**
 * @brief Window height
 */
#define WINDOW_HEIGHT 1080
/**
 * @brief Window name
 */
#define WINDOW_NAME "R-Type"

/**
 * @brief Half of the window width
 */
#define HALF_WINDOW_WIDTH WINDOW_WIDTH / 2
/**
 * @brief Half of the window height
 */
#define HALF_WINDOW_HEIGHT WINDOW_HEIGHT / 2

namespace rtype
{
    /**
     * @brief Instance of the IGraphical interface for the SFML library
     */
    class SFML: public IGraphical {
        public:
            SFML();
            ~SFML();

            void loadAssets() override;
            void drawSprite(std::string sprite, int x, int y, float scale, int rotation, int size_x, int size_y) override;
            void drawText(std::string text, int x, int y, int size) override;
            void playMusic(std::string music, bool loop) override;
            void stopMusic(std::string music) override;
            void setVolume(int volume) override;
            void clear() override;
            void display() override;
            std::pair<KeyState, KeyState> handleEvents() override;
            void stop() override;
            void init_key_bindings();


            void initTextures(std::string name, unsigned char const *sheet, unsigned int size);
            void initMusic(std::string name, unsigned char const *music, unsigned int size);
            sf::RenderWindow& getWindow() { return _window; };

        private:
            sf::RenderWindow _window;

            std::vector<std::pair<std::string, sf::Texture*>> textures;
            std::vector<std::pair<std::string, sf::Sprite*>> sprites;
            std::vector<std::pair<std::string, sf::Music*>> musics;
            sf::Font font;
            sf::Text text;
            KeyState keyState;
    };
}
