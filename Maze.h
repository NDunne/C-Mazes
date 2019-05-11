#pragma once

#include <string>

#include "SDL.h"
#include "MazeNode.h"

class Maze
{
public:
	const static int X_CELLS = 45;
	const static int Y_CELLS = 45;

	const static int boxLen = 10;
	const static int boxPad = 2;

	enum cellType { WALL, UNVISITED, VISITED };

	Maze(SDL_Window* w, SDL_Surface* s);
	~Maze();

	void draw();

private:
	SDL_Window* window;
	SDL_Surface* surface;

	Uint32 black;
	Uint32 grey;
	Uint32 white;

	//x:[y:[]]
	cellType cells[X_CELLS][Y_CELLS];
};

