#include <iostream>
#include <cstdlib>
#include "PRM.h"
#include "Astar.h"

#include <fstream>

int main()
{
    PRM prm(100, 100);
    prm.create_road_map(1500, 10);

    prm.set_start(5,5);
    prm.set_goal(85,95);
    
    std::vector<Node*> req_cfg = prm.update_road_map(10);
    Graph* G = prm.get_graph();

    auto list = A_star(req_cfg[0], req_cfg[1]); 


    /* PLOTTING */
    std::ofstream out_file, plot_file, result_file;
    out_file.open("prm_random_config.dat", std::ofstream::out);
    plot_file.open("plot_prm.plt", std::ofstream::out);
    result_file.open("a_star_solution.dat", std::ofstream::out);

    //
    out_file << "#pos_x" << "    " << "#pos_y\n";
    result_file << "#pos_x" << "    " << "#pos_y\n";

    for (int i = 0; i < G->num_of_vertices(); ++i)
    {
        Node* q = G->get_node(i);
        for (unsigned int j = 0; j < q->connected_vertices.size(); ++j)
        {
            out_file << q->pos_x << "    " << q->pos_y << '\n';
            out_file << q->connected_vertices[j]->pos_x << "    " << q->connected_vertices[j]->pos_y << '\n';
        }
        out_file << "\n";
    }
    plot_file << "set term qt 0 position 100,100\n" << "plot 'prm_random_config.dat' u 1:2 w l lw 0.8\n" << "set grid\n" << "replot\n";

    for (auto elem : list)
    {
        result_file << elem->node->pos_x << "       " << elem->node->pos_y << '\n';
    }

    //
    out_file.close();
    plot_file.close();
    result_file.close();
    std::system("gnuplot -p plot_prm.plt");
}
