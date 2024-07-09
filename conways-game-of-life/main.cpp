#include <raylib.h>
#include <iostream>
#include "simulation.hpp"

int main(){
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    int FPS = 12;
    const int CELL_SIZE = 25;

    Color GREY = {29, 29, 29, 255};

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game of Life");
    SetTargetFPS(FPS);

    Simulation simulation{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE};

    simulation.SetCellValue(5, 29, 1);
    simulation.SetCellValue(6, 0, 1);
    simulation.SetCellValue(5, 0, 1);
    simulation.SetCellValue(4, 0, 1);

    std::cout << simulation.CountLiveNeighbors(5, 29) << std::endl;

    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(GREY);

        simulation.Draw();

        EndDrawing();
    }

    CloseWindow();
}