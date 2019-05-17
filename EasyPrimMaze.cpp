#include "EasyPrimMaze.h"

EasyPrimMaze::EasyPrimMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

void EasyPrimMaze::drawEdge(MazeNode* A, MazeNode* B, edgeType e)
{
	MazeNode* midNode = new MazeNode((A->x + B->x) / 2, (A->y + B->y) / 2);
	
	switch (e)
	{
	case CANDIDATE:
		drawCell(A, blue);
		drawCell(midNode, blue);
		drawCell(B, blue);
		break;
	case VALID:
		drawCell(A, green);
		drawCell(midNode, green);
		drawCell(B, green);
		SDL_Delay(50);
		drawCell(A, UNVISITED);
		drawCell(midNode, UNVISITED);
		drawCell(B, UNVISITED);
		break;
	case INVALID:
		drawCell(A, red);
		drawCell(midNode, red);
		drawCell(B, red);
		SDL_Delay(50);
		drawCell(A, UNVISITED);
		drawCell(midNode, WALL);
		drawCell(B, WALL);
		break;
	default:
		return;
	}
}

void EasyPrimMaze::generate()
{
	drawBase();
	MazeNode* start = new MazeNode(1, 1);
	MazeNode* end = new MazeNode(MazeNode::X_NODES - 2, MazeNode::Y_NODES - 2);

	MazeNode * endNorth = end->adjNode(NORTH,2);
	MazeNode * endWest = end->adjNode(WEST,2);

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

		drawEdge(A, B, CANDIDATE);
		SDL_Delay(500);
		//std::cout << "\ncurrentEdge: " << A->toString() << " -> " << B->toString();

		if (mazeEdges.getEdge(A, B))
		{
			drawEdge(A, B, VALID);
		}

		else if (!DFS(A,B))
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
			SDL_Delay(10);

			for (int dir = NORTH; dir != END; dir++)
			{
				direction e_dir = (direction)dir;

				MazeNode* newNode = B->adjNode(e_dir,2);
				if (newNode != nullptr && !mazeEdges.getEdge(B, newNode))
				{
					edges.push_back({ B, newNode });
					//drawCell(newNode, cyan);
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

bool EasyPrimMaze::compare(MazeNode * currentNode, MazeNode * search)
{
	MazeNode* adj1;
	MazeNode* adj2;

	//Efficiency - checking cross requires that x or y is the same
	if (search->x == currentNode->x)
	{
		adj1 = search->adjNode(NORTH,2);
		adj2 = search->adjNode(SOUTH,2);
		if ((adj1 != nullptr && adj1->equals(currentNode)) || (adj2 != nullptr && adj2->equals(currentNode)))
		{
			return true;
		}
	}
	else if (search->y == currentNode->y)
	{
		adj1 = search->adjNode(EAST,2);
		adj2 = search->adjNode(WEST,2);
		if ((adj1 != nullptr && adj1->equals(currentNode)) || (adj2 != nullptr && adj2->equals(currentNode)))
		{
			return true;
		}
	}

	return false;
}