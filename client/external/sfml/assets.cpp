/**
 * @file assets.cpp
 * @brief Implementation of the assets loading
 * @date 09-01-2024
 */

#include "sfml.hpp"

//* Textures
#include "player_red.h"
#include "r_typesheet42.h"
#include "parallax100.h"
#include "parallax80.h"
#include "parallax60.h"
#include "sky.h"
#include "outerSpace.h"
#include "spaceGarage.h"
#include "connection.h"
#include "logo.h"
#include "input_frame.h"
#include "bar.h"
#include "button.h"
#include "letter_box.h"
#include "fps_30_60.h"
#include "fps_120.h"

//* Fonts
#include "rTypeFont.h"

//* Musics
#include "mainTheme.h"
#include "stageOne.h"

//* effects
#include "click.h"

/**
 * @brief Initialises the textures for the client's sprites
 *
 * @param name std::string name of the sprite
 * @param sheet unsigned char const * sprite sheet
 * @param size unsigned int size of the sprite sheet
 */
void rtype::SFML::initTextures(std::string name, unsigned char const *sheet, unsigned int size)
{
    textures.push_back(std::make_pair(name, new sf::Texture()));
    if (!textures.back().second->loadFromMemory(sheet, size)) {
        std::cerr << "Error loading texture" << std::endl;
        exit(84);
    }
    sprites.push_back(std::make_pair(name, new sf::Sprite(*textures.back().second)));
}

/**
 * @brief Initialises a music for the client
 *
 * @param name std::string name of the music
 * @param music unsigned char const * music
 * @param size unsigned int size of the music
 */
void rtype::SFML::initMusic(std::string name, unsigned char const *music, unsigned int size)
{
    musics.push_back(std::make_pair(name, new sf::Music()));
    if (!musics.back().second->openFromMemory(music, size)) {
        std::cerr << "Error loading music" << std::endl;
        exit(84);
    }
    musics.back().second->setVolume(10);
}

/**
 * @brief Loads the textures for the client's sprites
 */
void rtype::SFML::loadAssets()
{
    initTextures("logo", logo, logo_len);
    initTextures("outerSpace", outerSpace, outerSpace_len);
    initTextures("spaceGarage", spaceGarage, spaceGarage_len);
    initTextures("parallax100", parallax100, parallax100_len);
    initTextures("parallax80", parallax80, parallax80_len);
    initTextures("parallax60", parallax60, parallax60_len);
    initTextures("sky", sky, sky_len);
    initTextures("player_red", player_red, player_red_len);
    initTextures("connection", connection, connection_len);
    initTextures("input_frame", input_frame, input_frame_len);
    initTextures("bar", bar, bar_len);
    initTextures("button", button, button_len);
    initTextures("letter_box", letter_box, letter_box_len);
    initTextures("fps_30_60", fps_30_60, fps_30_60_len);
    initTextures("fps_120", fps_120, fps_120_len);
    initTextures("r_typesheet42", r_typesheet42, r_typesheet42_len);

    if (!font.loadFromMemory(rTypeFont, rTypeFont_len)) {
        std::cerr << "Error loading font" << std::endl;
        exit(84);
    }
    text.setFont(font);

    initMusic("mainTheme", mainTheme, mainTheme_len);
    initMusic("stageOne", stageOne, stageOne_len);
    initMusic("click", click, click_len);

}
