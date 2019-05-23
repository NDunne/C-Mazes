//Using SDL and standard IO
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <thread>

#include <iostream>

#include "MazeGeneration\MazeGenerator.h"

/*
TODO
- efficiency? get rid of padding and fill multiple cells at once?
- solvers
- text to show algorithm used
*/
bool quit = false;

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
		window = SDL_CreateWindow("SDL MAZE", 10, 40, 2*MAZE_FRAME_WIDTH, 2*MAZE_FRAME_HEIGHT, SDL_WINDOW_SHOWN);
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

int testFunction(void* data)
{
	std::cout << "Hi I'm a thread";

	return 0;
}

int generate(void* m)
{
	Maze* maze = (Maze*)m;
	maze->generate();

	return 0;
}

int main(int argc, char** argv)
{
	SDL_Window* window = initSDL();

	int width;
	int height;

	SDL_GetWindowSize(window, &width, &height);

	MazeGenerator* mazeGen = new MazeGenerator(window);
	
	Maze* m4 = mazeGen->newMaze(RECDIV, BR);

	Maze* m1 = mazeGen->newMaze(PRIM, TL);

	Maze* m2 = mazeGen->newMaze(KRUSKAL, TR);
	
	Maze* m3 = mazeGen->newMaze(ALDBRO, BL);

	std::thread t1(generate, m1);
	std::thread t2(generate, m2);
	std::thread t3(generate, m3);
	std::thread t4(generate, m4);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << "done";

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

	delete m1;
	delete m2;
	delete m3;
	delete m4; 

	delete mazeGen;

	close(window);

	return 0;
}

