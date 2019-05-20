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


	setCellType({1, 1}, SPECIAL);
	setCellType({ X_NODES - 2, Y_NODES - 2 }, SPECIAL);

}

void RecDivMaze::splitContainer(nodeContainer currentNodes)
{
	int numX = currentNodes.xLimit - currentNodes.xStart + 1;
	int numY = currentNodes.yLimit - currentNodes.yStart + 1;

	if (numX <= 1 || numY <= 1)
	{
		return;
	}
	else if (numX == 2 && numY == 2)
	{
		drawDelay();
		srand(time(NULL));

		int r;
		NodeCoord choice;
		bool valid = true;
		do
		{
			r = rand() % 4;
			switch (r)
			{
				case 0:
					choice = {currentNodes.xStart,currentNodes.yStart};
					valid = (getCellType(getAdjNode(choice,NORTH)) == UNVISITED || getCellType(getAdjNode(choice, WEST)) == UNVISITED);
					break;
				case 1:
					choice = { currentNodes.xLimit,currentNodes.yStart };
					valid = (getCellType(getAdjNode(choice, NORTH)) == UNVISITED || getCellType(getAdjNode(choice, EAST)) == UNVISITED);
					break;
				case 2:
					choice = { currentNodes.xStart,currentNodes.yLimit };
					valid = (getCellType(getAdjNode(choice, SOUTH)) == UNVISITED || getCellType(getAdjNode(choice, WEST)) == UNVISITED);
					break;
				default:
					choice = { currentNodes.xLimit,currentNodes.yLimit };
					valid = (getCellType(getAdjNode(choice, SOUTH)) == UNVISITED || getCellType(getAdjNode(choice, EAST)) == UNVISITED);
					break;
			}
		} while (valid);

		setCellType(choice, WALL);
	}
	else
	{
		srand((unsigned)time(0));

		//Vertical or horizontal wall

		//choice is the index of the wall
		drawDelay();

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
			choice = currentNodes.yStart + (rand() % (numY - 2)) + 1; //-2 to ensure 2 containers
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
				choice = currentNodes.yStart + (rand() % (numY - 2)) + 1; //-2 to ensure 2 containers
				drawHWall(currentNodes.xStart, currentNodes.xLimit, choice);
				splitContainer({ currentNodes.xStart, currentNodes.yStart, currentNodes.xLimit, choice - 1 });
				splitContainer({ currentNodes.xStart, choice + 1, currentNodes.xLimit, currentNodes.yLimit });
			}
		}
	}
}

void RecDivMaze::drawHWall(int x1, int x2, int y)
{
	int randMax = (1 + (x2 - x1));

	int door;
	
	do
	{
		door = rand() % randMax;
	} 
	while ((door != 0 && getCellType({ x1 - 1,y }) != WALL) || (x1 + door != x2 && getCellType({ x2 + 1,y }) != WALL));

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
	int randMax = (1 + (y2 - y1));

	int door;

	do
	{
		door = rand() % randMax;
	} while ((door != 0 && getCellType({ x, y1 - 1, }) != WALL) || ((y1 + door != y2 && getCellType({ x, y2 + 1 }) != WALL)));

	for (int i = y1; i <= y2; i++)
	{
		if (i != y1 + door)
		{
			setCellType(x,i, WALL);
		}
	}
}
