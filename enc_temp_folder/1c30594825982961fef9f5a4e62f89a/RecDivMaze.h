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

	virtual void drawBase();

	void splitContainer(nodeContainer currentNodes);

	void drawHWall(int x1, int x2, int y);

	void drawVWall(int x, int y1, int y2);
};

