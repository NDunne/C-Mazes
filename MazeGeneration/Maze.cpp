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

void Maze::setCellType(NodeCoord n, cellType type)
{
	mazeNodes[n] = type;
	drawCell(n, type);
}

void Maze::drawDelay()
{
	if (drawSpeed > 50)
	{
		drawSpeed -= 50;
	}
	SDL_Delay(drawSpeed);
}

void Maze::drawBase()
{
	for (int i = 0; i < X_NODES; i++)
	{
		for (int j = 0; j < Y_NODES; j++)
		{
			setCellType({ i, j }, WALL);
		}
	}

	//Update the surface
	SDL_UpdateWindowSurface(window);
}

//enum cellType { WALL, UNVISITED, VISITED, SPECIAL, SELECTED, VALID, INVALID };
void Maze::drawCell(NodeCoord n, cellType type)
{
	switch (type)
	{
	case WALL:
		return drawCell(n.first, n.second, black);
	case UNVISITED:
		return drawCell(n.first, n.second, white);
	case VISITED:
		return drawCell(n.first, n.second, grey);
	case SPECIAL:
		return drawCell(n.first, n.second, green);
	case SELECTED:
		return drawCell(n.first, n.second, blue);
	case VALID:
		return drawCell(n.first, n.second, green);
	default:
		return drawCell(n.first, n.second, red);
	}
}

void Maze::drawCell(int x, int y, Uint32 colour)
{
	SDL_Rect rect = { hPadding + x * (boxLen + boxPad), MAZE_PADDING + y * (boxLen + boxPad), boxLen, boxLen };
	SDL_FillRect(surface, &rect, colour);

	SDL_UpdateWindowSurface(window);
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