#include "Maze.h"

Maze::Maze(SDL_Window* w)
{
	window = w;
	surface = SDL_GetWindowSurface(window);

	int trueWindowWidth;
	SDL_GetWindowSize(window, &trueWindowWidth, nullptr);

	hPadding = (trueWindowWidth - MAZE_PIXEL_WIDTH) / 2;

	drawSpeed = startSpeed;
}

node Maze::getCellType(NodeCoord n)
{
	return mazeNodes[n];
}

void Maze::setCellType(NodeCoord n, Uint32 type, bool update)
{	
	mazeNodes[n] = {type, (mazeNodes[n].color == 0x0)? color: mazeNodes[n].color };

	drawCell(n, (type==UNVISITED)? color:type, update);
}

void Maze::drawDelay()
{
	if (drawSpeed > 20)
	{
		drawSpeed = (int) drawSpeed*0.9;
	}
	SDL_Delay(drawSpeed);
}

void Maze::drawBase()
{
	for (int i = 0; i < X_NODES; i++)
	{
		for (int j = 0; j < Y_NODES; j++)
		{
			setCellType({ i, j }, WALL, false);
		}
	}

	//Update the surface
	SDL_UpdateWindowSurface(window);
}

void Maze::nextColor()
{
	Uint32 r = (color & red) >> 16;
	Uint32 g = (color & green) >> 8;
	Uint32 b = (color & blue);

	if (add)
	{
		if (colorDif == greenSingle && g == 0xFF)
		{
			colorDif = (Uint32)redSingle;
			add = false;
		}
		else if (colorDif == redSingle && r == 0xFF)
		{
			colorDif = (Uint32)blueSingle;
			add = false;
		}
		//Interesting: because blueSing is 1 it becomes a bool, and gets attached to the && rather than the ==
		else if ((colorDif == blueSingle) && (b == 0xFF))
		{
			colorDif = (Uint32)greenSingle;
			add = false;
		}
	}
	else
	{
		if (colorDif == greenSingle && g == 0)
		{
			colorDif = redSingle;
			add = true;
		}
		else if (colorDif == redSingle && r == 0)
		{
			colorDif = blueSingle;
			add = true;
		}
		else if ((colorDif == blueSingle) && (b == 0))
		{
			colorDif = greenSingle;
			add = true;
		}
	}

	if (add) color += colorDif;
	else color -= colorDif;
}

//enum cellType { WALL, UNVISITED, VISITED, SPECIAL, SELECTED, VALID, INVALID };
void Maze::drawCell(NodeCoord n, Uint32 colour, bool update)
{
	
	return drawCell(n.first, n.second, colour, update);
}

void Maze::drawCell(int x, int y, Uint32 colour, bool update)
{
	SDL_Rect rect = { hPadding + x * (boxLen + boxPad), MAZE_PADDING + y * (boxLen + boxPad), boxLen, boxLen };
	SDL_FillRect(surface, &rect, colour);

	if (update)
	{
		SDL_UpdateWindowSurface(window);
	}
}

NodeCoord Maze::getAdjNode(int x, int y, direction dir, int dist)
{
	switch (dir)
	{
	case NORTH:
		if ((y - dist) > 0)
		{
			return { x, y - dist };
		}
		break;
	case EAST:
		if ((x + dist) < (X_NODES - 1))
		{
			return { x + dist, y };
		}
		break;
	case SOUTH:
		if ((y + dist) < (Y_NODES - 1))
		{
			return { x, y + dist };
		}
		break;
	case WEST:
		if ((x - dist) > 0)
		{
			return { x - dist, y };
		}
		break;
	}

	return nullNode;
}