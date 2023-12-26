/**
 * @file client.cpp
 * @brief
 * @date 04-12-2023
 */

#include "client.hpp"

/**
 * @brief Construct a new rtype::Client::Client object
 */
rtype::Client::Client()
{
    std::cout << "This is the R-Type Client" << std::endl;
}

/**
 * @brief Destroy the rtype::Client::Client object
 */
rtype::Client::~Client()
{
    std::cout << "Goodbye" << std::endl;
}

/**
 * @brief Run the client
 */
void rtype::Client::run()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    Network::Sender sender;
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                sender.send(std::string("Key Enter Pressed by client 13151"), 13152);
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(shape);
        window.display();
    }
}
