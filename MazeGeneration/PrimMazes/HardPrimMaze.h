#pragma once

#include "..\Maze.h"

class HardPrimMaze : public Maze
{
public:
	HardPrimMaze(SDL_Window* w);

private:
	bool compare(NodeCoord currentNode, NodeCoord search);

	void drawEdge(NodeCoord A, NodeCoord B, edgeType e);

	void generate();
};

