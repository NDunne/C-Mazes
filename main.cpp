//Using SDL and standard IO
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "MazeGeneration\MazeGenerator.h"

/*
TODO
- Kruskals generator
- Recursive division generator
*/

SDL_Window* initSDL()
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		throw;
	}
	else
	{
		//Create window
		//Parameters: Name, xPos, yPos, xLen, yLen
		window = SDL_CreateWindow("SDL MAZE", 10, 40, MAZE_PIXEL_WIDTH + (2*MAZE_PADDING), MAZE_PIXEL_HEIGHT + (2*MAZE_PADDING), SDL_WINDOW_SHOWN);
		if (window == NULL)
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			throw;
		}
	}

	return window;
}

void close(SDL_Window* window)
{
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char** argv)
{
	SDL_Window* window = initSDL();

	int width;
	int height;

	SDL_GetWindowSize(window, &width, &height);

	MazeGenerator* mazeGen = new MazeGenerator(window);
	
	Maze* m1 = mazeGen->newMaze(PRIM);

	SDL_Delay(2000);

	m1 = mazeGen->newMaze(KRUSKAL);

	SDL_Delay(2000);
	
	m1 = mazeGen->newMaze(RECDIV);

	delete m1;

	bool quit = false;

	SDL_Event e;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
	
	delete mazeGen;

	close(window);

	_CrtDumpMemoryLeaks();

	return 0;
}