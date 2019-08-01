#pragma once

#include "PrimMaze.h"

#include "KruskalMaze.h"

#include "RecDivMaze.h"

#include "AldousBroderMaze.h"

enum MazeType { PRIM, KRUSKAL, RECDIV, ALDBRO };



class MazeGenerator
{
public:
	MazeGenerator(SDL_Window* sdlWin);

	Maze* newMaze(MazeType t, DrawPosition dp);

private:
	SDL_Window* window;
	SDL_Surface* surface;
};

