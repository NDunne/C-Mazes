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
	
	splitContainer({ 1, 1, X_NODES-2, Y_NODES-2 }); //Coordinates are inclusive

}

void RecDivMaze::splitContainer(nodeContainer currentNodes)
{
	int numX = currentNodes.xLimit - currentNodes.xStart + 1;
	int numY = currentNodes.yLimit - currentNodes.yStart + 1;

	std::cout << "splitContainer";
	if (numX <= 2 || numY <= 2)
	{
		return;
	}
	else
	{
		srand((unsigned)time(0));

		//Vertical or horizontal wall

		//choice is the index of the wall
		int choice;
		if (numY < numX)
		{
			choice = currentNodes.xStart + (rand() % (numX - 2)) + 1; //-2 to ensure 2 containers
			drawVWall(choice, currentNodes.yStart, currentNodes.yLimit);
			splitContainer({currentNodes.xStart,currentNodes.yStart,choice-1,currentNodes.yLimit });
			splitContainer({choice+1, currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit });
		}
		else if (numX < numY)
		{
			choice = currentNodes.xStart + (rand() % (numY - 2)) + 1; //-2 to ensure 2 containers
			drawHWall(currentNodes.xStart, currentNodes.xLimit, choice);
			splitContainer({ currentNodes.xStart, currentNodes.yStart, currentNodes.xLimit, choice-1});
			splitContainer({currentNodes.xStart, choice+1, currentNodes.xLimit, currentNodes.yLimit});
		}
		else
		{
			choice = rand() % ((numX + numY) - 4);
			if (choice < numX)
			{
				choice = currentNodes.xStart + (rand() % (numX - 2)) + 1; //-2 to ensure 2 containers
				drawVWall(choice, currentNodes.yStart, currentNodes.yLimit);
				splitContainer({ currentNodes.xStart,currentNodes.yStart,choice - 1,currentNodes.yLimit });
				splitContainer({ choice + 1, currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit });
			}
			else
			{
				choice = currentNodes.xStart + (rand() % (numY - 2)) + 1; //-2 to ensure 2 containers
				drawHWall(currentNodes.xStart, currentNodes.xLimit, choice);
				splitContainer({ currentNodes.xStart, currentNodes.yStart, currentNodes.xLimit, choice - 1 });
				splitContainer({ currentNodes.xStart, choice + 1, currentNodes.xLimit, currentNodes.yLimit });
			}
		}
		SDL_Delay(500);
	}
}

void RecDivMaze::drawHWall(int x1, int x2, int y)
{
	int door = rand() % (1 + (x2 - x1));

	for (int i = x1; i <= x2; i++)
	{
		if (i != x1 + door)
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
		if (i != y1 + door)
		{
			setCellType(x,i, WALL);
		}
	}
}
