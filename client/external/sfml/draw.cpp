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
void rtype::SFML::drawSprite(std::string sprite, int x, int y, int startX, int startY, float scale = 1.0, int rotation = 0, int sizeX = 0, int sizeY = 0)
{
    for (auto& s : sprites) {
        if (s.first == sprite) {
            s.second->setPosition(x, y);
            s.second->setScale(scale, scale);
            s.second->setRotation(rotation);
            if (sizeX != 0 && sizeY != 0)
                s.second->setTextureRect(sf::IntRect(startX, startY, startX + sizeX, startY + sizeY));
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

/**
 * @brief Sets the volume of the music
 * 
 * @param volume int volume of the music
 */
void rtype::SFML::setVolume(int volume)
{
    for (auto& m : musics) {
        m.second->setVolume(volume);
    }
}