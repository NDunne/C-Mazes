#include "PrimMaze.h"

PrimMaze::PrimMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

void PrimMaze::generate()
{
	drawBase();
	MazeNode* start = new MazeNode(1, 1);
	MazeNode* end = new MazeNode(MazeNode::X_NODES - 2, MazeNode::Y_NODES - 2);

	MazeNode* endNorth = end->adjNode(NORTH);
	MazeNode* endWest = end->adjNode(WEST);

	drawCell(start, SPECIAL);
	drawCell(end, SPECIAL);

	std::vector<NodePair> edges;

	srand((unsigned)time(0));

	if (rand() % 2)
	{
		edges.push_back({ start, start->adjNode(EAST) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(EAST)->toString();
	}
	else
	{
		edges.push_back({ start, start->adjNode(SOUTH) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(SOUTH)->toString();
	}
	
	while (!edges.empty())
	{
		int currentIndex = rand() % edges.size();
		NodePair currentEdge = edges[currentIndex];

		std::cout << "\ncurrentEdge: " << currentEdge.first->toString() << " -> " << currentEdge.second->toString();

		if (!DFS(currentEdge.first, currentEdge.second))
		{
			//LOG std::cout << "\n no path";
			mazeEdges.addEdge(currentEdge, 1);

			MazeNode* B = currentEdge.second;

			if (B->equals(endNorth) || B->equals(endWest))
			{
				mazeEdges.addEdge(B, end, 1);
			}

			drawCell(B, UNVISITED);
			SDL_Delay(10);

			for (int dir = NORTH; dir != END; dir++)
			{
				direction e_dir = (direction)dir;

				MazeNode* newNode = B->adjNode(e_dir);
				if (newNode != nullptr && !mazeEdges.getEdge(B,newNode))
				{
					edges.push_back({ B, newNode });
					//LOG std::cout << "\n Maze edge queued: " << B->toString() << " -> " << newNode->toString();
				}
			}
		}

		edges.erase(edges.begin() + currentIndex);
	}
}

bool PrimMaze::compare(MazeNode* currentNode, MazeNode* search)
{
	MazeNode* adj1;
	MazeNode* adj2;

	//Efficiency - checking cross requires that x or y is the same
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

	return false;
}