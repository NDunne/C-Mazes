#include "Maze.h"


Maze::Maze(SDL_Window* w)
{
	window = w;
	surface = SDL_GetWindowSurface(window);

	black = SDL_MapRGB(surface->format, 0x0, 0x0, 0x0);
	grey = SDL_MapRGB(surface->format, 0x30, 0x30, 0x30);
	white = SDL_MapRGB(surface->format, 0xF0, 0xF0, 0xF0);
	green = SDL_MapRGB(surface->format, 0x0, 0xFF, 0x0);
	red = SDL_MapRGB(surface->format, 0xFF, 0x0, 0x0);
	blue = SDL_MapRGB(surface->format, 0x0, 0x0, 0xFF);

	int trueWindowWidth;
	SDL_GetWindowSize(window, &trueWindowWidth, nullptr);

	hPadding = (trueWindowWidth - MAZE_PIXEL_WIDTH) / 2;

	std::cout << "\nMaze: " << std::to_string(MAZE_PIXEL_WIDTH) << " by " << std::to_string(MAZE_PIXEL_WIDTH);

	std::cout << "\nPadding: \n h: " << std::to_string(hPadding) << "\n v: " << std::to_string(MAZE_PADDING);
}

void Maze::drawBase()
{
	for (int i = 0; i < MazeNode::X_NODES; i++)
	{
		for (int j = 0; j < MazeNode::Y_NODES; j++)
		{
			drawCell(i, j, WALL);
		}
	}

	//Update the surface
	SDL_UpdateWindowSurface(window);
}

void Maze::drawCell(int x, int y, Maze::cellType type)
{
	Uint32 colour;

	switch (type)
	{
	case UNVISITED:
		return drawCell(x, y, white);
	case VISITED:
		return drawCell(x, y, grey);
	case WALL:
		return drawCell(x, y, black);
	default:
		return drawCell(x, y, green);
	}
}

void Maze::drawCell(int x, int y, Uint32 colour)
{
	SDL_Rect rect = { hPadding + x * (MazeNode::boxLen + MazeNode::boxPad), MAZE_PADDING + y * (MazeNode::boxLen + MazeNode::boxPad), MazeNode::boxLen, MazeNode::boxLen };
	SDL_FillRect(surface, &rect, colour);

	SDL_UpdateWindowSurface(window);
}

bool Maze::compare(MazeNode* currentNode, MazeNode* search)
{
	return currentNode->equals(search);
}

bool Maze::DFS(MazeNode* start, MazeNode* search)
{
	//Prevent queuing the same node multiplt times for time
	bool queuedNodes[MazeNode::X_NODES][MazeNode::Y_NODES] = { false };

	//Make a copy so visited values are only changed in the scope of this function
	//MazeAdj MazeCopy = mazeEdges;

	//DFS Stack
	std::stack<MazeNode*> stack;

	//Push start node to top of stack
	stack.push(start);

	//flag so it isn't pushed again in this search
	queuedNodes[start->x][start->y] = true;

	while (!stack.empty())
	{
		//Little copy thing so the value isn't lost when it is popped
		MazeNode current = *stack.top();
		MazeNode* currentNode = &current;

		//Remove from the stack as top() leaves it
		stack.pop();

		//compare function may check other nodes than search, e.g. a cross
		if (currentNode->nequals(start) && compare(currentNode, search))
		{
			return true;
		}

		//if not found push unchecked connected nodes for checking

		NodeAdj adjacentNodes = mazeEdges.getNodeAdj(currentNode->getPair());

		//it first  = NodeCoord of adjacent node
		//it second = weight of edge (1 or 0);
		for (NodeAdj::iterator it = adjacentNodes.begin(); it != adjacentNodes.end(); it++)
		{
			if (!queuedNodes[it->first.first][it->first.second] && it->second)
			{
				MazeNode* newNode = new MazeNode(it->first.first, it->first.second);
				stack.push(newNode);
				queuedNodes[it->first.first][it->first.second] = true;

				//LOG std::cout << "\n   pushing: " << newNode->toString();
			}
		}
	}

	return false;
}
