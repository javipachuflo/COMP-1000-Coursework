#include "Game.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <utility>
#include <cstdlib>
#include <ctime>

Game::Game()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for random number generation
}

Game::~Game()
{
}

bool Game::Update()
{
    sf::RenderWindow window(sf::VideoMode(1080, 1080), "MysteryMaze");// set the window size to my monitor size
    window.setFramerateLimit(60); // set the framerate to 60 frames per second

    sf::Texture wallTexture;
    wallTexture.loadFromFile("Images/MysteryMaze_Wall_2.png");
    sf::Sprite wall(wallTexture);
    float cellSize = 54.0f; // Adjusted cell size to fit the window
    wall.setScale(cellSize / wallTexture.getSize().x, cellSize / wallTexture.getSize().y);
    wall.setOrigin(sf::Vector2f(wallTexture.getSize().x / 2.0f, wallTexture.getSize().y / 2.0f));

	sf::Texture floorTexture;
	floorTexture.loadFromFile("Images/MysteryMaze_Floor_Tile_2.png");
	sf::Sprite floor(floorTexture);
	floor.setScale(cellSize / floorTexture.getSize().x, cellSize / floorTexture.getSize().y);
	floor.setOrigin(sf::Vector2f(floorTexture.getSize().x / 2.0f, floorTexture.getSize().y / 2.0f));

    // get player texture as a Sprite and set the sprite's scale to 10x bigger and its origin to the center of the sprite 
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Images/MysteryMaze_Player.png");
    sf::Sprite player(playerTexture);
    player.setScale(sf::Vector2f(3, 3));
    player.setOrigin(sf::Vector2f(6, 5.5f));

    // get enemy texture as a Sprite and set the sprite's scale to 10x bigger and its origin to the center of the sprite as well as the position to the center (half and half of my monitor resolution)
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Images/MysteryMaze_Enemy.png");
    sf::Sprite enemy(enemyTexture);
    enemy.setScale(sf::Vector2f(3, 3));
    enemy.setPosition(sf::Vector2f(960, 540));
    enemy.setOrigin(sf::Vector2f(6, 5.5f));

    sf::Clock clock;

    // Generate the maze
    const int mazeWidth = 20;
    const int mazeHeight = 20;
    std::vector<std::vector<int>> maze = generateMaze(mazeWidth, mazeHeight);

    while (window.isOpen())
    {
        sf::Time timeSinceLastFrame = clock.restart(); // This variable will hold much time has passed between frames, making the player move at the same speed in all types of PCs when we times this value by the player input.

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }
        }

        sf::Vector2f vRequestedPlayerMovement(0.0f, 0.0f); // create a new vector2f (floating point vector) that will change depending on the input.

        float fSpeed = 250.0f;

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

        sf::Vector2f newPosition = player.getPosition();
        sf::Vector2f movement = vRequestedPlayerMovement * fSpeed * timeSinceLastFrame.asSeconds();

        // Check for collisions with the walls for each direction separately
        if (movement.x != 0.0f) {
            sf::Vector2f newXPosition = newPosition + sf::Vector2f(movement.x, 0.0f);
            sf::FloatRect playerBounds(newXPosition.x - player.getOrigin().x * player.getScale().x, newXPosition.y - player.getOrigin().y * player.getScale().y, player.getGlobalBounds().width, player.getGlobalBounds().height);
            bool collision = false;
            for (int i = 0; i < mazeWidth; ++i)
            {
                for (int j = 0; j < mazeHeight; ++j)
                {
                    if (maze[i][j] == 1)
                    {
                        sf::FloatRect wallBounds(i * cellSize, j * cellSize, cellSize, cellSize);
                        if (playerBounds.intersects(wallBounds))
                        {
                            collision = true;
                            break;
                        }
                    }
                }
                if (collision) break;
            }
            if (!collision)
            {
                newPosition.x = newXPosition.x;
            }
        }

        if (movement.y != 0.0f) {
            sf::Vector2f newYPosition = newPosition + sf::Vector2f(0.0f, movement.y);
            sf::FloatRect playerBounds(newYPosition.x - player.getOrigin().x * player.getScale().x, newYPosition.y - player.getOrigin().y * player.getScale().y, player.getGlobalBounds().width, player.getGlobalBounds().height);
            bool collision = false;
            for (int i = 0; i < mazeWidth; ++i)
            {
                for (int j = 0; j < mazeHeight; ++j)
                {
                    if (maze[i][j] == 1)
                    {
                        sf::FloatRect wallBounds(i * cellSize, j * cellSize, cellSize, cellSize);
                        if (playerBounds.intersects(wallBounds))
                        {
                            collision = true;
                            break;
                        }
                    }
                }
                if (collision) break;
            }
            if (!collision)
            {
                newPosition.y = newYPosition.y;
            }
        }

        // Check for collisions with the window boundaries
        if (newPosition.x - player.getOrigin().x * player.getScale().x < 0)
            newPosition.x = player.getOrigin().x * player.getScale().x;
        if (newPosition.y - player.getOrigin().y * player.getScale().y < 0)
            newPosition.y = player.getOrigin().y * player.getScale().y;
        if (newPosition.x + player.getOrigin().x * player.getScale().x > window.getSize().x)
            newPosition.x = window.getSize().x - player.getOrigin().x * player.getScale().x;
        if (newPosition.y + player.getOrigin().y * player.getScale().y > window.getSize().y)
            newPosition.y = window.getSize().y - player.getOrigin().y * player.getScale().y;

        player.setPosition(newPosition);

        window.clear(sf::Color::White); // Change the background color to white

		//Draw the floor
		for (int i = 0; i < mazeWidth; ++i)
		{
			for (int j = 0; j < mazeHeight; ++j)
			{
				floor.setPosition(sf::Vector2f(i* cellSize + cellSize / 2, j* cellSize + cellSize / 2));
				window.draw(floor);
			}
		}


        // Draw the maze
        for (int i = 0; i < mazeWidth; ++i)
        {
            for (int j = 0; j < mazeHeight; ++j)
            {
                if (maze[i][j] == 1)
                {
                    wall.setPosition(sf::Vector2f(i * cellSize + cellSize / 2, j * cellSize + cellSize / 2));
                    window.draw(wall);
                }
            }
        }

        window.draw(player); // draw the player
        //window.draw(enemy); // draw the enemy
        window.display();
    }

    return true;
}

std::vector<std::vector<int>> Game::generateMaze(int width, int height)
{
    // Initialize the maze with all walls (1s)
    std::vector<std::vector<int>> maze(width, std::vector<int>(height, 1));

    // Stack to hold the cells to be visited
    std::stack<sf::Vector2i> stack;
    // Start from the top-left corner of the maze
    stack.push(sf::Vector2i(0, 0));
    // Mark the starting cell as a path (0)
    maze[0][0] = 0;

    // Possible directions to move in the maze (right, down, left, up)
    std::vector<sf::Vector2i> directions = { sf::Vector2i(0, 2), sf::Vector2i(2, 0), sf::Vector2i(0, -2), sf::Vector2i(-2, 0) };

    // Continue until there are no more cells to visit
    while (!stack.empty())
    {
        // Get the current cell from the top of the stack
        sf::Vector2i current = stack.top();
        stack.pop();

        int x = current.x;
        int y = current.y;

        // List to hold the valid neighbors of the current cell
        std::vector<sf::Vector2i> neighbors;

        // Check all possible directions
        for (std::vector<sf::Vector2i>::iterator it = directions.begin(); it != directions.end(); ++it)
        {
            int dx = it->x;
            int dy = it->y;

            int nx = x + dx;
            int ny = y + dy;

            // Check if the neighbor is within the maze bounds and is still a wall
            if (nx >= 0 && ny >= 0 && nx < width && ny < height && maze[nx][ny] == 1)
            {
                // Add the neighbor to the list of valid neighbors
                neighbors.push_back(sf::Vector2i(nx, ny));
            }
        }

        // If there are valid neighbors
        if (!neighbors.empty())
        {
            // Push the current cell back onto the stack
            stack.push(current);

            // Choose a random neighbor to visit next
            sf::Vector2i next = neighbors[std::rand() % neighbors.size()];

            int nx = next.x;
            int ny = next.y;

            // Mark the chosen neighbor as a path (0)
            maze[nx][ny] = 0;
            // Also mark the cell between the current cell and the chosen neighbor as a path
            maze[x + (nx - x) / 2][y + (ny - y) / 2] = 0;

            // Push the chosen neighbor onto the stack to visit it next
            stack.push(next);
        }
    }

    return maze;
}