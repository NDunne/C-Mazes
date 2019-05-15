#include "MazeAdj.h"

void MazeAdj::addEdge(NodePair n, int w)
{
	MazeAdj::addEdge(n.first, n.second, w);
}

void MazeAdj::addEdge(int x1, int y1, int x2, int y2, int w)
{
	MazeNode* A = new MazeNode(x1, y1);
	MazeNode* B = new MazeNode(x2, y2);
	addEdge(A, B, w);
}

void MazeAdj::addEdge(MazeNode* A, MazeNode* B, int w)
{
	matrix[A->getPair()][B->getPair()] = w;
	matrix[B->getPair()][A->getPair()] = w;
}

NodeAdj MazeAdj::getNodeAdj(NodeCoord n)
{
	return matrix[n];
}

NodeAdj MazeAdj::getNodeAdj(MazeNode n)
{
	return matrix[n.getPair()];
}

NodeAdj MazeAdj::getNodeAdj(int x, int y)
{
	MazeNode* A = new MazeNode(x, y);
	return matrix[A->getPair()];
}

adjacency::iterator MazeAdj::getStart()
{
	return matrix.begin();
}

adjacency::iterator MazeAdj::getEnd()
{
	return matrix.end();
}

int MazeAdj::getEdge(MazeNode* A, MazeNode* B)
{
	return matrix[A->getPair()][B->getPair()];
}

int MazeAdj::getEdge(NodePair p)
{
	return getEdge(p.first, p.second);
}

bool MazeAdj::DFS(MazeNode* start, MazeNode* search, bool checkAdjacent)
{
	//LOG std::cout << "\nDFS: " << start->toString() << " -> " << search->toString();

	bool queuedNodes[MazeNode::X_NODES][MazeNode::Y_NODES] = { false };

	adjacency matrixCopy = matrix;
	//Make a copy so visited values are only changed in the scope of this function

	std::stack<MazeNode*> stack;

	stack.push(start);
	queuedNodes[start->x][start->y] = true;
	////LOG std::cout << "\n  push " << start.first << "," << start.second << "\n";

	while (!stack.empty())
	{
		////LOG std::cout << "  stack size: " << stack.size() << "\n";
		MazeNode current = *stack.top();
		MazeNode* currentNode = &current;
		stack.pop();
		//LOG std::cout << "\n  current: " << currentNode->toString();
		
		//Check Adjacent tiles to search to see if they are current, unless that adjacent tile is start
		if (!checkAdjacent && currentNode->equals(search)) return true;
		else if (checkAdjacent && currentNode->nequals(start))
		{
			
			MazeNode* adj1;
			MazeNode* adj2;
			if (search->x == currentNode->x)
			{
				std::cout << "\nchecking y adjacent of " << search->toString() << " for " << currentNode->toString();
				adj1 = search->adjNode(NORTH);
				adj2 = search->adjNode(SOUTH);
				if ((adj1 != nullptr && adj1->equals(currentNode)) || (adj2 != nullptr && adj2->equals(currentNode)))
				{
					return true;
				}
			}
			else if (search->y == currentNode->y)
			{ 
				std::cout << "\nchecking X adjacent of " << search->toString() << " for " << currentNode->toString();
				adj1 = search->adjNode(EAST);
				adj2 = search->adjNode(WEST);
				if ((adj1 != nullptr && adj1->equals(currentNode)) || (adj2 != nullptr && adj2->equals(currentNode)))
				{
					return true;
				}
			}
		}

		//if not found push unchecked connected nodes for checking
		
		NodeAdj adjacentNodes = getNodeAdj(currentNode->getPair());

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