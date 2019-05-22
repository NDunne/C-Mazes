#include "RecDivMaze.h"

//1 - 3 - 3 - 1 deadlock still

RecDivMaze::RecDivMaze(SDL_Window* w) : Maze(w)
{
	color = blue;
	colorDif = redSingle;
	generate();
}

void RecDivMaze::drawContainer(nodeContainer bounds)
{
	nextColor();
	for (int i = bounds.xStart; i <= bounds.xLimit; i++)
	{
		for (int j = bounds.yStart; j <= bounds.yLimit; j++)
		{
			drawCell(i, j, color, false);
		}
	}

	SDL_UpdateWindowSurface(window);
}

void RecDivMaze::drawBase()
{
	for (int i = 0; i < X_NODES; i++)
	{
		for (int j = 0; j < Y_NODES; j++)
		{
			if (i == 0 || j == 0 || i == (X_NODES - 1) || j == (Y_NODES - 1))
			{
				setCellType(i, j, WALL, false);
			}
			else
			{
				setCellType(i, j, UNVISITED, false);
			}
		}
	}

	//Update the surface
	SDL_UpdateWindowSurface(window);
}

void RecDivMaze::generate()
{
	drawBase();
	
	splitContainer({ 1, 1, X_NODES-2, Y_NODES-2 }); //Coordinates are inclusive

}

//a 1 3 3 1 structure is a special case
bool RecDivMaze::isTripleCorridor(nodeContainer currentNodes, int numX, int numY)
{
	//vertical
	if (numX == 2 && numY == 3)
	{
		return ((getCellType({ currentNodes.xStart - 1,currentNodes.yStart + 1}).type == UNVISITED) && (getCellType({ currentNodes.xLimit + 1, currentNodes.yLimit - 1 }).type == UNVISITED));
	}
	else if (numX == 3 && numY == 2)
	{
		return ((getCellType({ currentNodes.xStart + 1, currentNodes.yStart - 1 }).type == UNVISITED) && (getCellType({ currentNodes.xLimit - 1, currentNodes.yLimit + 1 }).type == UNVISITED));
	}
	return false;
}

void RecDivMaze::splitContainer(nodeContainer currentNodes)
{
	drawContainer(currentNodes);
	NodeCoord start = { 1, 1 };
	NodeCoord end = { X_NODES - 2, Y_NODES - 2 };

	int numX = currentNodes.xLimit - currentNodes.xStart + 1;
	int numY = currentNodes.yLimit - currentNodes.yStart + 1;

	if (numX <= 1 || numY <= 1) //No more walls required if one of the dimensions is 1W
	{
		return;
	}
	else if ((numX == 2 && numY == 2) || isTripleCorridor(currentNodes, numX, numY)) 
	{
		//A square, or a 2x3 where a wall cannot go in the middle pair
		int h = (numX == 3 && numY == 2);
		int v = (numX == 2 && numY == 3);

		drawDelay();
		srand((unsigned) time(NULL));

		int	r = rand() % 4;
		NodeCoord choice;
		nodeContainer remaining;
		bool invalid = true;
		do
		{
			switch (r)
			{
				case 0:
					choice = {currentNodes.xStart,currentNodes.yStart};
					invalid = (getCellType(getAdjNode(choice,NORTH)).type == UNVISITED || getCellType(getAdjNode(choice, WEST)).type == UNVISITED);
					remaining = { currentNodes.xStart + h,currentNodes.yStart + v,currentNodes.xLimit,currentNodes.yLimit };
					break;
				case 1:
					choice = { currentNodes.xLimit,currentNodes.yStart };
					invalid = (getCellType(getAdjNode(choice, NORTH)).type == UNVISITED || getCellType(getAdjNode(choice, EAST)).type == UNVISITED);
					remaining = { currentNodes.xStart,currentNodes.yStart + v,currentNodes.xLimit - h,currentNodes.yLimit };
					break;
				case 2:
					choice = { currentNodes.xStart,currentNodes.yLimit };
					invalid = (getCellType(getAdjNode(choice, SOUTH)).type == UNVISITED || getCellType(getAdjNode(choice, WEST)).type == UNVISITED);
					remaining = { currentNodes.xStart + h,currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit - v };
					break;
				default:
					choice = { currentNodes.xLimit,currentNodes.yLimit };
					invalid = (getCellType(getAdjNode(choice, SOUTH)).type == UNVISITED || getCellType(getAdjNode(choice, EAST)).type == UNVISITED);
					remaining = { currentNodes.xStart,currentNodes.yStart,currentNodes.xLimit - h,currentNodes.yLimit - v };
					break;
			}
			r = rand() % 4;
		} while (invalid || ((choice == start) || (choice == end)));

		setCellType(choice, VALID);
		drawDelay();
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

		if (numY < numX) //If Horizontal containter add a vertical wall
		{
			do
			{
				choice = currentNodes.xStart + (rand() % (numX - 2)) + 1; //-2 to ensure 2 containers
				drawn = addVWall(choice, currentNodes.yStart, currentNodes.yLimit);
			} 
			while (!drawn);
			splitContainer({ currentNodes.xStart,currentNodes.yStart,choice - 1,currentNodes.yLimit });
			splitContainer({ choice + 1, currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit });
		}
		else if (numX < numY) //If Vertical container add a horizontal wall
		{
			do
			{
				choice = currentNodes.yStart + (rand() % (numY - 2)) + 1; //-2 to ensure 2 containers
				drawn = addHWall(currentNodes.xStart, currentNodes.xLimit, choice);
			} 
			while (!drawn);
			splitContainer({ currentNodes.xStart, currentNodes.yStart, currentNodes.xLimit, choice - 1 });
			splitContainer({ currentNodes.xStart, choice + 1, currentNodes.xLimit, currentNodes.yLimit });
		}
		else //otherwise flip a coin to decide 
		{
			do
			{
				choice = rand() % 2;//((numX + numY) - 4);
				if (choice == 0)
				{
					choice = currentNodes.xStart + (rand() % (numX - 2)) + 1; //-2 to ensure 2 containers
					drawn = addVWall(choice, currentNodes.yStart, currentNodes.yLimit);
					if (!drawn) continue;
					splitContainer({ currentNodes.xStart,currentNodes.yStart,choice - 1,currentNodes.yLimit });
					splitContainer({ choice + 1, currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit });
				}
				else
				{
					choice = currentNodes.yStart + (rand() % (numY - 2)) + 1; //-2 to ensure 2 containers
					drawn = addHWall(currentNodes.xStart, currentNodes.xLimit, choice);
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
bool RecDivMaze::addHWall(int x1, int x2, int y)
{
	drawHWall(x1, x2, y, -1, SELECTED);
	int door;

	bool startEdgeIsDoor = getCellType({ x1 - 1,y }).type != WALL;
	bool endEdgeIsDoor = getCellType({ x2 + 1,y }).type != WALL;

	if (startEdgeIsDoor && endEdgeIsDoor)
	{
		drawHWall(x1,x2,y,-1,INVALID);
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

	drawHWall(x1, x2, y, door, VALID);
	return true;
}

void RecDivMaze::drawHWall(int x1, int x2, int y, int door, Uint32 type)
{
	for (int i = x1; i <= x2; i++)
	{
		if (i != x1 + door)
		{
			setCellType(i, y, type, false);
		}
		else
		{
			setCellType(i, y, UNVISITED, false);
		}
	}
	SDL_UpdateWindowSurface(window);
	drawDelay();

	if (type == VALID)
	{
		for (int i = x1; i <= x2; i++)
		{
			if (i != x1 + door)
			{
				setCellType(i, y, WALL, false);
			}
			else
			{
				setCellType(i, y, UNVISITED, false);
				drawCell(i, y, color, false);
			}
		}
		SDL_UpdateWindowSurface(window);
		drawDelay();
	}
	else if (type == INVALID)
	{
		for (int i = x1; i <= x2; i++)
		{
			setCellType(i, y, UNVISITED, false);
		}
		SDL_UpdateWindowSurface(window);
		drawDelay();
	}
}

bool RecDivMaze::addVWall(int x, int y1, int y2)
{
	drawVWall(x, y1, y2, -1, SELECTED);
	int door;

	bool startEdgeIsDoor = getCellType({ x,y1 - 1 }).type != WALL;
	bool endEdgeIsDoor = getCellType({ x,y2 + 1 }).type != WALL;

	if (startEdgeIsDoor && endEdgeIsDoor)
	{
		drawVWall(x, y1, y2, -1, INVALID);
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
	drawVWall(x, y1, y2, door, VALID);
	return true;
}

void RecDivMaze::drawVWall(int x, int y1, int y2, int door, Uint32 type)
{
	for (int i = y1; i <= y2; i++)
	{
		if (i != y1 + door)
		{
			setCellType(x, i, type, false);
		}
		else
		{
			setCellType(x, i, UNVISITED, false);
		}
	}
	SDL_UpdateWindowSurface(window);
	drawDelay();
	
	if (type == VALID)
	{
		for (int i = y1; i <= y2; i++)
		{
			if (i != y1 + door)
			{
				setCellType(x, i, WALL, false);
			}
			else
			{
				setCellType(x, i,UNVISITED, false);
			}
		}
		SDL_UpdateWindowSurface(window);
		drawDelay();
	}
	else if (type == INVALID)
	{
		for (int i = y1; i <= y2; i++)
		{
			setCellType(x, i, UNVISITED, false);
		}
		SDL_UpdateWindowSurface(window);
		drawDelay();
	}
}
