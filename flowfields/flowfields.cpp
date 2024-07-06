#include <raylib.h>

int main(){
    const int width = 1000;
    const int height = 1000;

    int left_x = (width * -0.5);
    int right_x = (width * 1.5);
    int top_y = (height * -0.5);
    int bottom_y = (height * 1.5);

    int resolution = (width * 0.01);

    int num_columns = (right_x - left_x) / resolution;
    int num_rows = (bottom_y - top_y) / resolution;

    InitWindow(1000, 1000, "First Raylib project"); //Initialize window(width 800, height 800, window name)
    SetTargetFPS(60); // Setting the frame rate. 

    //Game Loop
    while (WindowShouldClose() == false)
    {
        //Event Handling

        //Updating Positions

        //Drawing
        BeginDrawing(); //Begin Canvas Drawing

        EndDrawing(); //End Canvas Drawing
    }
    

    //Close Window
    CloseWindow();

    return 0;
}