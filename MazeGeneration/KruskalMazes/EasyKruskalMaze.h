#pragma once

#include "..\Maze.h"

class EasyKruskalMaze : public Maze
{
public:
	EasyKruskalMaze(SDL_Window* w);

private:
	void generate();

	//bool compare(NodeCoord currentNode, NodeCoord search);

	void drawEdge(NodeCoord A, NodeCoord B, edgeType e);
	void drawEdge(NodePair pair, edgeType e) { return drawEdge(pair.first, pair.second, e); }

	std::vector<NodePair> allEdges();
};

