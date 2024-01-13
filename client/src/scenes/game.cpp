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
    // _graphical->drawSprite(_ecs.getComponent<Sprite>(player)->texture, _ecs.getComponent<Position>(_players[0])->x, _ecs.getComponent<Position>(_players[0])->y, 3, 180, 34, 34);
    _graphical->display();
}

/**
 * @brief Draws the background Parallax (three layers)
 *
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
        

    _graphical->drawSprite("parallax100", _parallaxPos.at(0).first, _parallaxPos.at(0).second, 0, 0, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax100", _parallaxPos.at(1).first, _parallaxPos.at(1).second, 0, 0, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax80", _parallaxPos.at(2).first, _parallaxPos.at(2).second, 0, 0, 1, 1, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax80", _parallaxPos.at(3).first, _parallaxPos.at(3).second, 0, 0, 1, 1, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax60", _parallaxPos.at(4).first, _parallaxPos.at(4).second, 0, 0, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax60", _parallaxPos.at(5).first, _parallaxPos.at(5).second, 0, 0, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
}
