#pragma once

#include "PrimMazes\PrimMaze.h"

#include "KruskalMazes\KruskalMaze.h"


enum MazeType { PRIM, KRUSKAL };

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

