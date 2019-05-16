#include "EasyPrimMaze.h"

EasyPrimMaze::EasyPrimMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

void EasyPrimMaze::drawEdge(MazeNode* A, MazeNode* B)
{
	MazeNode* midNode = new MazeNode((A->x + B->x) / 2, (A->y + B->y) / 2);
	drawCell(midNode, UNVISITED);
	SDL_Delay(5);
}

void EasyPrimMaze::generate()
{
	drawBase();
	MazeNode* start = new MazeNode(1, 1);
	MazeNode* end = new MazeNode(MazeNode::X_NODES - 2, MazeNode::Y_NODES - 2);

	MazeNode * endNorth = end->adjNode(NORTH,2);
	MazeNode * endWest = end->adjNode(WEST,2);

	drawCell(start, SPECIAL);
	drawCell(end, SPECIAL);

	std::vector<NodePair> edges;

	srand((unsigned)time(0));

	if (rand() % 2)
	{
		edges.push_back({ start, start->adjNode(EAST,2) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(EAST)->toString();
	}
	else
	{
		edges.push_back({ start, start->adjNode(SOUTH,2) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(SOUTH)->toString();
	}

	while (!edges.empty())
	{
		int currentIndex = rand() % edges.size();
		NodePair currentEdge = edges[currentIndex];

		MazeNode* A = currentEdge.first;
		MazeNode* B = currentEdge.second;

		//std::cout << "\ncurrentEdge: " << A->toString() << " -> " << B->toString();

		if (!DFS(A,B))
		{
			//LOG std::cout << "\n no path";
			mazeEdges.addEdge(currentEdge, 1);

			if (B->equals(endNorth) || B->equals(endWest))
			{
				mazeEdges.addEdge(B, end, 1);

				drawEdge(B, end);
			}

			drawEdge(A, B);

			drawCell(B, UNVISITED);
			SDL_Delay(10);

			for (int dir = NORTH; dir != END; dir++)
			{
				direction e_dir = (direction)dir;

				MazeNode* newNode = B->adjNode(e_dir,2);
				if (newNode != nullptr && !mazeEdges.getEdge(B, newNode))
				{
					edges.push_back({ B, newNode });
					//LOG std::cout << "\n Maze edge queued: " << B->toString() << " -> " << newNode->toString();
				}
			}
		}

		edges.erase(edges.begin() + currentIndex);
	}
}

bool EasyPrimMaze::compare(MazeNode * currentNode, MazeNode * search)
{
	MazeNode* adj1;
	MazeNode* adj2;

	//Efficiency - checking cross requires that x or y is the same
	if (search->x == currentNode->x)
	{
		std::cout << "\nchecking y adjacent of " << search->toString() << " for " << currentNode->toString();
		adj1 = search->adjNode(NORTH,2);
		adj2 = search->adjNode(SOUTH,2);
		if ((adj1 != nullptr && adj1->equals(currentNode)) || (adj2 != nullptr && adj2->equals(currentNode)))
		{
			return true;
		}
	}
	else if (search->y == currentNode->y)
	{
		std::cout << "\nchecking X adjacent of " << search->toString() << " for " << currentNode->toString();
		adj1 = search->adjNode(EAST,2);
		adj2 = search->adjNode(WEST,2);
		if ((adj1 != nullptr && adj1->equals(currentNode)) || (adj2 != nullptr && adj2->equals(currentNode)))
		{
			return true;
		}
	}

	return false;
}