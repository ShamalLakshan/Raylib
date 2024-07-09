#include <raylib.h>
#include "grid.hpp"

int main(){
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    int FPS = 12;
    const int CELL_SIZE = 25;

    Color GREY = {29, 29, 29, 255};

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game of Life");
    SetTargetFPS(FPS);

    Grid grid{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE};

    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(GREY);
        grid.Draw();
        EndDrawing();
    }

    CloseWindow();
}