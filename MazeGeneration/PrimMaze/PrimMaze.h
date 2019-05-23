#pragma once

#include "..\MSTMaze.h"

class PrimMaze : public MSTMaze
{
public:
	PrimMaze(SDL_Window* w);

private:
	void generate();
};

