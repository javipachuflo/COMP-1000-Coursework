---------CONTROLS---------
W - up
A - left
S - down
D - right

--------GOAL--------
Your goal is to reach the green flag at the bottom-right of the screen without letting the monsters touch you.
Beware! This version of the game has very quick monsters. If you die, the level resets and a new maze will be generated.
Expect to die, especially if you're unlucky and the monster spawns in the middle of your path! (This is more common in the lower levels)

Once you reach the goal, you can consider yourself the winner!

However, you may continue if you are looking for a challenge, for every time you reach the goal, a new level will be generated, but bigger and with more monsters!
You can then set your own goals (e.g. "I want to reach level 10"), or continue playing until you give up. Up to you!



++++++HOW THE MAZE IS GENERATED++++++
Every time the game is run, a new, randomly generated maze that uses a Depth-Search-First algorithm is generated that is as big as 10 * level. That means that in level 1, you will have a small 10*10 maze, in level 2, you will have a 20*20 maze, in level 3, a 30*30 maze, and so on. The value of level is increased by 1 every time the player reaches the goal!

+++++ADDITIONAL FEATURES++++++A level system: "level" has an initial value of 1. The maze dimensions are 10 * level. Every time the player reaches the goal, level is incremented by 1 and a new maze, with the new values is generated (e.g. level 2 = 10 * 2 = 20 (maze dimensions = 20 * 20).





For more information, read MysteryMaze_Documentation.pdf