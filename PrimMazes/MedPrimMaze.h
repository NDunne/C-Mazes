#pragma once

#include "..\Maze.h"

class MedPrimMaze : public Maze
{
public:
	MedPrimMaze(SDL_Window* w);

private:
	void generate();

	bool compare(MazeNode* currentNode, MazeNode* search);

	void drawEdge(MazeNode* A, MazeNode* B, edgeType e);
};

