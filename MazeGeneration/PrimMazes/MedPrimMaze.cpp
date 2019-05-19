#include "MedPrimMaze.h"

MedPrimMaze::MedPrimMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

void MedPrimMaze::drawEdge(NodeCoord A, NodeCoord B, edgeType e)
{
	NodeCoord midNode = { (A.first + B.first) / 2, (A.second + B.second) / 2 };

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

	//delete midNode;
}

void MedPrimMaze::generate()
{
	drawBase();
	NodeCoord start = { 1, 1 };
	NodeCoord end = { MazeGraph::X_NODES - 2, MazeGraph::Y_NODES - 2 };

	NodeCoord endNorth = MazeGraph::getAdjNode(end, NORTH, 2);
	NodeCoord endWest = MazeGraph::getAdjNode(end, WEST, 2);

	std::vector<NodePair> edges;

	srand((unsigned)time(0));

	if (rand() % 2)
	{
		edges.push_back({ start, MazeGraph::getAdjNode(start, EAST,2) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(EAST)->toString();
	}
	else
	{
		edges.push_back({ start, MazeGraph::getAdjNode(start, SOUTH,2) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(SOUTH)->toString();
	}

	while (!edges.empty())
	{
		int currentIndex = rand() % edges.size();
		NodePair currentEdge = edges[currentIndex];

		NodeCoord A = currentEdge.first;
		NodeCoord B = currentEdge.second;

		drawEdge(A, B, CANDIDATE);
		//std::cout << "\ncurrentEdge: " << A->toString() << " -> " << B->toString();

		if (mazeEdges.getEdge(A, B))
		{
			drawEdge(A, B, VALID);
		}

		else if (!DFS(A, B))
		{
			//LOG std::cout << "\n no path";
			mazeEdges.addEdge(currentEdge, 1);
			SDL_Delay(1000 / drawSpeed);
			drawEdge(A, B, VALID);

			if ((B ==endNorth || B == endWest) && !DFS(B, end))
			{
				mazeEdges.addEdge(B, end, 1);

				drawEdge(B, end, VALID);
			}

			for (int dir = NORTH; dir != END; dir++)
			{
				direction e_dir = (direction)dir;

				NodeCoord newNode = MazeGraph::getAdjNode(B, e_dir, 2);
				if (newNode != nullNode && !mazeEdges.getEdge(B, newNode))
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