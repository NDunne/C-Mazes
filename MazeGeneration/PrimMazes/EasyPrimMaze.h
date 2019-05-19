#pragma once

#include "..\Maze.h"

class EasyPrimMaze : public Maze
{
public:
	EasyPrimMaze(SDL_Window* w);

private:
	void generate();

	bool compare(NodeCoord currentNode, NodeCoord search);

	void drawEdge(NodeCoord A, NodeCoord B, edgeType e);
};

