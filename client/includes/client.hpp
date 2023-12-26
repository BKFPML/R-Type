/**
 * @file client.hpp
 * @brief Client class header file
 * @date 29-11-2023
 */

# pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../../engine/includes/network.hpp"
#include "../../engine/includes/ECS.hpp"


namespace rtype
{
    const std::string WINDOW_NAME = "R-Type";
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    class Client {
        public:
            Client();
            ~Client();

            void run();

        private:

    };
}