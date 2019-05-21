#pragma once
#include "..\Maze.h"
struct nodeContainer
{
	int xStart;
	int yStart;
	int xLimit;
	int yLimit;
};

class RecDivMaze : public Maze
{
public:
	RecDivMaze(SDL_Window* w);

protected:
	void generate();

	void drawContainer(nodeContainer bounds);

	virtual void drawBase();

	void splitContainer(nodeContainer currentNodes);

	bool isTripleCorridor(nodeContainer currentNodes, int numX, int numY);

	bool drawHWall(int x1, int x2, int y);

	bool drawVWall(int x, int y1, int y2);
};

