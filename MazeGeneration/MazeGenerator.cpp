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

Maze* MazeGenerator::newMaze(MazeType t, MazeDifficulty d)
{
	if (t == PRIM)
	{
		switch (d)
		{
		case EASY:
			currentMaze = new EasyPrimMaze(window);
			break;
		case MEDIUM:
			currentMaze = new MedPrimMaze(window);
			break;
		default:
			currentMaze = new HardPrimMaze(window);
		}
	}
	else
		currentMaze = new EasyKruskalMaze(window);

	return currentMaze;
}

Maze* MazeGenerator::getMaze()
{
	return currentMaze;
}
