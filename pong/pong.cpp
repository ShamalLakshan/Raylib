#include <raylib.h>

//14:45

int main(){
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE); // Start position x, Start position y, end position x, end position y, Color(color)
        DrawCircle(screen_width / 2, screen_height / 2, 20, WHITE);
        DrawRectangle(10, screen_height / 2 - 60, 25, 120, RED); // position X, position Y, width , height, Color(color)
        DrawRectangle(screen_width - 35, screen_height / 2 - 60, 25, 120, RED);

        EndDrawing();
    }
    

    CloseWindow();

    return 0;
}