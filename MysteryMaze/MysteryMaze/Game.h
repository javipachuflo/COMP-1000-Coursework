#pragma once
#include <vector>

class Game
{
public:
    Game();
    ~Game();
    int Update();

private:
    std::vector<std::vector<int>> generateMaze(int width, int height);
};