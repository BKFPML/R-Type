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

    //! TEMP
    _graphical->drawSprite("player_red", _ecs.getComponent<Position>(_players[0])->x, _ecs.getComponent<Position>(_players[0])->y, 3, 180, 34, 34);

    _graphical->display();
}

/**
 * @brief Draws the background Parallax (three layers)
 *
 */
void rtype::Client::drawParallax()
{
    _parallaxPos[0].first -= 1;
    _parallaxPos[1].first -= 1;
    _parallaxPos[2].first -= 2;
    _parallaxPos[3].first -= 2;
    _parallaxPos[4].first -= 3;
    _parallaxPos[5].first -= 3;

    if (_parallaxPos[0].first <= -WINDOW_WIDTH)
        _parallaxPos[0].first = WINDOW_WIDTH;
    if (_parallaxPos[1].first <= -WINDOW_WIDTH)
        _parallaxPos[1].first = WINDOW_WIDTH;
    if (_parallaxPos[2].first <= -WINDOW_WIDTH)
        _parallaxPos[2].first = WINDOW_WIDTH;
    if (_parallaxPos[3].first <= -WINDOW_WIDTH)
        _parallaxPos[3].first = WINDOW_WIDTH;
    if (_parallaxPos[4].first <= -WINDOW_WIDTH)
        _parallaxPos[4].first = WINDOW_WIDTH;
    if (_parallaxPos[5].first <= -WINDOW_WIDTH)
        _parallaxPos[5].first = WINDOW_WIDTH;
        

    _graphical->drawSprite("parallax100", _parallaxPos[0].first, _parallaxPos[0].second, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax100", _parallaxPos[1].first, _parallaxPos[1].second, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax80", _parallaxPos[2].first, _parallaxPos[2].second, 1, 1, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax80", _parallaxPos[3].first, _parallaxPos[3].second, 1, 1, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax60", _parallaxPos[4].first, _parallaxPos[4].second, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
    _graphical->drawSprite("parallax60", _parallaxPos[5].first, _parallaxPos[5].second, 1, 180, WINDOW_WIDTH, WINDOW_HEIGHT);
}
