#include "simulation.hpp"
#include <vector>
#include<utility>


void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{
    int liveNeighbors = 0;
    std::vector<std::pair<int,int>> neighborOffsets = 
    {
        {-1, 0}, // Directly above
        {1, 0},  // Directly below
        {0, -1}, // To the left
        {0, 1},  // To the right
        {-1, -1},// Diagonal upper left
        {-1, 1}, // Diagonal upper right
        {1, -1}, // Diagonal lower left
        {1, 1}   // Diagonal lower right
    };

    for(const auto& offset : neighborOffsets)
    {
        int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
        int neighborColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns();
        liveNeighbors += grid.GetValue(neighborRow, neighborColumn);
    }
    return liveNeighbors;
}
