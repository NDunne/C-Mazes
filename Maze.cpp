#include "Maze.h"


Maze::Maze(SDL_Window* w)
{
	window = w;
	surface = SDL_GetWindowSurface(window);

	black = SDL_MapRGB(surface->format, 0x0, 0x0, 0x0);
	grey = SDL_MapRGB(surface->format, 0x30, 0x30, 0x30);
	white = SDL_MapRGB(surface->format, 0xF0, 0xF0, 0xF0);
	green = SDL_MapRGB(surface->format, 0x0, 0xF0, 0x0);
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

void Maze::drawCell(MazeNode* n, Maze::cellType type)
{
	Maze::drawCell(n->x, n->y, type);
}

void Maze::drawCell(int x, int y, Maze::cellType type)
{
	SDL_Rect rect = { (5 * MazeNode::boxPad) + x * (MazeNode::boxLen + MazeNode::boxPad), (5 * MazeNode::boxPad) + y * (MazeNode::boxLen + MazeNode::boxPad), MazeNode::boxLen, MazeNode::boxLen };

	Uint32 colour;

	switch (type)
	{
	case UNVISITED:
		colour = white;
		break;
	case VISITED:
		colour = grey;
		break;
	case WALL:
		colour = black;
		break;
	default:
		colour = green;
		break;
	}
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
