#include "MazeGenerator.h"


MazeGenerator::MazeGenerator(SDL_Window* sdlWin)
{
	window = sdlWin;
	//Get window surface
	surface = SDL_GetWindowSurface(window);

	//Fill the surface white
	SDL_FillRect(surface, NULL, UNVISITED);
}

Maze* MazeGenerator::newMaze(MazeType t, DrawPosition dp)
{
	if (t == PRIM)
	{
		return new PrimMaze(window, dp);
	}
	else if (t == KRUSKAL)
	{
		return new KruskalMaze(window, dp);
	}
	else if (t == ALDBRO)
	{
		return new AldousBroderMaze(window, dp);
	}
	else
	{
		return new RecDivMaze(window, dp);
	}
}

