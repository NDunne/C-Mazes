#include "MazeGenerator.h"


MazeGenerator::MazeGenerator(SDL_Window* sdlWin)
{
	window = sdlWin;
	//Get window surface
	surface = SDL_GetWindowSurface(window);

	//Fill the surface white
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
	
	currentMaze = NULL;
}


MazeGenerator::~MazeGenerator()
{
	delete currentMaze;
}

Maze* MazeGenerator::newMaze(MazeType t)
{
	if (t == PRIM)
	{
		currentMaze = new PrimMaze(window);
	}
	else if (t == KRUSKAL)
	{
		currentMaze = new KruskalMaze(window);
	}
	else
	{
		currentMaze = new RecDivMaze(window);
	}

	return currentMaze;
}

Maze* MazeGenerator::getMaze()
{
	return currentMaze;
}
