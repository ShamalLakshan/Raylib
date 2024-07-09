CC = g++
CCFLAGS = -g -Wall -Wextra
RAYLIBFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
PROGRAM = main

$(PROGRAM): $(PROGRAM).cpp
	$(CC) $(PROGRAM).cpp $(CCFLAGS) $(RAYLIBFLAGS) -o $(PROGRAM)

clean:
	$(PROGRAM).cpp