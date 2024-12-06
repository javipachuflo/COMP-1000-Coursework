#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "MysteryMaze");// set the window size to my monitor size

    // get player texture as a Sprite and set the sprite's scale to 10x bigger and its origin to the center of the sprite 
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Images/MysteryMaze_Player.png");
    sf::Sprite player(playerTexture);
    player.setScale(sf::Vector2f(10, 10));
    //player.setPosition(sf::Vector2f(960, 540));
    player.setOrigin(sf::Vector2f(7, 7));

    // get enemy texture as a Sprite and set the sprite's scale to 10x bigger and its origin to the center of the sprite as well as the position to the center (half and half of my monitor resolution)
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Images/MysteryMaze_Enemy.png");
    sf::Sprite enemy(enemyTexture);
    enemy.setScale(sf::Vector2f(10, 10));
    enemy.setPosition(sf::Vector2f(960, 540));
    enemy.setOrigin(sf::Vector2f(7, 7));

    sf::Clock clock; // This will allow us to check how much time has passed between frames, making the player move at the same speed in all types of PCs

    while (window.isOpen())
    {
        sf::Time timeSinceLastFrame = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sf::Vector2f vRequestedPlayerMovement(0.0f, 0.0f); // create a new vector2f (floating point vector) that will change depending on the input.

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            vRequestedPlayerMovement += sf::Vector2f(0.0f, -1.0f); // increse by a negative y value
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            vRequestedPlayerMovement += sf::Vector2f(-1.0f, 0.0f);// increse by a negative x value

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            vRequestedPlayerMovement += sf::Vector2f(0.0f, 1.0f);// increse by a positive y value

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            vRequestedPlayerMovement += sf::Vector2f(1.0f, 0.0f);// increse by a positive x value

        }

        player.move(vRequestedPlayerMovement);

        window.clear();
        window.draw(player); // draw the player
        window.draw(enemy); // draw the enemy
        window.display();
    }

    return 0;
}