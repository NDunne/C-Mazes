#pragma once

#include <string>
#include <iterator>
#include <iostream>

using NodeCoord = std::pair<int, int>;

enum direction { NORTH, EAST, SOUTH, WEST, END};

class MazeNode
{
public:
	const static int X_NODES = 45; 
	const static int Y_NODES = 45; 

	const static int boxLen = 2;
	const static int boxPad = 1;

	MazeNode();
	MazeNode(int Xin, int Yin);
	MazeNode(NodeCoord n);

	std::string toString();

	//retuns a new MazeNode with co-ordinates in the required direction
	MazeNode* adjNode(direction dir, int dist = 1);

	int x;
	int y;

	//returns a std::pair<int,int> { x, y }
	NodeCoord getPair();

	//Node is equal
	bool operator== (MazeNode m);
	bool operator!= (MazeNode m);

	bool equals(MazeNode* m);
	bool nequals(MazeNode* m);
};