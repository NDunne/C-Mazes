#pragma once
#include "PrimMaze.h"

enum MazeType { PRIM };
enum MazeDifficulty {EASY, MEDIUM, HARD };

class MazeGenerator
{
public:
	MazeGenerator(SDL_Window* sdlWin);
	~MazeGenerator();

	Maze* newMaze(MazeType t, MazeDifficulty d);

	Maze* getMaze();

private:
	SDL_Window* window;
	SDL_Surface* surface;
	Maze* currentMaze;
};

