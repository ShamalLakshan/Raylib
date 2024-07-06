#include <raylib.h>

int main(){
    int ball_x = 400;
    int ball_y = 400;
    Color green = {20, 160, 133, 255}; // Color Struct = (R, G, B, Alpha (upto 255))

    InitWindow(800, 800, "First Raylib project"); //Initialize window(width 800, height 800, window name)
    SetTargetFPS(60); // Setting the frame rate. 

    //Game Loop
    while (WindowShouldClose() == false)
    {
        //Event Handling
        if(IsKeyDown(KEY_RIGHT)){ //Is the right key pressed
            ball_x +=3;
        }
        else if(IsKeyDown(KEY_LEFT)){
            ball_x -= 3;
        }
        else if(IsKeyDown(KEY_UP)){
            ball_y -= 3;
        }
        else if(IsKeyDown(KEY_DOWN)){
            ball_y += 3;
        }
        else if(IsKeyDown(KEY_Z)){ // Reset Ball
            ball_x = 400;
            ball_y = 400;
        }

        //Updating Positions
            //ball_x += 3;

        //Drawing
        BeginDrawing(); //Begin Canvas Drawing
        DrawCircle(ball_x, ball_y, 20, WHITE); //Draw Circle : Position(x, y) , radius, color
        ClearBackground(green); // Fill the game window with black

        EndDrawing(); //End Canvas Drawing
    }
    

    //Close Window
    CloseWindow();

    return 0;
}