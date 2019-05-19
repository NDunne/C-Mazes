#pragma once

#include "..\Maze.h"

class MedPrimMaze : public Maze
{
public:
	MedPrimMaze(SDL_Window* w);

private:
	void generate();

	void drawEdge(NodeCoord A, NodeCoord B, edgeType e);
};

