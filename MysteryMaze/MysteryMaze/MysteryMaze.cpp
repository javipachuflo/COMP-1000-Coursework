#include <SFML/Graphics.hpp>
#include <iostream> //for debugging
#include <random>

// declare the functions
void generateMaze();

sf::RenderWindow window(sf::VideoMode(1920, 1080), "MysteryMaze");// set the window size to my monitor size


int main()
{

	generateMaze();

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


    sf::Clock clock; 

    while (window.isOpen())
    {
        sf::Time timeSinceLastFrame = clock.restart(); // This variable will hold much time has passed between frames, making the player move at the same speed in all types of PCs when we times this value by the player input.

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sf::Vector2f vRequestedPlayerMovement(0.0f, 0.0f); // create a new vector2f (floating point vector) that will change depending on the input.

        float fSpeed = 500.0f;

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
        //std::cout << vRequestedPlayerMovement.x << "\n";
        //std::cout << vRequestedPlayerMovement.y << "\n";



        player.move(vRequestedPlayerMovement * fSpeed * timeSinceLastFrame.asSeconds()); // the input of the player times the time it took for the frame to pass

        window.clear();
        window.draw(player); // draw the player
        //window.draw(enemy); // draw the enemy
        window.display();
    }

    return 0;
}

void generateMaze()
{
	// generate a maze

    sf::Texture wallTexture;
    wallTexture.loadFromFile("Images/MysteryMaze_Wall_Bordered.png");
    sf::Sprite wall(wallTexture);
    wall.setScale(sf::Vector2f(10, 10));
    wall.setPosition(sf::Vector2f(80, 80)); // add 80 at the beginning for the first wall to appear fully
    wall.setOrigin(sf::Vector2f(8, 8));


    sf::Vector2f currentWallPosition = wall.getPosition();

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Images/MysteryMaze_Enemy.png");
    sf::Sprite enemy(enemyTexture);
    enemy.setScale(sf::Vector2f(10, 10));
    enemy.setPosition(sf::Vector2f(960, 540));
    enemy.setOrigin(sf::Vector2f(7, 7));


	window.draw(wall);

    int mazeArray[20][20];

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			mazeArray[i][j] = rand() % 2; // 0 or 1
            sf::Vector2f offset(currentWallPosition.y * i, currentWallPosition.x * j); // the offset of the walls 

			wall.setPosition(offset);
			window.draw(wall); 
		}
	}
}