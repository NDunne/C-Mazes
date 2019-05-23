#include "RecDivMaze.h"

//1 - 3 - 3 - 1 deadlock still

//newRecDiv

RecDivMaze::RecDivMaze(SDL_Window* w, DrawPosition dp) : Maze(w, dp)
{
	//color = blue;
	//colorDif = redSingle;
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
	
	srand((unsigned)time(NULL));

	splitContainer({ 1, 1, X_NODES-2, Y_NODES-2 }); //Coordinates are inclusive

	finish();
}

void RecDivMaze::splitContainer(nodeContainer currentNodes)
{
	drawContainer(currentNodes);

	int numX = currentNodes.xLimit - currentNodes.xStart + 1;
	int numY = currentNodes.yLimit - currentNodes.yStart + 1;

	int xNodes = (numX / 2);
	int yNodes = (numY / 2);

	if (numX <= 1 || numY <= 1) //No more walls required if one of the dimensions is 1W
	{
		return;
	}
	else
	{
		//Vertical or horizontal wall

		//choice is the index of the wall
		drawDelay();

		bool drawn = false;
		int choice;

		if (numY < numX) //If Horizontal containter add a vertical wall
		{
			do
			{
				choice = currentNodes.xStart + 1 +(2 * (rand() % (numX/2))); 
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
				choice = currentNodes.yStart + 1 + (2 * (rand() % (numY / 2)));
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
					choice = currentNodes.xStart + 1 + (2 * (rand() % (numY / 2)));
					drawn = addVWall(choice, currentNodes.yStart, currentNodes.yLimit);
					if (!drawn) continue;
					splitContainer({ currentNodes.xStart,currentNodes.yStart,choice - 1,currentNodes.yLimit });
					splitContainer({ choice + 1, currentNodes.yStart,currentNodes.xLimit,currentNodes.yLimit });
				}
				else
				{
					choice = currentNodes.yStart + 1 + (2 * (rand() % (numY / 2)));
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
		int randMax = (1 + (x2 - x1)/2);

		door = 2 * (rand() % randMax);
	}

	drawHWall(x1, x2, y, door, VALID);
	return true;
}

void RecDivMaze::drawHWall(int x1, int x2, int y, int door, cellType type)
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
			drawCell(i, y, color, false);
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
		int randMax = (1 + (y2 - y1) / 2);

		door = 2 * (rand() % randMax);
	}
	drawVWall(x, y1, y2, door, VALID);
	return true;
}

void RecDivMaze::drawVWall(int x, int y1, int y2, int door, cellType type)
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
			drawCell(x, i, color, false);
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
				drawCell(x, i, color, false);
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
