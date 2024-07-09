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


    while(WindowShouldClose() == false){
        //Event Handling
        if (IsKeyPressed(KEY_ENTER))
        {
            simulation.Start();
            SetWindowTitle("Game of Life is Running");
        }
        else if (IsKeyPressed(KEY_SPACE))
        {
            simulation.Stop();
            SetWindowTitle("Game of Life is Paused");
        }
        

        //Updating State
        simulation.Update();

        //Drawing
        BeginDrawing();
        ClearBackground(GREY);

        simulation.Draw();

        EndDrawing();
    }

    CloseWindow();
}