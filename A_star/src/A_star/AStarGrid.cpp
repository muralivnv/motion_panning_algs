#include <A_star/AStarGrid.h>


void AStarGrid::create_grid()
{
    for (uint x = 0; x < grid_.size(); ++x)
    {
        for (uint y = 0; y < grid_[0].size(); ++y)
        {
            grid_[x][y].pos_x = x + node_radius_;
            grid_[x][y].pos_y = y + node_radius_;
        }
    }
}

void AStarGrid::print()
{
    for (uint x = 0; x < grid_.size(); ++x)
    {
        for (uint y = 0; y < grid_[0].size(); ++y)
        {
            std::cout<< "( " << grid_[x][y].pos_x << ",";
            std::cout<< grid_[x][y].pos_y << " )";

            std::cout << "    ";
        }
        std::cout << '\n';
    }
}

