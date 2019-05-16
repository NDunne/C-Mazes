#pragma once

#include "Maze.h"

class EasyPrimMaze : public Maze
{
public:
	EasyPrimMaze(SDL_Window* w);

private:
	void generate();

	bool compare(MazeNode* currentNode, MazeNode* search);

	void drawEdge(MazeNode* A, MazeNode* B);
};

