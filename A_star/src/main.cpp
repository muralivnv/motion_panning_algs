#include <A_star/AStarGrid.h>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    AStarGrid path_grid(25, 25, 0.5);
    path_grid.create_grid();

    path_grid.start(2,7);
    path_grid.goal(20,15);

    path_grid.generate_shortest_path();

    return EXIT_SUCCESS;
}
