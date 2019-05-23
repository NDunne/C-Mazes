#pragma once

#include "..\MSTMaze.h"

class KruskalMaze : public MSTMaze
{
public:
	KruskalMaze(SDL_Window* w);

protected:
	void generate();
	
	std::vector<NodePair> allEdges();
};

