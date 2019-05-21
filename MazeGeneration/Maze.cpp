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

cellType Maze::getCellType(NodeCoord n)
{
	return mazeNodes[n];
}

void Maze::setCellType(NodeCoord n, cellType type, bool update)
{
	mazeNodes[n] = type;
	drawCell(n, type, update);
}

void Maze::drawDelay()
{
	return;
	if (drawSpeed > 100)
	{
		drawSpeed -= 10;
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
	Uint32 r = (color & 0xFF0000) >> 16;
	Uint32 g = (color & 0xFF00) >> 8;
	Uint32 b = (color & 0xFF);

	if (r > 0 && b == 0) {
		color -= 0x10000;
		color += 0x100;
	}
	if (g > 0 && r == 0) {
		color -= 0x100;
		color += 1;
	}
	if (b > 0 && g == 0) {
		color += 0x10000;
		color -= 1;
	}
}

//enum cellType { WALL, UNVISITED, VISITED, SPECIAL, SELECTED, VALID, INVALID };
void Maze::drawCell(NodeCoord n, cellType type, bool update)
{
	switch (type)
	{
	case WALL:
		return drawCell(n.first, n.second, black, update);
	case UNVISITED:
		return drawCell(n.first, n.second, color, update); //white for demonstrate
	case VISITED:
		return drawCell(n.first, n.second, grey, update);
	case SPECIAL:
		return drawCell(n.first, n.second, white, update); //green for demonstrate
	case SELECTED:
		return drawCell(n.first, n.second, blue, update);
	case VALID:
		return drawCell(n.first, n.second, green, update);
	default:
		return drawCell(n.first, n.second, red, update);
	}
}

void Maze::drawCell(int x, int y, Uint32 colour, bool update)
{
	SDL_Rect rect = { hPadding + x * (boxLen + boxPad), MAZE_PADDING + y * (boxLen + boxPad), boxLen, boxLen };
	SDL_FillRect(surface, &rect, colour);

	if (update) SDL_UpdateWindowSurface(window);
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