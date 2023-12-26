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
    loadTextures();
}

/**
 * @brief Destroy the rtype::Client::Client object
 */
rtype::Client::~Client()
{
    std::cout << "Goodbye" << std::endl;
}

/**
 * @brief Load the textures for the client's sprites
 */
void rtype::Client::loadTextures()
{
    if (!parallaxTexture1.loadFromFile("assets/background/Parallax100.png"))
        std::cerr << "Error loading parallax1.png" << std::endl;
    if (!parallaxTexture2.loadFromFile("assets/background/Parallax80.png"))
        std::cerr << "Error loading parallax2.png" << std::endl;
    if (!parallaxTexture3.loadFromFile("assets/background/Parallax60.png"))
        std::cerr << "Error loading parallax3.png" << std::endl;
    parallaxSprite1.setTexture(parallaxTexture1);
    parallaxSprite1b.setTexture(parallaxTexture1);
    parallaxSprite2.setTexture(parallaxTexture2);
    parallaxSprite2b.setTexture(parallaxTexture2);
    parallaxSprite3.setTexture(parallaxTexture3);
    parallaxSprite3b.setTexture(parallaxTexture3);

    parallaxSprite1.setPosition(0, 0);
    parallaxSprite1b.setPosition(WINDOW_WIDTH, 0);
    parallaxSprite2.setPosition(0, 0);
    parallaxSprite2b.setPosition(WINDOW_WIDTH, 0);
    parallaxSprite3.setPosition(0, 0);
    parallaxSprite3b.setPosition(WINDOW_WIDTH, 0);
}

/**
 * @brief Draw the background parallax effect
 *
 * @param window sf::RenderWindow to draw the parallax effect on
 */
void rtype::Client::drawParallax(sf::RenderWindow &window)
{
    float parallaxSpeed1 = 0.5f;
    float parallaxSpeed2 = 0.6f;
    float parallaxSpeed3 = 0.7f;

    parallaxSprite1.move(-parallaxSpeed1, 0);
    parallaxSprite1b.move(-parallaxSpeed1, 0);
    parallaxSprite2.move(-parallaxSpeed2, 0);
    parallaxSprite2b.move(-parallaxSpeed2, 0);
    parallaxSprite3.move(-parallaxSpeed3, 0);
    parallaxSprite3b.move(-parallaxSpeed3, 0);

    if (parallaxSprite1.getPosition().x < -parallaxSprite1.getLocalBounds().width)
        parallaxSprite1.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite1b.getPosition().x < -parallaxSprite1b.getLocalBounds().width)
        parallaxSprite1b.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite2.getPosition().x < -parallaxSprite2.getLocalBounds().width)
        parallaxSprite2.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite2b.getPosition().x < -parallaxSprite2b.getLocalBounds().width)
        parallaxSprite2b.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite3.getPosition().x < -parallaxSprite3.getLocalBounds().width)
        parallaxSprite3.setPosition(WINDOW_WIDTH, 0);
    if (parallaxSprite3b.getPosition().x < -parallaxSprite3b.getLocalBounds().width)
        parallaxSprite3b.setPosition(WINDOW_WIDTH, 0);

    window.draw(parallaxSprite1);
    window.draw(parallaxSprite1b);
    window.draw(parallaxSprite2);
    window.draw(parallaxSprite2b);
    window.draw(parallaxSprite3);
    window.draw(parallaxSprite3b);
}

/**
 * @brief Run the client
 */
void rtype::Client::run()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    Network::Sender sender;

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
        drawParallax(window);
        window.display();
    }
}
