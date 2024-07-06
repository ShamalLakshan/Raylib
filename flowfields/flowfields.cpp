#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

// Function prototypes
float fade(float t);
float lerp(float t, float a, float b);
float grad(int hash, float x, float y);
float noise(float x, float y);

// Permutation table
std::vector<int> p(256);

// Initialize the permutation table
void initPermutationTable() {
    for (int i = 0; i < 256; i++) {
        p[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(p.begin(), p.end(), g);
    p.insert(p.end(), p.begin(), p.end()); // Duplicate the array
}

// Helper functions for Perlin noise
float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float lerp(float t, float a, float b) { 
    return a + t * (b - a); 
}

float grad(int hash, float x, float y) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

// Perlin noise function
float noise(float x, float y) {
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

std::vector<Vector2> generateCurve(float startX, float startY, const std::vector<std::vector<float>>& grid, int left_x, int top_y, int resolution, int num_steps, float step_length) {
    std::vector<Vector2> curvePoints;
    float x = startX;
    float y = startY;

    for (int n = 0; n < num_steps; ++n) {
        curvePoints.push_back({x, y});

        float x_offset = x - left_x;
        float y_offset = y - top_y;

        int column_index = static_cast<int>(x_offset / resolution);
        int row_index = static_cast<int>(y_offset / resolution);

        if (column_index >= 0 && column_index < grid.size() &&
            row_index >= 0 && row_index < grid[0].size()) {
            float grid_angle = grid[column_index][row_index];

            float x_step = step_length * cos(grid_angle);
            float y_step = step_length * sin(grid_angle);

            x = x + x_step;
            y = y + y_step;
        } else {
            break;
        }
    }

        return curvePoints;
}

Color getRandomColor() {
    return { 
        static_cast<unsigned char>(GetRandomValue(0, 255)),
        static_cast<unsigned char>(GetRandomValue(0, 255)),
        static_cast<unsigned char>(GetRandomValue(0, 255)),
        255
    };
}

int main() {
    const int width = 400;
    const int height = 400;
    const float MY_PI = 3.14159265358979323846f;

    int left_x = (width * -0.5);
    int right_x = (width * 1.5);
    int top_y = (height * -0.5);
    int bottom_y = (height * 1.5);

    int resolution = (width * 0.01);

    int num_columns = (right_x - left_x) / resolution;
    int num_rows = (bottom_y - top_y) / resolution;

    std::vector<std::vector<float>> grid(num_columns, std::vector<float>(num_rows));

    InitWindow(width, height, "Flow Field - 50 Curves");
    SetTargetFPS(60);

    initPermutationTable();

    while (!WindowShouldClose()) {
        // Update grid
        for (int column = 0; column < num_columns; column++) {
            for (int row = 0; row < num_rows; row++) {
                float scaledX = column * 0.005f;
                float scaledY = row * 0.005f;
                float noiseVal = noise(scaledX, scaledY);
}