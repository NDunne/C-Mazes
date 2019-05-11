#include "MazeGenerator.h"
#include "Maze.h"
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

Maze* MazeGenerator::newMaze()
{
	currentMaze = new Maze(window, surface);
	return currentMaze;
}

Maze* MazeGenerator::getMaze()
{
	return currentMaze;
}
