#pragma once

#include "Maze.h"

class PrimMaze : public Maze
{
public:
	PrimMaze(SDL_Window* w);

private:
	bool compare(MazeNode* currentNode, MazeNode* search);

	void drawEdge(MazeNode* A, MazeNode* B, edgeType e);

	void generate();
};

