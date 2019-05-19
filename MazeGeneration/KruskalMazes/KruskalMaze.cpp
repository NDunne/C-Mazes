#include "KruskalMaze.h"
KruskalMaze::KruskalMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

std::vector<NodePair> KruskalMaze::allEdges()
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

void KruskalMaze::generate()
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

	drawCell(start, SPECIAL);
	drawCell(end, SPECIAL);
}

void KruskalMaze::drawEdge(NodeCoord A, NodeCoord B, edgeType e)
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