#pragma once
#include "Maze.h"
#include "MazeGraph.h"

class MSTMaze : public Maze
{
public:
	MSTMaze(SDL_Window* w);

protected:
	MazeGraph mazeEdges;

	bool DFS(NodeCoord start, NodeCoord search);
	
	void addEdge(NodeCoord A, NodeCoord B);
	void addEdge(NodePair p) { return addEdge(p.first, p.second); }

	void drawEdge(NodeCoord A, NodeCoord B, cellType c);
	void drawEdge(NodePair p, cellType c) { return drawEdge(p.first, p.second, c);  }

	//Used in DFS - to say if a node is a match or not, needs to be different
	virtual bool compare(NodeCoord currentNode, NodeCoord search);
};

