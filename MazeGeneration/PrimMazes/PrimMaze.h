#pragma once

#include "..\Maze.h"

class PrimMaze : public Maze
{
public:
	PrimMaze(SDL_Window* w);

private:
	void generate();

	void drawEdge(NodeCoord A, NodeCoord B, edgeType e);
};

