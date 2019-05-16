#pragma once

#include <string>
#include <iterator>
#include <iostream>

using NodeCoord = std::pair<int, int>;

enum direction { NORTH, EAST, SOUTH, WEST, END};

class MazeNode
{
public:
	const static int X_NODES = 11; //0 & 44 must be walls
	const static int Y_NODES = 19; //0 & 44 must be walls

	MazeNode();
	MazeNode(int Xin, int Yin);
	MazeNode(NodeCoord n);

	std::string toString();

	//retuns a new MazeNode with co-ordinates in the required direction
	MazeNode* adjNode(direction d);

	int x;
	int y;

	//returns a std::pair<int,int> { x, y }
	NodeCoord getPair();

	//Node is equal
	bool operator== (MazeNode m);
	bool operator!= (MazeNode m);

	bool equals(MazeNode* m);
	bool nequals(MazeNode* m);

	bool checkAdj(MazeNode check);
};