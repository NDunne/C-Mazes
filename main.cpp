//Using SDL and standard IO
#include <iostream>

#include "MazeGenerator.h"

//Screen dimension constants
const int SCREEN_WIDTH = (8 * MazeNode::boxPad) + MazeNode::X_NODES * (MazeNode::boxLen + MazeNode::boxPad); //550;
const int SCREEN_HEIGHT = (8 * MazeNode::boxPad) + MazeNode::Y_NODES * (MazeNode::boxLen + MazeNode::boxPad);

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
		window = SDL_CreateWindow("SDL MAZE", 10, 40, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	MazeGenerator* mazeGen = new MazeGenerator(window);

	Maze* m1 = mazeGen->newMaze(EASYPRIM);

	SDL_Delay(5000);

	Maze* m2 = mazeGen->newMaze(PRIM);

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
