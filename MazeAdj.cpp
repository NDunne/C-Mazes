#include "MazeAdj.h"

MazeAdj::MazeAdj()
{
}


MazeAdj::~MazeAdj()
{
}

void MazeAdj::addEdge(NodePair n, int w)
{
	addEdge(n.first, n.second, w);
}

void MazeAdj::addEdge(int x1, int y1, int x2, int y2, int w)
{
	NodeCoord A = std::make_pair(x1, y1);
	NodeCoord B = std::make_pair(x2, y2);
	addEdge(A, B, w);
}

void MazeAdj::addEdge(NodeCoord A, NodeCoord B, int w)
{
	matrix[A][B] = { w ,false };
	matrix[B][A] = { w, false };
}

NodeAdj MazeAdj::getAdjacent(NodeCoord node)
{
	return matrix[node];
}

NodeAdj MazeAdj::getAdjacent(int x, int y)
{
	return matrix[std::make_pair(x, y)];
}

adjacency::iterator MazeAdj::getStart()
{
	return matrix.begin();
}

adjacency::iterator MazeAdj::getEnd()
{
	return matrix.end();
}

std::string MazeAdj::NodeCoordToString(NodeCoord* n)
{
	return (n->first + ":" + n->second);
}

bool MazeAdj::DFS(NodeCoord start, NodeCoord search)
{
	std::cout << "DFS: " << start.first << ", " << start.second << " -> " << search.first << ", " << search.second << "\n";

	adjacency matrixCopy = matrix;
	//Make a copy so visited values are only changed in the scope of this function

	std::stack<NodeCoord> stack;

	stack.push(start);
	//std::cout << "\n  push " << start.first << "," << start.second << "\n";

	while (!stack.empty())
	{
		//std::cout << "  stack size: " << stack.size() << "\n";
		NodeCoord current = stack.top();
	
		//std::cout << "  current: " << current.first << "," << current.second << "\n";

		if (current == search) return true;

		stack.pop();
		NodeAdj adj = matrixCopy[current];

		for (NodeAdj::iterator it = adj.begin(); it != adj.end(); it++)
		{

			//std::cout << "\n check " << current.first << "," << current.second << " -> " << it->first.first << "," << it->first.second << " " << it->second.visited << "\n";
			if (!it->second.visited)
			{
				matrixCopy[current][it->first].visited = true;
				matrixCopy[it->first][current].visited = true;
				stack.push(it->first);
				//std::cout << "-pushed-";
			}
		}
	}

	return false;
}