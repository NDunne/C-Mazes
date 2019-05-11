#include "Maze.h"
#include <iostream>

Maze::Maze(SDL_Window* w, SDL_Surface* s)
{
	window = w;
	surface = s;

	black = SDL_MapRGB(surface->format, 0x0, 0x0, 0x0);
	grey = SDL_MapRGB(surface->format, 0x30, 0x30, 0x30);
	white = SDL_MapRGB(surface->format, 0xF0, 0xF0, 0xF0);

	for (int x = 0; x < X_CELLS; x++)
	{
		for (int y = 0; y < Y_CELLS; y++)
		{
			cells[x][y] = WALL;
		}
	}
}


Maze::~Maze()
{
}

void Maze::draw()
{	
	for (int i = 0; i < X_CELLS; i++)
	{
		for (int j = 0; j < Y_CELLS; j++)
		{
			SDL_Rect rect = { boxPad+ 4 + i * (boxLen + boxPad), boxPad + 4 + j * (boxLen + boxPad), boxLen, boxLen };
			SDL_FillRect(surface, &rect,(cells[i][j] == WALL)? black:white);
		}
	}

	//Update the surface
	SDL_UpdateWindowSurface(window);
}
