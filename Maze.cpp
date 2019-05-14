#include "Maze.h"
#include <iostream>

Maze::Maze(SDL_Window* w, SDL_Surface* s)
{
	window = w;
	surface = s;

	black = SDL_MapRGB(surface->format, 0x0, 0x0, 0x0);
	grey = SDL_MapRGB(surface->format, 0x30, 0x30, 0x30);
	white = SDL_MapRGB(surface->format, 0xF0, 0xF0, 0xF0);

	Prims();

	//add edge to all adjacent cells

	/*for (int x = 0; x < X_CELLS; x++)
	{
		for (int y = 0; y < Y_CELLS; y++)
		{
			if (!(x == 0 || y == 0 || x == (X_CELLS-1) || y == (Y_CELLS-1)))
			{
				if (x > 1)
				{
					allEdges.addEdge(x - 1, y, x, y, 1);
				}
				if (y > 1)
				{
					allEdges.addEdge(x, y - 1, x, y, 1);
				}
			}
		}
	}*/
}

bool Maze::isValid(NodeCoord n)
{
	return (n.first > 0 && n.first < (X_CELLS - 1) && n.second > 0 && n.second < (Y_CELLS - 1));
}

void Maze::Prims()
{

	draw();
	NodeCoord start = { 1, 1 };

	std::vector<NodePair> edges;

	srand((unsigned)time(0));

	if (rand() % 2)
	{
		edges.push_back({ start, {start.first, start.second + 1} });
	}
	else
	{
		edges.push_back({ start, {start.first+1, start.second} });
	}
	
	while (!edges.empty())
	{
		int currentIndex = rand() % edges.size();
		NodePair current = edges[currentIndex];
		
		edges.erase(edges.begin() + currentIndex);

		if (!mazeEdges.DFS(current.first, current.second))
		{
			mazeEdges.addEdge(current, 1);

			NodeCoord B = current.second;

			drawCell(B.first - 1, B.second - 1, UNVISITED);

			for (int i = -1; i <= 1; i += 2)
			{
				NodeCoord newNode = {current.second.first+i, current.second.second};
				if (isValid(newNode)) edges.push_back({ current.second,newNode });

				newNode = { current.second.first, current.second.second+i };
				if (isValid(newNode)) edges.push_back({ current.second,newNode });
			}
		}
	}
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
	default:
		colour = black;
		break;
	}
	SDL_FillRect(surface, &rect, colour);


	SDL_UpdateWindowSurface(window);
}

void Maze::draw()
{	
	for (int i = 0; i < X_CELLS; i++)
	{
		for (int j = 0; j < Y_CELLS; j++)
		{
			drawCell(i, j, WALL);
		}
	}

	/*for (auto it1 = mazeEdges.getStart(); it1 != mazeEdges.getEnd(); ++it1)
	{
		NodeCoord A = it1->first;
		NodeAdj a_adj = it1->second;

		for (auto it2 = a_adj.begin(); it2 != a_adj.end(); ++it2)
		{
			NodeCoord B = it2->first;

			if (A.first == B.first)
			{
				for (int m = A.second; m <= B.second; m++)
				{
					drawCell(A.first, m, UNVISITED);
					SDL_UpdateWindowSurface(window);
					SDL_Delay(50);
				}
			}
			else
			{
				for (int m = A.first; m <= B.first; m++)
				{
					drawCell(m, A.second, UNVISITED);
					SDL_UpdateWindowSurface(window);
					SDL_Delay(50);
				}
			}
		}
	}
	*/

	//Update the surface
	SDL_UpdateWindowSurface(window);
}
