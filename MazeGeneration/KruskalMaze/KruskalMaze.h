#pragma once

#include "..\MSTMaze.h"

class KruskalMaze : public MSTMaze
{
public:
	KruskalMaze(SDL_Window* w, DrawPosition dp);

	void generate();

protected:
	std::vector<NodePair> allEdges();
};

