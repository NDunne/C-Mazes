#include "PrimMaze.h"

PrimMaze::PrimMaze(SDL_Window* w, DrawPosition dp) : MSTMaze(w, dp)
{
	color = red;
	colorDif = greenSingle;
	generate();

	finish();
}

void PrimMaze::generate()
{
	drawBase();
	NodeCoord start = { 1, 1 };
	NodeCoord end = { X_NODES - 2, Y_NODES - 2 };

	NodeCoord endNorth = Maze::getAdjNode(end, NORTH, 2);
	NodeCoord endWest = Maze::getAdjNode(end, WEST, 2);

	std::vector<NodePair> edges;

	srand((unsigned)time(0));

	if (rand() % 2)
	{
		edges.push_back({ start, Maze::getAdjNode(start, EAST,2) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(EAST)->toString();
	}
	else
	{
		edges.push_back({ start, Maze::getAdjNode(start, SOUTH,2) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(SOUTH)->toString();
	}

	while (!edges.empty())
	{
		int currentIndex = rand() % edges.size();
		NodePair currentEdge = edges[currentIndex];

		NodeCoord A = currentEdge.first;
		NodeCoord B = currentEdge.second;

		drawEdge(A, B, SELECTED);
		if (mazeEdges.getEdge(A, B))
		{
			drawEdge(A, B, VALID);
		}
		else if (!DFS(A, B))
		{
			//LOG std::cout << "\n no path";
			addEdge(currentEdge);

			if ((B ==endNorth || B == endWest) && !DFS(B, end))
			{
				addEdge(B, end);
			}

			for (int dir = NORTH; dir != END; dir++)
			{
				direction e_dir = (direction)dir;

				NodeCoord newNode = Maze::getAdjNode(B, e_dir, 2);
				if (newNode != nullNode && !mazeEdges.getEdge(B, newNode))
				{
					edges.push_back({ B, newNode });
				}
			}
		}
		else
		{
			drawEdge(A, B, INVALID);
		}

		edges.erase(edges.begin() + currentIndex);
	}

	//setCellType(start, SPECIAL);
	//setCellType(end, SPECIAL);
}