/**
 * @file IGraphical.hpp
 * @brief Header file for the IGraphical interface
 * @date 10-01-2024
 */

#pragma once

#include <string>
#include <iostream>

#include "./input.hpp"

namespace rtype {
    class IGraphical {
        public:
            virtual ~IGraphical() = default;

            virtual void loadAssets() = 0;
            virtual void drawSprite(std::string sprite, int x, int y, float scale, int rotation, int size_x, int size_y) = 0;
            virtual void drawText(std::string text, int x, int y, int size) = 0;
            virtual void playMusic(std::string music, bool loop) = 0;
            virtual void stopMusic(std::string music) = 0;
            virtual void setVolume(int volume) = 0;
            virtual void clear() = 0;
            virtual void display() = 0;
            virtual std::pair<KeyState, KeyState> handleEvents() = 0;
            virtual void stop() = 0;
    };
}
