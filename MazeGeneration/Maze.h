#pragma once

#include <SDL2/SDL.h>

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

enum cellType : Uint32 
{ 
	WALL = 0x0, 
	UNVISITED = 0xF0F0F0,
	VISITED = 0x303030,
	SELECTED = 0xC0C0FF,
	VALID = 0xC0FFC0,
	INVALID = 0xFFC0C0
};

struct node
{
	cellType type;
	Uint32 color;
};

enum direction { NORTH, EAST, SOUTH, WEST, END };

using NodeCoord = std::pair<int, int>;
using nodeTypeMap = std::map<NodeCoord, node>;

using NodePair = std::pair<NodeCoord, NodeCoord>;

const NodeCoord nullNode = { -1, -1 };

const Uint32 red = 0xFF0000;
const Uint32 blue = 0x0000FF;
const Uint32 green = 0x00FF00;

const Uint32 redSingle = 0x10000;
const Uint32 greenSingle = 0x100;
const Uint32 blueSingle = 0x1;

const int startSpeed = 500;

const int X_NODES = 45;
const int Y_NODES = 45;

const int boxLen = 5;
const int boxPad = 0;

const int MAZE_PIXEL_WIDTH = (X_NODES * (boxLen + boxPad)) - boxPad; //550;
const int MAZE_PIXEL_HEIGHT = (Y_NODES * (boxLen + boxPad)) - boxPad;

const int MAZE_PADDING = (2 + (2 * boxPad));

const int MAZE_FRAME_WIDTH = MAZE_PIXEL_WIDTH + (2 * MAZE_PADDING);
const int MAZE_FRAME_HEIGHT = MAZE_PIXEL_HEIGHT + (2 * MAZE_PADDING);

enum DrawPosition { TL, TR, BL, BR };

class Maze
{
public:
	Maze(SDL_Window* w, DrawPosition dp);

	static NodeCoord getAdjNode(int x, int y, direction dir, int dist = 1);
	static NodeCoord getAdjNode(NodeCoord n, direction dir, int dist = 1) { return getAdjNode(n.first, n.second, dir, dist); }

	int drawSpeed;

	node getCellType(NodeCoord n);
	node getCellType(int x, int y) { return getCellType(x, y); }

	void setCellType(NodeCoord n, cellType type, bool update=true);
	void setCellType(int x, int y, cellType type, bool update=true) { return setCellType({ x, y }, type, update); }

	virtual void generate() = 0;

protected:
	SDL_Window* window;
	SDL_Surface* surface;

	void drawDelay();

	virtual void drawBase();

	void finish();

	Uint32 color = blue;
	Uint32 colorDif = redSingle;

	void nextColor();

	void drawCell(int x, int y, Uint32 colour, bool update);

private:
	bool add = true;

	int hPadding, vPadding;

	nodeTypeMap mazeNodes;

	void drawCell(NodeCoord n, Uint32 colour, bool update);
};
