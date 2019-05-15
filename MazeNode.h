#pragma once

#include <string>
#include <iterator>
#include <iostream>

using NodeCoord = std::pair<int, int>;

enum direction { NORTH, EAST, SOUTH, WEST, END};

class MazeNode
{
public:
	MazeNode();
	MazeNode(int Xin, int Yin);
	MazeNode(NodeCoord n);

	//retuns a new MazeNode with co-ordinates in the required direction
	MazeNode* adjNode(direction d);

	int x;
	int y;

	//returns a std::pair<int,int> { x, y }
	NodeCoord getPair();

	//Node is equal
	bool operator== (MazeNode m);
	bool operator!= (MazeNode m);

	bool checkAdj(MazeNode check);
};