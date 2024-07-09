#include "raylib.h"
#include <vector>
#include <random>
#include <algorithm>

const int kDisplayWidth = 1280;
const int kDisplayHeight = 720;
const int kElementSize = 3;
const int kMatrixWidth = kDisplayWidth / kElementSize;
const int kMatrixHeight = kDisplayHeight / kElementSize;

std::vector<std::vector<int>> currentState(kMatrixWidth, std::vector<int>(kMatrixHeight, 0));
std::vector<std::vector<int>> futureState(kMatrixWidth, std::vector<int>(kMatrixHeight, 0));

bool isSimulationPaused = false;
const int kMaxAge = 10;

void PopulateInitialState() {
    std::mt19937 randomGen(std::random_device{}());
    std::uniform_int_distribution<> coinFlip(0, 1);

    for (int i = 0; i < kMatrixWidth; i++) {
        for (int j = 0; j < kMatrixHeight; j++) {
            currentState[i][j] = coinFlip(randomGen);
        }
    }
}

int CalculateLiveNeighbors(int x, int y) {
    int sum = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = (x + dx + kMatrixWidth) % kMatrixWidth;
            int ny = (y + dy + kMatrixHeight) % kMatrixHeight;
            sum += (currentState[nx][ny] > 0);
        }
    }
    return sum;
}

void EvolveCellularAutomata() {
    for (int i = 0; i < kMatrixWidth; i++) {
        for (int j = 0; j < kMatrixHeight; j++) {
            int aliveNeighbors = CalculateLiveNeighbors(i, j);
            if (currentState[i][j] > 0) {
                futureState[i][j] = (aliveNeighbors == 2 || aliveNeighbors == 3) 
                    ? std::min(currentState[i][j] + 1, kMaxAge) : 0;
            } else {
                futureState[i][j] = (aliveNeighbors == 3) ? 1 : 0;
            }
        }
    }
    currentState.swap(futureState);
}

Color DetermineElementColor(int age) {
    int shade = age * 200 / kMaxAge;
    return Color{255, 255, 255, static_cast<unsigned char>(255 - shade)};
}

void RenderGridLines() {
    for (int i = 0; i <= kMatrixWidth; i++) {
        DrawLine(i * kElementSize, 0, i * kElementSize, kDisplayHeight, DARKGRAY);
    }
    for (int j = 0; j <= kMatrixHeight; j++) {
        DrawLine(0, j * kElementSize, kDisplayWidth, j * kElementSize, DARKGRAY);
    }
}

int main() {
    InitWindow(kDisplayWidth, kDisplayHeight, "Cellular Automaton Simulator");
    SetTargetFPS(10);

    PopulateInitialState();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            isSimulationPaused = !isSimulationPaused;
        }

        if (!isSimulationPaused) {
            EvolveCellularAutomata();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < kMatrixWidth; i++) {
            for (int j = 0; j < kMatrixHeight; j++) {
                if (currentState[i][j] > 0) {
                    DrawRectangle(i * kElementSize, j * kElementSize, 
                                  kElementSize, kElementSize, 
                                  DetermineElementColor(currentState[i][j]));
                }
            }
        }

        RenderGridLines();

        if (isSimulationPaused) {
            DrawText("SIMULATION PAUSED", 10, 10, 20, RED);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}