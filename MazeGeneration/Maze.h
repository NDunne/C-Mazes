#pragma once

#include "SDL.h"

#include <iterator>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <map>

const enum cellType : Uint32 
{ 
	WALL = 0x0, 
	UNVISITED,
	VISITED = 0x303030,
	//SPECIAL = 0x00FF00,
	SELECTED = 0xF1F1F1,
	VALID = 0x000000,
	INVALID = 0xF5F5F5
};

struct node
{
	Uint32 type;
	Uint32 color;
};

enum direction { NORTH, EAST, SOUTH, WEST, END };

using NodeCoord = std::pair<int, int>;
using nodeTypeMap = std::map<NodeCoord, node>;

using NodePair = std::pair<NodeCoord, NodeCoord>;

const NodeCoord nullNode = { -1, -1 };
/*
const Uint32 black = 0x0;
const Uint32 grey = 0x303030;
const Uint32 white = 0xFFFFFF;
const Uint32 light = 0xF0F0F0;

const Uint32 red = 0xFF0000;
const Uint32 blue = 0x0000FF;
const Uint32 green = 0x00FF00;
const Uint32 cyan = 0x00FFFF;
*/

const Uint32 red = 0xFF0000;
const Uint32 blue = 0x0000FF;
const Uint32 green = 0x00FF00;

const Uint32 redSingle = 0x10000;
const Uint32 greenSingle = 0x100;
const Uint32 blueSingle = 0x1;

const int startSpeed = 710;

const int X_NODES = 45;
const int Y_NODES = 45;

const int boxLen = 2;
const int boxPad = 0;

const int MAZE_PIXEL_WIDTH = (X_NODES * (boxLen + boxPad)) - boxPad; //550;
const int MAZE_PIXEL_HEIGHT = (Y_NODES * (boxLen + boxPad)) - boxPad;

const int MAZE_PADDING = (4 * boxPad);

class Maze
{
public:
	Maze(SDL_Window* w);

	static NodeCoord getAdjNode(int x, int y, direction dir, int dist = 1);
	static NodeCoord getAdjNode(NodeCoord n, direction dir, int dist = 1) { return getAdjNode(n.first, n.second, dir, dist); }

	int drawSpeed;

	node getCellType(NodeCoord n);
	node getCellType(int x, int y) { return getCellType(x, y); }

	void setCellType(NodeCoord n, Uint32 type, bool update=true);
	void setCellType(int x, int y, Uint32 type, bool update=true) { return setCellType({ x, y }, type, update); }

protected:
	SDL_Window* window;
	SDL_Surface* surface;

	void drawDelay();

	virtual void drawBase();

	virtual void generate() = 0;

	Uint32 color = red;

	void nextColor();

	void drawCell(int x, int y, Uint32 colour, bool update);

private:
	Uint32 colorDif = greenSingle;
	bool add = true;

	int hPadding;

	nodeTypeMap mazeNodes;

	void drawCell(NodeCoord n, Uint32 colour, bool update);
};