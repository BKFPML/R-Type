/**
 * @file client.hpp
 * @brief Client class header file
 * @date 29-11-2023
 */

# pragma once

#include <iostream>
#include <ctime>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../../engine/includes/network_library/boost_udp.hpp"
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

            virtual void run(ISender& sender, IReceiver& receive, int port) = 0;
            virtual void loadTextures() = 0;
            virtual void drawParallax(sf::RenderWindow &window) = 0;
            ECS initECS();
            

        private:
    };
}
