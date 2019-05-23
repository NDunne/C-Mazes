#include "KruskalMaze.h"
KruskalMaze::KruskalMaze(SDL_Window* w) :MSTMaze(w)
{
	color = green;
	colorDif = blueSingle;
	generate();

	finish();
}

std::vector<NodePair> KruskalMaze::allEdges()
{
	std::vector<NodePair> edges;

	for (int i = 1; i < X_NODES - 1; i += 2)
	{
		for (int j = 1; j < Y_NODES - 1; j += 2)
		{
			NodeCoord current = { i, j };
			NodeCoord currSouth = Maze::getAdjNode(current, SOUTH, 2);
			NodeCoord currEast = Maze::getAdjNode(current, EAST, 2);

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
	NodeCoord end = { X_NODES - 2, Y_NODES - 2 };

	std::vector<NodePair> edges = allEdges();

	unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();

	auto rng = std::default_random_engine(seed);
	std::shuffle(std::begin(edges), std::end(edges), rng);

	int numEdges = edges.size();

	for (int i = 0; i < numEdges; i++)
	{
		NodePair currentEdge = edges[i];
		drawEdge(currentEdge.first, currentEdge.second, SELECTED);
	
		if (!DFS(currentEdge.first, currentEdge.second))
		{
			addEdge(currentEdge);
		}
		else
		{
			drawEdge(currentEdge, INVALID);
		}
	}

	//setCellType(start, SPECIAL);
	//setCellType(end, SPECIAL);
}