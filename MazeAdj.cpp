#include "MazeAdj.h"

void MazeAdj::addEdge(NodePair n, int w)
{
	MazeAdj::addEdge(&n.first, &n.second, w);
}

void MazeAdj::addEdge(int x1, int y1, int x2, int y2, int w)
{
	MazeNode* A = new MazeNode(x1, y1);
	MazeNode* B = new MazeNode(x2, y2);
	addEdge(A, B, w);
}

void MazeAdj::addEdge(MazeNode* A, MazeNode* B, int w)
{
	matrix[A->getPair()][B->getPair()] = { w ,false };
	matrix[B->getPair()][A->getPair()] = { w, false };
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

int MazeAdj::getEdge(MazeNode A, MazeNode B)
{
	return matrix[A.getPair()][B.getPair()].weight;
}

int MazeAdj::getEdge(NodePair p)
{
	return getEdge(p.first, p.second);
}

bool MazeAdj::DFS(MazeNode start, MazeNode search, bool checkAdjacent = false)
{
	std::cout << "DFS: " << start.x << ", " << start.y << " -> " << search.x << ", " << search.y << "\n";

	adjacency matrixCopy = matrix;
	//Make a copy so visited values are only changed in the scope of this function

	std::stack<MazeNode> stack;

	stack.push(start);
	//std::cout << "\n  push " << start.first << "," << start.second << "\n";

	while (!stack.empty())
	{
		//std::cout << "  stack size: " << stack.size() << "\n";
		MazeNode current = stack.top();
		stack.pop();
		//std::cout << "  current: " << current.first << "," << current.second << "\n";

		//if this DFS is before adding the edges we need to DFS for all adjacent Cells that aren't the start.
		if (!checkAdjacent && current == search) return true;
		else if (checkAdjacent && current != start && )
		
		//Check Adjecent tiles to search to see if they are current, unless that adjacent tile is start

		NodeAdj adj = matrixCopy[current.getPair()];

		for (NodeAdj::iterator it = adj.begin(); it != adj.end(); it++)
		{

			//std::cout << "\n check " << current.first << "," << current.second << " -> " << it->first.first << "," << it->first.second << " " << it->second.visited << "\n";
			if (it->second.weight && !it->second.visited)
			{
				matrixCopy[current.getPair()][it->first].visited = true;
				matrixCopy[it->first][current.getPair()].visited = true;
				
				MazeNode* stackItem = new MazeNode(it->first);
				stack.push(*stackItem);
				//std::cout << "-pushed-";
			}
		}
	}

	return false;
}