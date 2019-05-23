#include "AldousBroderMaze.h"

AldousBroderMaze::AldousBroderMaze(SDL_Window* w, DrawPosition dp) : MSTMaze(w, dp)
{
	color = blue;
	colorDif = redSingle;

	srand((unsigned)time(NULL));

	generate();

	finish();
}

bool AldousBroderMaze::isNullNode(const NodeCoord n)
{
	return (n == nullNode);
}

NodeCoord AldousBroderMaze::randomNeighbor(NodeCoord n, NodeCoord origin)
{
	std::vector<NodeCoord> neighbors = { getAdjNode(n,NORTH,2), getAdjNode(n,EAST,2), getAdjNode(n,SOUTH,2), getAdjNode(n,WEST,2) };

	neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), nullNode), neighbors.end());
	neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), origin), neighbors.end());

	return neighbors.at(rand() % neighbors.size());
}

void AldousBroderMaze::generate()
{
	drawBase();

	NodeCoord current, next, last;
	
	last = nullNode;
	int visited = 1;
	int nodes = ((X_NODES - 1) / 2) * ((Y_NODES - 1) / 2);
	//15x15 grid   - WALL
	//             - (WALL-NODE) x 7 + WALL 
	//             - x 7
	//             - WALL

	current = { 1 + 2 * (rand() % ((X_NODES - 1) / 2)), 1 + 2 * (rand() % ((Y_NODES - 1) / 2)) };

	do
	{
		next = randomNeighbor(current, last);
		cellType nextType = getCellType(next).type;

		drawEdge({ current, next }, SELECTED);

		if (mazeEdges.getEdge(current, next))
		{
			drawEdge(current, next, VALID);
		}
		else if (nextType == WALL)
		{
			addEdge(current, next);
			visited++;
		}
		else
		{
			drawEdge({ current, next }, INVALID);
		}

		last = current;
		current = next;
	} 
	while (visited < nodes);
}