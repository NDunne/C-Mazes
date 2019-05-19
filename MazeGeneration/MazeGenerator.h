#pragma once

#include "PrimMazes\HardPrimMaze.h"
#include "PrimMazes\MedPrimMaze.h"
#include "PrimMazes\EasyPrimMaze.h"

#include "KruskalMazes\EasyKruskalMaze.h"

enum MazeType { PRIM, KRUSKAL };
enum MazeDifficulty {EASY, MEDIUM, HARD };

class MazeGenerator
{
public:
	MazeGenerator(SDL_Window* sdlWin);
	~MazeGenerator();

	Maze* newMaze(MazeType t, MazeDifficulty d);

	Maze* getMaze();

private:
	SDL_Window* window;
	SDL_Surface* surface;
	Maze* currentMaze;
};

