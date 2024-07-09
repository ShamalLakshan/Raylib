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
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.x / CELL_SIZE;
            int column = mousePosition.y / CELL_SIZE;
        }

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
        else if (IsKeyPressed(KEY_F))
        {
            FPS += 2;
            SetTargetFPS(FPS);
        }
        else if (IsKeyPressed(KEY_S))
        {
            FPS -= 2;
            SetTargetFPS(FPS);
        }
        else if (IsKeyPressed(KEY_R))
        {
            simulation.CreateRandomState();
        }
        else if (IsKeyPressed(KEY_C))
        {
            simulation.ClearGrid();
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

//1:04