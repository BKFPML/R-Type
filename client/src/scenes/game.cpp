/**
 * @file game.cpp
 * @brief Handles the rendering of the game scene
 * @date 09-01-2024
 */

#include "client.hpp"

/**
 * @brief Draws the game
 *
 */
void rtype::Client::drawGame()
{
    _graphical->clear();
    drawParallax();
    drawEntities();
    drawSky();
    _graphical->display();
}

/**
 * @brief Draws the background Parallax (three layers)
 */
void rtype::Client::drawParallax()
{
    _parallaxPos.at(0).first -= 1;
    _parallaxPos.at(1).first -= 1;
    _parallaxPos.at(2).first -= 2;
    _parallaxPos.at(3).first -= 2;
    _parallaxPos.at(4).first -= 3;
    _parallaxPos.at(5).first -= 3;

    if (_parallaxPos.at(0).first <= -WINDOW_WIDTH)
        _parallaxPos.at(0).first = WINDOW_WIDTH;
    if (_parallaxPos.at(1).first <= -WINDOW_WIDTH)
        _parallaxPos.at(1).first = WINDOW_WIDTH;
    if (_parallaxPos.at(2).first <= -WINDOW_WIDTH)
        _parallaxPos.at(2).first = WINDOW_WIDTH;
    if (_parallaxPos.at(3).first <= -WINDOW_WIDTH)
        _parallaxPos.at(3).first = WINDOW_WIDTH;
    if (_parallaxPos.at(4).first <= -WINDOW_WIDTH)
        _parallaxPos.at(4).first = WINDOW_WIDTH;
    if (_parallaxPos.at(5).first <= -WINDOW_WIDTH)
        _parallaxPos.at(5).first = WINDOW_WIDTH;

    _graphical->drawSprite("parallax100", _parallaxPos.at(0).first, _parallaxPos.at(0).second, 0, 0, 1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax100", _parallaxPos.at(1).first, _parallaxPos.at(1).second, 0, 0, 1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax80", _parallaxPos.at(2).first, _parallaxPos.at(2).second, 0, 0, 1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax80", _parallaxPos.at(3).first, _parallaxPos.at(3).second, 0, 0, 1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax60", _parallaxPos.at(4).first, _parallaxPos.at(4).second, 0, 0, 1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax60", _parallaxPos.at(5).first, _parallaxPos.at(5).second, 0, 0, 1, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

/**
 * @brief Draw the Sky Parallax with a sinusoidal movement
 */
void rtype::Client::drawSky()
{
    static float movement = 0.0f;
    movement += 0.02f;

    _skyPos.at(0).first -= 5;
    _skyPos.at(1).first -= 5;

    if (_skyPos.at(0).first <= -WINDOW_WIDTH)
        _skyPos.at(0).first = WINDOW_WIDTH;
    if (_skyPos.at(1).first <= -WINDOW_WIDTH)
        _skyPos.at(1).first = WINDOW_WIDTH;

    float yOffset = 15.0f * std::sin(movement);

    _graphical->drawSprite("sky", _skyPos.at(0).first, _skyPos.at(0).second + yOffset, 0, 0, 0.5, 0, WINDOW_WIDTH * 2, 245);
    _graphical->drawSprite("sky", _skyPos.at(1).first, _skyPos.at(1).second + yOffset, 0, 0, 0.5, 0, WINDOW_WIDTH * 2, 245);
}
