#include "MazeGenerator.h"
#include "PrimMaze.h"
#include "EasyPrimMaze.h"

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
{}

Maze* MazeGenerator::newMaze(MazeType t, MazeDifficulty d)
{
	currentMaze = nullptr;
	if (t == PRIM)
	{
		switch (d)
		{
			case EASY:
				currentMaze = new EasyPrimMaze(window);
				break;
			case MEDIUM:
				currentMaze = new EasyPrimMaze(window);
				break;
			default:
				currentMaze = new PrimMaze(window);
		}
	}
	return currentMaze;
}

Maze* MazeGenerator::getMaze()
{
	return currentMaze;
}
