CC = g++
CCFLAGS = -g -Wall -Wextra
RAYLIBFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
PROGRAM = main
PROGRAM_LINKS = grid.cpp

$(PROGRAM): $(PROGRAM).cpp
	$(CC) $(PROGRAM).cpp $(PROGRAM_LINKS) $(CCFLAGS) $(RAYLIBFLAGS) -o $(PROGRAM)

clean:
	$(PROGRAM).cpp