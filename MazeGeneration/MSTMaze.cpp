#include "MSTMaze.h"

MSTMaze::MSTMaze(SDL_Window* w) : Maze(w)
{}

void MSTMaze::addEdge(NodeCoord A, NodeCoord B)
{
	nextColor();
	mazeEdges.addEdge(A, B);
	drawEdge(A, B, VALID);
}

void MSTMaze::drawEdge(NodeCoord A, NodeCoord B, cellType c)
{
	NodeCoord midNode = { (A.first + B.first) / 2, (A.second + B.second) / 2 };

	setCellType(A, c, false);
	setCellType(midNode, c, false);
	setCellType(B, c, true);
	drawDelay();

	if (c == VALID)
	{
		setCellType(A, UNVISITED, false);
		setCellType(midNode, UNVISITED, false);
		setCellType(B, UNVISITED, true);
		drawDelay();
	}
	else if (c == INVALID)
	{
		setCellType(A, UNVISITED, false);
		setCellType(midNode, WALL, false);
		setCellType(B, UNVISITED, true);
		drawDelay();
	}
}

bool MSTMaze::compare(NodeCoord currentNode, NodeCoord search)
{
	return currentNode == search;
}

bool MSTMaze::DFS(NodeCoord start, NodeCoord search)
{
	//Prevent queuing the same node multiplt times for time
	bool queuedNodes[X_NODES][Y_NODES] = { false };

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
