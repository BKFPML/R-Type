/**
 * @file inputs.cpp
 * @brief Implementation of the inputs handling
 * @date 09-01-2024
 */

#include "client.hpp"

/**
 * @brief Maps the keys returned by the graphical lib to the game keys
 *
 * @param keys KeyState returned by the graphical lib
 */
void rtype::Client::handleKeys(KeyState keys)
{
    if(keys.up)
        std::cout << "UP" << std::endl;
    if(keys.down)
        std::cout << "DOWN" << std::endl;
    if(keys.left)
        std::cout << "LEFT" << std::endl;
    if(keys.right)
        std::cout << "RIGHT" << std::endl;
    if(keys.space)
        std::cout << "SPACE" << std::endl;
    if(keys.shift)
        std::cout << "SHIFT" << std::endl;
    if(keys.a)
        std::cout << "A" << std::endl;
    if(keys.eight)
        std::cout << "8" << std::endl;
}
