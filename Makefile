include Makefile.defs

#Executable name
OBJ_NAME = mazes

MazeFolders := $(wildcard MazeGeneration/*Maze/.)

INC = -I. -IMazeGeneration/. $(addprefix -I,$(MazeFolders))

#target all compiles executable
all : MazeGenerator
	$(eval OBJS := $(wildcard **/*.o))
	$(CC) main.cpp $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INC) -o $(OBJ_NAME)

MazeGenerator :
	$(MAKE) -C MazeGeneration

.PHONY : clean

clean :
	$(RM) mazes $(OBJS)