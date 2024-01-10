/**
 * @file draw.cpp
 * @brief Implementation of the draw functions in SFML
 * @date 09-01-2024
 */

#include "sfml.hpp"

/**
 * @brief Draws a sprite on the SFML window
 *
 * @param sprite std::string path to the sprite
 * @param x int x position of the sprite
 * @param y int y position of the sprite
 */
void rtype::SFML::drawSprite(std::string sprite, int x, int y, float scale = 1.0, int rotation = 0, int size_x = 0, int size_y = 0)
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
 * @brief Draws text on the SFML window
 *
 * @param text std::string text to write
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
 * @brief Plays a music
 *
 * @param music std::string name of the music to play
 */
void rtype::SFML::playMusic(std::string music, bool loop = true)
{
    for (auto& m : musics) {
        if (m.first == music) {
            m.second->setLoop(loop);
            m.second->play();
        }
    }
}


/**
 * @brief Stops a music
 * 
 * @param music std::string name of the music to stop
 */

void rtype::SFML::stopMusic(std::string music)
{
    for (auto& m : musics) {
        if (m.first == music) {
            m.second->stop();
        }
    }
}