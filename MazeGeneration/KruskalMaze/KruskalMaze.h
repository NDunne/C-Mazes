#pragma once

#include "..\MSTMaze.h"

class KruskalMaze : public MSTMaze
{
public:
	KruskalMaze(SDL_Window* w, DrawPosition dp);

protected:
	void generate();
	
	std::vector<NodePair> allEdges();
};

