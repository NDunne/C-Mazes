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

enum cellType { WALL, UNVISITED, VISITED, SPECIAL, SELECTED, VALID, INVALID };

enum direction { NORTH, EAST, SOUTH, WEST, END };

using NodeCoord = std::pair<int, int>;
using nodeTypeMap = std::map<NodeCoord, cellType>;

using NodePair = std::pair<NodeCoord, NodeCoord>;

const NodeCoord nullNode = { -1, -1 };

const Uint32 black = 0x0;
const Uint32 grey = 0x303030;
const Uint32 white = 0xF0F0F0;
const Uint32 green = 0x00FF00;
const Uint32 red = 0xFF0000;
const Uint32 blue = 0x0000FF;
const Uint32 cyan = 0x00FFFF;

const int startSpeed = 550;

const int X_NODES = 15;
const int Y_NODES = 15;

const int boxLen = 20;
const int boxPad = 1;

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

	cellType getCellType(NodeCoord n);
	cellType getCellType(int x, int y) { return getCellType(x, y); }

	void setCellType(NodeCoord n, cellType type);
	void setCellType(int x, int y, cellType type) { return setCellType({ x, y }, type); }

protected:
	SDL_Window* window;
	SDL_Surface* surface;

	void drawDelay();

	virtual void drawBase();

	virtual void generate() = 0;

private:
	int hPadding;

	nodeTypeMap mazeNodes;

	void drawCell(NodeCoord n, cellType type);
	void drawCell(int x, int y, Uint32 colour);
};