#include "raylib.h"
#include <vector>
#include <cmath>
#include <random>

// Perlin noise function
float noise(float x, float y) {
    // This is a simple implementation of Perlin noise
    // For a more accurate version, you might want to use a library or implement the full algorithm
    const float SEED = 1337.0f;
    x += SEED;
    y += SEED;
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    x -= floor(x);
    y -= floor(y);
    float u = fade(x);
    float v = fade(y);
    int A = p[X] + Y, B = p[X + 1] + Y;
    return lerp(v, lerp(u, grad(p[A], x, y), grad(p[B], x - 1, y)),
                lerp(u, grad(p[A + 1], x, y - 1), grad(p[B + 1], x - 1, y - 1)));
}

// Helper functions for Perlin noise
float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
float lerp(float t, float a, float b) { return a + t * (b - a); }
float grad(int hash, float x, float y) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}



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


        const int num_steps = 1000;  // Adjust as needed
        const float step_length = 5.0f;  // Adjust as needed

        // Starting point
        float x = 500.0f;
        float y = 100.0f;

        // Create a vector to store the points of the curve
        std::vector<Vector2> curvePoints;

        for (int n = 0; n < num_steps; ++n) {
            curvePoints.push_back({x, y});

            float x_offset = x - left_x;
            float y_offset = y - top_y;

            int column_index = static_cast<int>(x_offset / resolution);
            int row_index = static_cast<int>(y_offset / resolution);

            // Check bounds to prevent out-of-range access
            if (column_index >= 0 && column_index < grid.size() &&
                row_index >= 0 && row_index < grid[0].size()) {
                float grid_angle = grid[column_index][row_index];

                float x_step = step_length * cos(grid_angle);
                float y_step = step_length * sin(grid_angle);

                x = x + x_step;
                y = y + y_step;
            } else {
                // Handle out-of-bounds case (e.g., stop the curve or wrap around)
                break;
            }
        }

        // Draw the curve
        if (curvePoints.size() > 1) {
            for (size_t i = 0; i < curvePoints.size() - 1; ++i) {
                DrawLineV(curvePoints[i], curvePoints[i + 1], RED);
            }
        }


        EndDrawing(); //End Canvas Drawing
    }
    

    //Close Window
    CloseWindow();

    return 0;
}