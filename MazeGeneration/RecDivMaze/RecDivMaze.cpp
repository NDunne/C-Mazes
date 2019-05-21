#include "RecDivMaze.h"

//1 - 3 - 3 - 1 deadlock still

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
	else if ((numX == 2 && numY == 2) || (numX == 2 && numY == 3) || (numX == 3 && numY == 2))
	{
		int h = (numX == 3 && numY == 2);
		int v = (numX == 2 && numY == 3);

		drawDelay();
		srand(time(NULL));

		int	r = rand() % 4;
		NodeCoord choice;
		nodeContainer remaining;
		bool valid = true;
		do
		{
			switch (r)
			{
				case 0:
					choice = {currentNodes.xStart,currentNodes.yStart};
					valid = (getCellType(getAdjNode(choice,NORTH)) == UNVISITED || getCellType(getAdjNode(choice, WEST)) == UNVISITED);
					remaining = { currentNodes.xStart + h,currentNodes.yStart + v,currentNodes.xLimit,currentNodes.yLimit };
					break;
				case 1:
					choice = { currentNodes.xLimit,currentNodes.yStart };
					valid = (getCellType(getAdjNode(choice, NORTH)) == UNVISITED || getCellType(getAdjNode(choice, EAST)) == UNVISITED);
					remaining = { currentNodes.xStart,currentNodes.yStart + v,currentNodes.xLimit - h,currentNodes.yLimit };
					break;
				case 2:
					choice = { currentNodes.xStart,currentNodes.yLimit };
					valid = (getCellType(getAdjNode(choice, SOUTH)) == UNVISITED || getCellType(getAdjNode(choice, WEST)) == UNVISITED);
					remaining = { currentNodes.xStart + h,currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit - v };
					break;
				default:
					choice = { currentNodes.xLimit,currentNodes.yLimit };
					valid = (getCellType(getAdjNode(choice, SOUTH)) == UNVISITED || getCellType(getAdjNode(choice, EAST)) == UNVISITED);
					remaining = { currentNodes.xStart,currentNodes.yStart,currentNodes.xLimit - h,currentNodes.yLimit - v };
					break;
			}

			r = (r + 1) % 4;
		} while (valid);

		setCellType(choice, WALL);
		if (v + h) splitContainer(remaining);
	}
	else
	{
		srand((unsigned)time(0));

		//Vertical or horizontal wall

		//choice is the index of the wall
		drawDelay();

		bool drawn = false;
		int choice;

		if (numY < numX)
		{
			do
			{
				choice = currentNodes.xStart + (rand() % (numX - 2)) + 1; //-2 to ensure 2 containers
				drawn = drawVWall(choice, currentNodes.yStart, currentNodes.yLimit);
			} 
			while (!drawn);
			splitContainer({ currentNodes.xStart,currentNodes.yStart,choice - 1,currentNodes.yLimit });
			splitContainer({ choice + 1, currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit });
		}
		else if (numX < numY)
		{
			do
			{
				choice = currentNodes.yStart + (rand() % (numY - 2)) + 1; //-2 to ensure 2 containers
				drawn = drawHWall(currentNodes.xStart, currentNodes.xLimit, choice);
			} 
			while (!drawn);
			splitContainer({ currentNodes.xStart, currentNodes.yStart, currentNodes.xLimit, choice - 1 });
			splitContainer({ currentNodes.xStart, choice + 1, currentNodes.xLimit, currentNodes.yLimit });
		}
		else
		{
			do
			{
				choice = rand() % 2;//((numX + numY) - 4);
				if (choice == 0)
				{
					choice = currentNodes.xStart + (rand() % (numX - 2)) + 1; //-2 to ensure 2 containers
					drawn = drawVWall(choice, currentNodes.yStart, currentNodes.yLimit);
					if (!drawn) continue;
					splitContainer({ currentNodes.xStart,currentNodes.yStart,choice - 1,currentNodes.yLimit });
					splitContainer({ choice + 1, currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit });
				}
				else
				{
					choice = currentNodes.yStart + (rand() % (numY - 2)) + 1; //-2 to ensure 2 containers
					drawn = drawHWall(currentNodes.xStart, currentNodes.xLimit, choice);
					if (!drawn) continue;
					splitContainer({ currentNodes.xStart, currentNodes.yStart, currentNodes.xLimit, choice - 1 });
					splitContainer({ currentNodes.xStart, choice + 1, currentNodes.xLimit, currentNodes.yLimit });
				}
			} 
			while (!drawn);
		}
	}
}

//If door both sides of the selected wall we have impassable code.
bool RecDivMaze::drawHWall(int x1, int x2, int y)
{
	int door;

	bool startEdgeIsDoor = getCellType({ x1 - 1,y }) != WALL;
	bool endEdgeIsDoor = getCellType({ x2 + 1,y }) != WALL;

	if (startEdgeIsDoor && endEdgeIsDoor)
	{
		return false;
	}
	else if (startEdgeIsDoor)
	{
		door = 0;
	}
	else if (endEdgeIsDoor)
	{
		door = (x2 - x1);
	}
	else
	{
		int randMax = (1 + (x2 - x1));
		
		door = rand() % randMax;
	}

	for (int i = x1; i <= x2; i++)
	{
		if (i != x1 + door)
		{
			setCellType(i,y,WALL);
		}
	}

	return true;
}

bool RecDivMaze::drawVWall(int x, int y1, int y2)
{
	int door;

	bool startEdgeIsDoor = getCellType({ x,y1 -1 }) != WALL;
	bool endEdgeIsDoor = getCellType({ x,y2 + 1 }) != WALL;

	if (startEdgeIsDoor && endEdgeIsDoor)
	{
		return false;
	}
	else if (startEdgeIsDoor)
	{
		door = 0;
	}
	else if (endEdgeIsDoor)
	{
		door = (y2 - y1);
	}
	else
	{
		int randMax = (1 + (y2 - y1));

		door = rand() % randMax;
	}

	for (int i = y1; i <= y2; i++)
	{
		if (i != y1 + door)
		{
			setCellType(x, i, WALL);
		}
	}

	return true;
}
