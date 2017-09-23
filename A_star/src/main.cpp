#include <A_star/AStarGrid.h>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{

    AStarGrid path_grid(15,15,1);
    path_grid.create_grid();
    path_grid.print();

    return EXIT_SUCCESS;
}
