#pragma once

#include "Maze.h"

#include <string>
#include <stack>

using NodeAdj = std::map < NodeCoord, int > ;
using adjacency = std::map< NodeCoord, NodeAdj >;

//an adjacency: A:(Ax,Ay) -> (B:(Bx,By) -> w(A,B))

class MazeGraph
{
public:
	void addEdge(NodePair n, int w) { return addEdge(n.first, n.second); }
	void addEdge(int x1, int y1, int x2, int y2) { return addEdge({ x1, y1 }, { x2, y2 }); }
	void addEdge(NodeCoord A, NodeCoord B);

	void removeEdge(NodePair n, int w) { return addEdge(n.first, n.second); }
	void removeEdge(int x1, int y1, int x2, int y2) { return addEdge({ x1, y1 }, { x2, y2 }); }
	void removeEdge(NodeCoord A, NodeCoord B);

	//retrieve the edge weight from the matrix
	int getEdge(NodePair p) { return getEdge(p.first, p.second); }
	int getEdge(NodeCoord A, NodeCoord B);

	//retrieve map of Nodes to weights of their edge to the paramter co-ordinates
	NodeAdj getNodeEdges(int x, int y) { return getNodeEdges({ x, y }); };
	//retrieve map of Nodes to weights of their edge to the paramter NodeCoord
	NodeAdj getNodeEdges(NodeCoord n);

private:
	adjacency matrix;
};

