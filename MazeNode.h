#pragma once
class MazeNode
{
public:
	enum NodeType { WALL, UNVISITED, VISITED };
	
	MazeNode();
	~MazeNode();

	MazeNode* getNorth();
	MazeNode* getEast();
	MazeNode* getSouth();
	MazeNode* getWest();

	NodeType getType();

	void setNorth(MazeNode* mn);
	void setEast(MazeNode* mn);
	void setSouth(MazeNode* mn);
	void setWest(MazeNode* mn);

	void setType(NodeType t);

private:
	MazeNode* north;
	MazeNode* east;
	MazeNode* south;
	MazeNode* west;

	NodeType type;
};

