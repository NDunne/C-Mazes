#pragma once

#include "..\MSTMaze.h"

class PrimMaze : public MSTMaze
{
public:
	PrimMaze(SDL_Window* w, DrawPosition dp);

	void generate();
};

