#include "HardPrimMaze.h"

HardPrimMaze::HardPrimMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

void HardPrimMaze::drawEdge(NodeCoord A, NodeCoord B, edgeType e)
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
	NodeCoord start = { 1, 1 };
	NodeCoord end = { MazeGraph::X_NODES - 2, MazeGraph::Y_NODES - 2 };

	NodeCoord endNorth = MazeGraph::getAdjNode(end, NORTH);
	NodeCoord endWest = MazeGraph::getAdjNode(end, WEST);

	std::vector<NodePair> edges;

	srand((unsigned)time(0));

	if (rand() % 2)
	{
		edges.push_back({ start, MazeGraph::getAdjNode(start, EAST) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(EAST)->toString();
	}
	else
	{
		edges.push_back({ start, MazeGraph::getAdjNode(start, SOUTH) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(SOUTH)->toString();
	}
	
	while (!edges.empty())
	{
		int currentIndex = rand() % edges.size();
		NodePair currentEdge = edges[currentIndex];

		NodeCoord A = currentEdge.first;
		NodeCoord B = currentEdge.second;

		drawEdge(A, B, CANDIDATE);

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

			if ((B == endNorth || B == endWest) && !DFS(B, end))
			{
				mazeEdges.addEdge(B, end, 1);
				drawEdge(B, end, VALID);
			}

			drawCell(B, UNVISITED);

			for (int dir = NORTH; dir != END; dir++)
			{
				direction e_dir = (direction)dir;

				NodeCoord newNode = MazeGraph::getAdjNode(B, e_dir);
				if (newNode != nullNode && !mazeEdges.getEdge(B,newNode))
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

	//delete start;
	//delete end;

	//delete endNorth;
	//delete endWest;
}

bool HardPrimMaze::compare(NodeCoord currentNode, NodeCoord search)
{
	NodeCoord adj1;
	NodeCoord adj2;

	//Efficiency - checking cross requires that x or y is the same
	if (search.first == currentNode.first)
	{
		adj1 = MazeGraph::getAdjNode(search, NORTH);
		adj2 = MazeGraph::getAdjNode(search, SOUTH);
		if ((adj1 != nullNode && adj1 == currentNode) || (adj2 != nullNode && adj2 == currentNode))
		{
			return true;
		}
	}
	else if (search.second == currentNode.second)
	{
		adj1 = MazeGraph::getAdjNode(search, EAST);
		adj2 = MazeGraph::getAdjNode(search, WEST);
		if ((adj1 != nullNode && adj1 == currentNode) || (adj2 != nullNode && adj2 == currentNode))
		{
			return true;
		}
	}

	return false;
}