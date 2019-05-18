//Using SDL and standard IO
#include <iostream>

#include "MazeGenerator.h"

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

	std::cout << "window: " << std::to_string(width) << " by " << std::to_string(height);

	MazeGenerator* mazeGen = new MazeGenerator(window);

	Maze* m1 = mazeGen->newMaze(PRIM, EASY);

	SDL_Delay(5000);

	Maze* m2 = mazeGen->newMaze(PRIM, MEDIUM);

	SDL_Delay(5000);

	Maze* m3 = mazeGen->newMaze(PRIM, HARD);

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

	close(window);

	return 0;
}
