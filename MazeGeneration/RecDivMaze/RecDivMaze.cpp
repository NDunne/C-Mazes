#include "RecDivMaze.h"

RecDivMaze::RecDivMaze(SDL_Window* w) : Maze(w)
{
	generate();
}

void RecDivMaze::drawBase()
{
	for (int i = 0; i < X_NODES; i++)
	{
		for (int j = 0; j < Y_NODES; j++)
		{
			if (i == 0 || j == 0 || i == (X_NODES - 1) || j == (Y_NODES - 1))
			{
				setCellType(i, j, WALL);
			}
			else
			{
				setCellType(i, j, UNVISITED);
			}
		}
	}
}

void RecDivMaze::generate()
{
	drawBase();
	
	splitContainer({ 1, 1, X_NODES-1, Y_NODES-1 });

}

void RecDivMaze::splitContainer(nodeContainer currentNodes)
{
	int numX = currentNodes.xLimit - currentNodes.xStart + 1;
	int numY = currentNodes.yLimit - currentNodes.yStart + 1;

	std::cout << "splitContainer";
	if (currentNodes.xStart == currentNodes.xLimit && currentNodes.yStart == currentNodes.yLimit)
	{
		return;
	}
	else
	{
		srand((unsigned)time(0));

		//Vertical or horizontal wall

		int options = numX + numY;

		int choice = rand() % options;

		if (choice < numX)
		{
			drawVWall(currentNodes.xStart + choice, currentNodes.yStart, currentNodes.yLimit);
			splitContainer({currentNodes.xStart,currentNodes.yStart,currentNodes.xStart + choice - 1,currentNodes.yLimit });
			splitContainer({currentNodes.xStart + choice + 1, currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit });
		}
		else
		{
			drawHWall(currentNodes.xStart, currentNodes.xLimit, currentNodes.yStart + (choice - numX));
			splitContainer({ currentNodes.xStart, currentNodes.yStart, currentNodes.xLimit, currentNodes.yStart + (choice - numX) - 1 });
			splitContainer({currentNodes.xStart, currentNodes.yStart + (choice - numX) - 1, currentNodes.xLimit, currentNodes.yLimit});
		}

		SDL_Delay(500);
	}
}

void RecDivMaze::drawHWall(int x1, int x2, int y)
{
	int door = rand() % (1 + (x2 - x1));

	for (int i = x1; i <= x2; i++)
	{
		if (i != door)
		{
			setCellType(i,y,WALL);
		}
	}
}

void RecDivMaze::drawVWall(int x, int y1, int y2)
{
	int door = rand() % (1 + (y2 - y1));

	for (int i = y1; i <= y2; i++)
	{
		if (i != door)
		{
			setCellType(x,i, WALL);
		}
	}
}
