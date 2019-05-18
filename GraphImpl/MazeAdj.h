#pragma once

#include <stack>
#include <map>

#include "MazeNode.h"

using NodeAdj = std::map < NodeCoord, int > ;
using adjacency = std::map< NodeCoord, NodeAdj >;

//an adjacency: A:(Ax,Ay) -> (B:(Bx,By) -> w(A,B))

using NodePair = std::pair<MazeNode*, MazeNode*>;

class MazeAdj
{
public:
	void addEdge(NodePair n, int w);
	void addEdge(MazeNode* A, MazeNode* B, int w);
	void addEdge(int x1, int y1, int x2, int y2, int w);

	//return start iterator
	adjacency::iterator getStart();

	//return end iterator
	adjacency::iterator getEnd();

	//retrieve the edge weight from the matrix
	int getEdge(NodePair p);
	int getEdge(MazeNode* A, MazeNode* B);

	//retrieve map of Nodes to weights of their edge to the paramter MazeNode
	NodeAdj getNodeAdj(MazeNode n);
	//retrieve map of Nodes to weights of their edge to the paramter NodeCoord
	NodeAdj getNodeAdj(NodeCoord n);
	//retrieve map of Nodes to weights of their edge to the paramter co-ordinates
	NodeAdj getNodeAdj(int x, int y);

private:
	adjacency matrix;
};

