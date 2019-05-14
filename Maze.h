#pragma once

#include "SDL.h"
#include "MazeAdj.h"

#include <vector>
#include <random>
#include <ctime>

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

	const static int X_NODES = X_CELLS - 2;
	const static int Y_NODES = Y_CELLS - 2;
	
	bool isValid(NodeCoord n);

	void Prims();
	void drawCell(int x, int y, Maze::cellType type);

	//x:[y:[]]
	cellType cells[X_CELLS][Y_CELLS];

	MazeAdj allEdges;
	MazeAdj mazeEdges;
};

