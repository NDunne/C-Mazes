#include "EasyKruskalMaze.h"

EasyKruskalMaze::EasyKruskalMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

std::vector<NodePair> EasyKruskalMaze::allEdges()
{
	std::vector<NodePair> edges;

	for (int i = 1; i < MazeGraph::X_NODES - 1; i += 2)
	{
		for (int j = 1; j < MazeGraph::Y_NODES - 1; j += 2)
		{
			//SDL_Delay(500);
			NodeCoord current = { i, j };
			NodeCoord currSouth = MazeGraph::getAdjNode(current, SOUTH, 2);
			NodeCoord currEast = MazeGraph::getAdjNode(current, EAST, 2);

			if (currSouth != nullNode)
			{
				edges.push_back({ current, currSouth });
			}

			if (currEast != nullNode)
			{
				edges.push_back({ current, currEast });
			}
		}
	}

	return edges;
}

void EasyKruskalMaze::generate()
{
	drawBase();
	NodeCoord start = { 1, 1 };
	NodeCoord end = { MazeGraph::X_NODES - 2, MazeGraph::Y_NODES - 2 };

	std::vector<NodePair> edges = allEdges();

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	auto rng = std::default_random_engine(seed);
	std::shuffle(std::begin(edges), std::end(edges), rng);

	int numEdges = edges.size();

	for (int i = 0; i < numEdges; i++)
	{
		NodePair currentEdge = edges[i];

		if (!DFS(currentEdge.first, currentEdge.second))
		{
			mazeEdges.addEdge(currentEdge, 1);
			SDL_Delay(1000 / drawSpeed);
			drawEdge(currentEdge, VALID);
			std::cout << "";
		}
		else
		{
			SDL_Delay(1000 / drawSpeed);
			drawEdge(currentEdge, INVALID);
			std::cout << "";
		}
	}
}

/*
bool EasyKruskalMaze::compare(NodeCoord currentNode, NodeCoord search)
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
}*/

void EasyKruskalMaze::drawEdge(NodeCoord A, NodeCoord B, edgeType e)
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
		drawCell(B, UNVISITED);
		break;
	default:
		return;
	}
}