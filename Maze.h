#pragma once

#include "SDL.h"
#include "MazeAdj.h"

#include <vector>
#include <random>
#include <ctime>

class Maze
{
public:
	enum cellType { WALL, UNVISITED, VISITED, SPECIAL };

	Maze(SDL_Window* w);

	void drawBase();

protected:
	SDL_Window* window;
	SDL_Surface* surface;

	Uint32 black;
	Uint32 grey;
	Uint32 white;
	Uint32 green;
	
	bool DFS(MazeNode* start, MazeNode* search);

	void drawCell(MazeNode* n, Maze::cellType type);
	void drawCell(int x, int y, Maze::cellType type);

	MazeAdj mazeEdges;

	//Used in DFS - to say if a node is a match or not, needs to be different
	virtual bool compare(MazeNode* currentNode, MazeNode* search);

	virtual void generate() = 0;
};

