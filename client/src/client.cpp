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
    if (!playerTexture.loadFromFile("assets/sprites/r-typesheet5.gif"))
        std::cerr << "Error loading r-typesheet5.gif" << std::endl;
    planeSprite.setTexture(playerTexture);
    playersSprites.push_back(planeSprite);
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
 * @brief Initialize the ECS
 * 
 * @return ECS
 */
ECS rtype::Client::initECS()
{
    ECS ecs;
    ecs.registerComponent<Position>();
    ecs.registerComponent<Health>();
    ecs.registerComponent<Velocity>();
    return ecs;
}

/**
 * @brief Run the client
 * 
 * @param sender Network::Sender to send data to the server
 * @param receive Network::Receive to receive data from the server
 * @param port int port to use for the client
 */
void rtype::Client::run(Network::Sender sender, Network::Receive& receive, int port)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);

    ECS ecs = initECS();
    std::vector<ECS::Entity> players;
    players.push_back(ecs.createEntity());
    ecs.addComponent<Position>(players[0], {100, 100});
    ecs.addComponent<Health>(players[0], 100);
    ecs.addComponent<Velocity>(players[0], {1, 1, 2});
    srand(time(0));

    playersSprites[0].setPosition(rand() % 300 + 200, rand() % 500 + 200);
    playersSprites[0].setScale(5, 5);
    playersSprites[0].setTextureRect(sf::IntRect(0, 0, 34, 34));
    playersSprites[0].setRotation(180);

    while (window.isOpen())
    {
        if (receive.getReceivedIPs().size() > 0) {
            std::cout << "Received IPs: " << std::endl;
            for (const auto& ip : receive.getReceivedIPs()) {
                std::cout << ip << std::endl;
                players.push_back(ecs.createEntity());
                ecs.addComponent<Position>(players[-1], {100, 100});
                ecs.addComponent<Health>(players[-1], 100);
                ecs.addComponent<Velocity>(players[-1], {1, 1, 2});
                playersSprites.push_back(planeSprite);
                playersSprites.back().setPosition(500 + rand()%200, 800 - rand()%300);
                playersSprites.back().setScale(5, 5);
                playersSprites.back().setTextureRect(sf::IntRect(0, 0, 34, 34));
                playersSprites.back().setRotation(180);
            }
            receive.clearReceivedIPs();
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                sender.send("bullet-x:100-y:100-vx:1-vy:1");
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                playersSprites[0].move(0, -10);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                playersSprites[0].move(-10, 0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                playersSprites[0].move(0, 10);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                playersSprites[0].move(10, 0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            }
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        for (auto& player: playersSprites) {
            player.move(0.1, 0);
        }
        sender.send(std::to_string(playersSprites[0].getPosition().x) + " " + std::to_string(playersSprites[0].getPosition().y) + " " + std::to_string(port));
        window.clear(sf::Color::Black);
        drawParallax(window);
        std::cout << "Players: " << playersSprites.size() << std::endl;
        for (auto& player: playersSprites) {
            std::cout << "Player: " << player.getPosition().x << " " << player.getPosition().y << std::endl;
            window.draw(player);
        }
        window.display();
    }
}
