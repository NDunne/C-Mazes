#pragma once

#include "..\MSTMaze.h"

class AldousBroderMaze : public MSTMaze
{
public:
	AldousBroderMaze(SDL_Window* w);

private:
	void generate();

	bool isNullNode(const NodeCoord n);
	NodeCoord randomNeighbor(NodeCoord n, NodeCoord origin);
};

