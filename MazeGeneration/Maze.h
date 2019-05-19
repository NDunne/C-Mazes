#pragma once

#include "SDL.h"
#include "MazeGraph.h"

#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>

const int MAZE_PIXEL_WIDTH = (MazeGraph::X_NODES * (MazeGraph::boxLen + MazeGraph::boxPad)) - MazeGraph::boxPad; //550;
const int MAZE_PIXEL_HEIGHT = (MazeGraph::Y_NODES * (MazeGraph::boxLen + MazeGraph::boxPad)) - MazeGraph::boxPad;

const int MAZE_PADDING = (4 * MazeGraph::boxPad);

const int drawSpeed = 1;

const Uint32 black = 0x0;
const Uint32 grey = 0x303030;
const Uint32 white = 0xF0F0F0;
const Uint32 green = 0x00FF00;
const Uint32  red = 0xFF0000;
const Uint32 blue = 0x0000FF;
const Uint32  cyan = 0x00FFFF;

class Maze
{
public:
	enum cellType { WALL, UNVISITED, VISITED, SPECIAL };
	enum edgeType {CANDIDATE, SELECTED, VALID, INVALID };

	Maze(SDL_Window* w);

	void drawBase();

protected:
	SDL_Window* window;
	SDL_Surface* surface;

	bool DFS(NodeCoord start, NodeCoord search);

	void drawCell(NodeCoord n, Maze::cellType type) { drawCell(n.first, n.second, type); };
	void drawCell(int x, int y, Maze::cellType type);
	void drawCell(NodeCoord n, Uint32 colour) { drawCell(n.first, n.second, colour); };
	void drawCell(int x, int y, Uint32 colour);

	virtual void drawEdge(NodeCoord A, NodeCoord B, edgeType e) = 0;

	MazeGraph mazeEdges;

	//Used in DFS - to say if a node is a match or not, needs to be different
	virtual bool compare(NodeCoord currentNode, NodeCoord search);

	virtual void generate() = 0;

private:
	int hPadding;
};

