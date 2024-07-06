#include <raylib.h>
#include <cmath>
#include <vector>

int main(){
    const int width = 1000;
    const int height = 1000;
    const float PIE = 3.14;

    int left_x = (width * -0.5);
    int right_x = (width * 1.5);
    int top_y = (height * -0.5);
    int bottom_y = (height * 1.5);

    int resolution = (width * 0.01);

    int num_columns = (right_x - left_x) / resolution;
    int num_rows = (bottom_y - top_y) / resolution;

    const float default_angle = PIE * 0.25;

    std::vector<std::vector<float>> grid(num_columns, std::vector<float>(num_rows));


    InitWindow(1000, 1000, "First Raylib project"); //Initialize window(width 800, height 800, window name)
    SetTargetFPS(60); // Setting the frame rate. 

    //Game Loop
    while (WindowShouldClose() == false)
    {
        //Event Handling

        //Updating Positions
        for (int column = 0; column < num_columns; ++column) {
            for (int row = 0; row < num_rows; ++row) {
                float angle = (static_cast<float>(row) / num_rows) * PI;
                grid[column][row] = angle;
            }
        }

        //Drawing
        BeginDrawing(); //Begin Canvas Drawing
        ClearBackground(WHITE);


        float cellWidth = static_cast<float>(screenWidth) / num_columns;
        float cellHeight = static_cast<float>(screenHeight) / num_rows;
        
        for (int column = 0; column < num_columns; ++column) {
            for (int row = 0; row < num_rows; ++row) {
                float angle = grid[column][row];
                
                // Calculate the center of each cell
                Vector2 center = {
                    column * cellWidth + cellWidth / 2,
                    row * cellHeight + cellHeight / 2
                };
                
                // Calculate the end point of the line based on the angle
                Vector2 end = {
                    center.x + cos(angle) * (cellWidth / 2),
                    center.y + sin(angle) * (cellHeight / 2)
                };
                
                // Draw a line representing the angle
                DrawLineEx(center, end, 2, BLACK);
            }
        }


        EndDrawing(); //End Canvas Drawing
    }
    

    //Close Window
    CloseWindow();

    return 0;
}