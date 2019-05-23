#include "MazeGenerator.h"


MazeGenerator::MazeGenerator(SDL_Window* sdlWin)
{
	window = sdlWin;
	//Get window surface
	surface = SDL_GetWindowSurface(window);

	//Fill the surface white
	SDL_FillRect(surface, NULL, UNVISITED);

	currentMaze = NULL;
}


MazeGenerator::~MazeGenerator()
{
	delete currentMaze;
}

Maze* MazeGenerator::newMaze(MazeType t, DrawPosition dp)
{
	if (t == PRIM)
	{
		currentMaze = new PrimMaze(window, dp);
	}
	else if (t == KRUSKAL)
	{
		currentMaze = new KruskalMaze(window, dp);
	}
	else if (t == ALDBRO)
	{
		currentMaze = new AldousBroderMaze(window, dp);
	}
	else
	{
		currentMaze = new RecDivMaze(window, dp);
	}

	return currentMaze;
}

Maze* MazeGenerator::getMaze()
{
	return currentMaze;
}
