#include <A_star/AStarGrid.h>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{

    AStarGrid path_grid(30,30,0.5);
    path_grid.create_grid();

    path_grid.draw_grid();

    return EXIT_SUCCESS;
}
