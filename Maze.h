#pragma once

#include "SDL.h"
#include "MazeAdj.h"

#include <vector>
#include <random>
#include <ctime>

const int MAZE_PIXEL_WIDTH = (MazeNode::X_NODES * (MazeNode::boxLen + MazeNode::boxPad)) - MazeNode::boxPad; //550;
const int MAZE_PIXEL_HEIGHT = (MazeNode::Y_NODES * (MazeNode::boxLen + MazeNode::boxPad)) - MazeNode::boxPad;

const int MAZE_PADDING = (4 * MazeNode::boxPad);

class Maze
{
public:
	enum cellType { WALL, UNVISITED, VISITED, SPECIAL };
	enum edgeType {CANDIDATE, VALID, INVALID };

	Maze(SDL_Window* w);

	void drawBase();

protected:
	SDL_Window* window;
	SDL_Surface* surface;

	Uint32 black;
	Uint32 grey;
	Uint32 white;
	Uint32 green;
	Uint32 red;
	Uint32 blue;

	
	bool DFS(MazeNode* start, MazeNode* search);

	void drawCell(MazeNode* n, Maze::cellType type) { drawCell(n->x, n->y, type); };
	void drawCell(int x, int y, Maze::cellType type);
	void drawCell(MazeNode* n, Uint32 colour) { drawCell(n->x, n->y, colour); };
	void drawCell(int x, int y, Uint32 colour);

	virtual void drawEdge(MazeNode* A, MazeNode* B, edgeType e) = 0;

	MazeAdj mazeEdges;

	//Used in DFS - to say if a node is a match or not, needs to be different
	virtual bool compare(MazeNode* currentNode, MazeNode* search);

	virtual void generate() = 0;

private:
	int hPadding;
};

