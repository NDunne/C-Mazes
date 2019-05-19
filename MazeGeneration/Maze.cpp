#include "Maze.h"


Maze::Maze(SDL_Window* w)
{
	window = w;
	surface = SDL_GetWindowSurface(window);

	int trueWindowWidth;
	SDL_GetWindowSize(window, &trueWindowWidth, nullptr);

	hPadding = (trueWindowWidth - MAZE_PIXEL_WIDTH) / 2;

	std::cout << "\nMaze: " << std::to_string(MAZE_PIXEL_WIDTH) << " by " << std::to_string(MAZE_PIXEL_WIDTH);

	std::cout << "\nPadding: \n h: " << std::to_string(hPadding) << "\n v: " << std::to_string(MAZE_PADDING);
}

void Maze::drawBase()
{
	for (int i = 0; i < MazeGraph::X_NODES; i++)
	{
		for (int j = 0; j < MazeGraph::Y_NODES; j++)
		{
			drawCell(i, j, WALL);
		}
	}

	//Update the surface
	SDL_UpdateWindowSurface(window);
}

void Maze::drawCell(int x, int y, Maze::cellType type)
{
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
	SDL_Rect rect = { hPadding + x * (MazeGraph::boxLen + MazeGraph::boxPad), MAZE_PADDING + y * (MazeGraph::boxLen + MazeGraph::boxPad), MazeGraph::boxLen, MazeGraph::boxLen };
	SDL_FillRect(surface, &rect, colour);

	SDL_UpdateWindowSurface(window);
}

bool Maze::compare(NodeCoord currentNode, NodeCoord search)
{
	return currentNode == search;
}

bool Maze::DFS(NodeCoord start, NodeCoord search)
{
	//Prevent queuing the same node multiplt times for time
	bool queuedNodes[MazeGraph::X_NODES][MazeGraph::Y_NODES] = { false };

	//Make a copy so visited values are only changed in the scope of this function
	//MazeAdj MazeCopy = mazeEdges;

	//DFS Stack
	std::stack<NodeCoord> stack;

	//Push start node to top of stack
	stack.push(start);

	//flag so it isn't pushed again in this search
	queuedNodes[start.first][start.second] = true;

	while (!stack.empty())
	{
		NodeCoord currentNode = stack.top();
	
		//Remove from the stack as top() leaves it
		stack.pop();
		//delete top_p;

		//compare function may check other nodes than search, e.g. a cross
		if (currentNode != start && compare(currentNode, search))
		{
			return true;
		}

		//if not found push unchecked connected nodes for checking

		NodeAdj adjacentNodes = mazeEdges.getNodeEdges(currentNode);

		//it first  = NodeCoord of adjacent node
		//it second = weight of edge (1 or 0);
		for (NodeAdj::iterator it = adjacentNodes.begin(); it != adjacentNodes.end(); it++)
		{
			if (!queuedNodes[it->first.first][it->first.second] && it->second)
			{
				NodeCoord newNode = { it->first.first, it->first.second };
				stack.push(newNode);
				queuedNodes[it->first.first][it->first.second] = true;

				//LOG std::cout << "\n   pushing: " << newNode->toString();
			}
		}
	}

	return false;
}
