include ../Makefile.defs

objects = Maze MSTMaze MazeGraph MazeGenerator

MazeFolders := $(wildcard *Maze/.)

INC = -I. $(addprefix -I,$(MazeFolders))

mazeTypes := $(wildcard *Maze/*.cpp)
$(info $$mazeTypes is [${mazeTypes}])

#target all compiles executable
all : $(objects)
	
Maze : Maze.cpp
	$(CC) -c Maze.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS)

MSTMaze : MSTMaze.cpp
	$(CC) -c MSTMaze.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS)

MazeGraph : MazeGraph.cpp
	$(CC) -c MazeGraph.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS)

MazeGenerator : MazeGenerator.cpp
	$(CC) -c MazeGenerator.cpp $(mazeTypes) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INC)

clean :
	$(shell find . -name "*.o" -type f -delete)