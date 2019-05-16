#include "PrimMaze.h"
#include <iostream>

Maze::Maze(SDL_Window* w, SDL_Surface* s)
{
	window = w;
	surface = s;

	black = SDL_MapRGB(surface->format, 0x0, 0x0, 0x0);
	grey = SDL_MapRGB(surface->format, 0x30, 0x30, 0x30);
	white = SDL_MapRGB(surface->format, 0xF0, 0xF0, 0xF0);
	green = SDL_MapRGB(surface->format, 0x0, 0xF0, 0x0);

	Prims();

}

void Maze::Prims()
{

	drawBase();
	MazeNode* start = new MazeNode(1, 1);
	MazeNode* end = new MazeNode(MazeNode::X_NODES - 2, MazeNode::Y_NODES - 2);

	MazeNode* endNorth = end->adjNode(NORTH);
	MazeNode* endWest = end->adjNode(WEST);

	drawCell(start, SPECIAL);
	drawCell(end, SPECIAL);

	std::vector<NodePair> edges;

	srand((unsigned)time(0));

	if (rand() % 2)
	{
		edges.push_back({ start, start->adjNode(EAST) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(EAST)->toString();
	}
	else
	{
		edges.push_back({ start, start->adjNode(SOUTH) });
		//LOG std::cout << "\nPushing edge: " << start->toString() << " -> " << start->adjNode(SOUTH)->toString();
	}
	
	while (!edges.empty())
	{
		int currentIndex = rand() % edges.size();
		NodePair currentEdge = edges[currentIndex];

		std::cout << "\ncurrentEdge: " << currentEdge.first->toString() << " -> " << currentEdge.second->toString();

		if (!mazeEdges.DFS(currentEdge.first, currentEdge.second, true))
		{
			//LOG std::cout << "\n no path";
			mazeEdges.addEdge(currentEdge, 1);

			MazeNode* B = currentEdge.second;

			if (B->equals(endNorth) || B->equals(endWest))
			{
				mazeEdges.addEdge(B, end, 1);
			}

			drawCell(B, UNVISITED);
			SDL_Delay(10);

			for (int dir = NORTH; dir != END; dir++)
			{
				direction e_dir = (direction)dir;

				MazeNode* newNode = B->adjNode(e_dir);
				if (newNode != nullptr && !mazeEdges.getEdge(B,newNode))
				{
					edges.push_back({ B, newNode });
					//LOG std::cout << "\n Maze edge queued: " << B->toString() << " -> " << newNode->toString();
				}
			}
		}

		edges.erase(edges.begin() + currentIndex);
	}
}

void Maze::drawCell(MazeNode* n, Maze::cellType type)
{
	Maze::drawCell(n->x, n->y, type);
}

void Maze::drawCell(int x, int y, Maze::cellType type)
{
	SDL_Rect rect = { boxPad + 4 + x * (boxLen + boxPad), boxPad + 4 + y * (boxLen + boxPad), boxLen, boxLen };
	
	Uint32 colour;

	switch (type)
	{
	case UNVISITED:
		colour = white;
		break;
	case VISITED:
		colour = grey;
		break;
	case WALL:
		colour = black;
		break;
	default:
		colour = green;
		break;
	}
	SDL_FillRect(surface, &rect, colour);


	SDL_UpdateWindowSurface(window);
}

void Maze::drawBase()
{	
	for (int i = 0; i < MazeNode::X_NODES; i++)
	{
		for (int j = 0; j < MazeNode::Y_NODES; j++)
		{
			drawCell(i, j, WALL);
		}
	}

	//Update the surface
	SDL_UpdateWindowSurface(window);
}
