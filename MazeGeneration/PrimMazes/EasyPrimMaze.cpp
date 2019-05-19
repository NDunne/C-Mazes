#include "EasyPrimMaze.h"

EasyPrimMaze::EasyPrimMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

void EasyPrimMaze::generate()
{
	drawBase();
	NodeCoord start = { 1, 1 };
	NodeCoord end = { MazeGraph::X_NODES - 2, MazeGraph::Y_NODES - 2 };

	NodeCoord endNorth = MazeGraph::getAdjNode(end,NORTH,2);
	NodeCoord endWest = MazeGraph::getAdjNode(end,WEST,2);

	std::vector<NodePair> edges;

	srand((unsigned)time(0));

	if (rand() % 2)
	{
		edges.push_back({ start, MazeGraph::getAdjNode(start,EAST,2) });
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

		drawEdge(A, B, SELECTED);
		SDL_Delay(1000/drawSpeed);
		//std::cout << "\ncurrentEdge: " << A->toString() << " -> " << B->toString();

		if (mazeEdges.getEdge(A, B))
		{
			drawEdge(A, B, VALID);
		}

		else if (!DFS(A,B))
		{
			//LOG std::cout << "\n no path";
			mazeEdges.addEdge(currentEdge, 1);
			SDL_Delay(1000 / drawSpeed);
			drawEdge(A, B, VALID);

			if ((B == endNorth || B == endWest) && !DFS(B,end))
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

bool EasyPrimMaze::compare(NodeCoord currentNode, NodeCoord search)
{
	NodeCoord adj1;
	NodeCoord adj2;

	//Efficiency - checking cross requires that x or y is the same
	if (search.first == currentNode.first)
	{
		adj1 = MazeGraph::getAdjNode(search, NORTH, 2);
		adj2 = MazeGraph::getAdjNode(search, SOUTH, 2);
		if ((adj1 != nullNode && adj1 == currentNode) || (adj2 != nullNode && adj2 == currentNode))
		{
			return true;
		}
	}
	else if (search.second == currentNode.second)
	{
		adj1 = MazeGraph::getAdjNode(search, EAST, 2);
		adj2 = MazeGraph::getAdjNode(search, WEST, 2);
		if ((adj1 != nullNode && adj1 == currentNode) || (adj2 != nullNode && adj2 == currentNode))
		{
			return true;
		}
	}

	return false;
}

void EasyPrimMaze::drawEdge(NodeCoord A, NodeCoord B, edgeType e)
{
	NodeCoord midNode = { (A.first + B.first) / 2, (A.second + B.second) / 2 };

	switch (e)
	{
	case SELECTED:
		drawCell(A, blue);
		drawCell(midNode, blue);
		drawCell(B, blue);
		break;
	case CANDIDATE:
		drawCell(A, cyan);
		drawCell(midNode, cyan);
		drawCell(B, cyan);
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