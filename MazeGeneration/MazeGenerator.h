#pragma once

#include "PrimMaze\PrimMaze.h"

#include "KruskalMaze\KruskalMaze.h"

#include "RecDivMaze\RecDivMaze.h"


enum MazeType { PRIM, KRUSKAL, RECDIV };

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

