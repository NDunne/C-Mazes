#include "HardPrimMaze.h"

HardPrimMaze::HardPrimMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

void HardPrimMaze::drawEdge(MazeNode* A, MazeNode* B, edgeType e)
{
	switch (e)
	{
	case CANDIDATE:
		drawCell(A, blue);
		drawCell(B, blue);
		break;
	case VALID:
		drawCell(A, green);
		drawCell(B, green);
		SDL_Delay(50);
		drawCell(A, UNVISITED);
		drawCell(B, UNVISITED);
		break;
	case INVALID:
		drawCell(A, red);
		drawCell(B, red);
		SDL_Delay(50);
		drawCell(A, UNVISITED);
		drawCell(B, WALL);
		break;
	}
}

void HardPrimMaze::generate()
{
	drawBase();
	MazeNode* start = new MazeNode(1, 1);
	MazeNode* end = new MazeNode(MazeNode::X_NODES - 2, MazeNode::Y_NODES - 2);

	MazeNode* endNorth = end->adjNode(NORTH);
	MazeNode* endWest = end->adjNode(WEST);

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

		MazeNode* A = currentEdge.first;
		MazeNode* B = currentEdge.second;

		drawEdge(A, B, CANDIDATE);
		SDL_Delay(1000 / drawSpeed);

		if (mazeEdges.getEdge(A, B))
		{
			drawEdge(A, B, VALID);
		}

		else if (!DFS(A, B))
		{
			//LOG std::cout << "\n no path";
			mazeEdges.addEdge(currentEdge, 1);

			drawEdge(A, B, VALID);

			if (B->equals(endNorth) || B->equals(endWest))
			{
				mazeEdges.addEdge(B, end, 1);
				drawEdge(B, end, VALID);
			}

			drawCell(B, UNVISITED);

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
		else
		{
			drawEdge(A, B, INVALID);
		}

		edges.erase(edges.begin() + currentIndex);
	}

	drawCell(start, SPECIAL);
	drawCell(end, SPECIAL);
}

bool HardPrimMaze::compare(MazeNode* currentNode, MazeNode* search)
{
	MazeNode* adj1;
	MazeNode* adj2;

	//Efficiency - checking cross requires that x or y is the same
	if (search->x == currentNode->x)
	{
		adj1 = search->adjNode(NORTH);
		adj2 = search->adjNode(SOUTH);
		if ((adj1 != nullptr && adj1->equals(currentNode)) || (adj2 != nullptr && adj2->equals(currentNode)))
		{
			return true;
		}
	}
	else if (search->y == currentNode->y)
	{
		adj1 = search->adjNode(EAST);
		adj2 = search->adjNode(WEST);
		if ((adj1 != nullptr && adj1->equals(currentNode)) || (adj2 != nullptr && adj2->equals(currentNode)))
		{
			return true;
		}
	}

	return false;
}