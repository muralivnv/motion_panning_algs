#include <A_star/AStarGrid.h>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    AStarGrid path_grid(15,15, 0.5);
    path_grid.create_grid();

    path_grid.start(4,3);
    path_grid.goal(8,12);
    path_grid.generate_shortest_path();

    return EXIT_SUCCESS;
}
