#pragma once

#include "..\Maze.h"

class KruskalMaze : public Maze
{
public:
	KruskalMaze(SDL_Window* w);

protected:
	void generate();

	void drawEdge(NodeCoord A, NodeCoord B, edgeType e);
	void drawEdge(NodePair pair, edgeType e) { return drawEdge(pair.first, pair.second, e); }

	std::vector<NodePair> allEdges();
};

