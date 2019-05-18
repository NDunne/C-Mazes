#include "MedPrimMaze.h"

MedPrimMaze::MedPrimMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

void MedPrimMaze::drawEdge(MazeNode* A, MazeNode* B, edgeType e)
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
		drawCell(B, UNVISITED);
		break;
	default:
		return;
	}
}

void MedPrimMaze::generate()
{
	drawBase();
	MazeNode* start = new MazeNode(1, 1);
	MazeNode* end = new MazeNode(MazeNode::X_NODES - 2, MazeNode::Y_NODES - 2);

	MazeNode * endNorth = end->adjNode(NORTH, 2);
	MazeNode * endWest = end->adjNode(WEST, 2);

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
		SDL_Delay(1000 / drawSpeed);
		//std::cout << "\ncurrentEdge: " << A->toString() << " -> " << B->toString();

		if (mazeEdges.getEdge(A, B))
		{
			drawEdge(A, B, VALID);
		}

		else if (!DFS(A, B))
		{
			//LOG std::cout << "\n no path";
			mazeEdges.addEdge(currentEdge, 1);

			drawEdge(A, B, VALID);

			if ((B->equals(endNorth) || B->equals(endWest)) && !DFS(B, end))
			{
				mazeEdges.addEdge(B, end, 1);

				drawEdge(B, end, VALID);
			}

			for (int dir = NORTH; dir != END; dir++)
			{
				direction e_dir = (direction)dir;

				MazeNode* newNode = B->adjNode(e_dir, 2);
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

bool MedPrimMaze::compare(MazeNode * currentNode, MazeNode * search)
{
	return currentNode->equals(search);
}