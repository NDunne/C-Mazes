#pragma once
#include "PrimMaze.h"

enum MazeType { PRIM, EASYPRIM };

class MazeGenerator
{
public:
	MazeGenerator(SDL_Window* sdlWin);
	~MazeGenerator();

	Maze* newMaze(MazeType t);

	Maze* getMaze();

private:
	SDL_Window* window;
	SDL_Surface* surface;
	Maze* currentMaze;
};

