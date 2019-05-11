#pragma once
#include "Maze.h"

class MazeGenerator
{
public:
	MazeGenerator(SDL_Window* sdlWin);
	~MazeGenerator();

	Maze* newMaze();

	Maze* getMaze();

private:
	SDL_Window* window;
	SDL_Surface* surface;
	Maze* currentMaze;
};

