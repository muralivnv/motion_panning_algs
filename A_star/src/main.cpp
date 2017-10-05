#include <A_star/AStarGrid.h>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    AStarGrid path_grid(15,15,0.5);
    path_grid.create_grid();

    path_grid.start(5,5);
    path_grid.goal(10,5);
    path_grid.generate_shortest_path();

//    path_grid.draw_grid();

    return EXIT_SUCCESS;
}
