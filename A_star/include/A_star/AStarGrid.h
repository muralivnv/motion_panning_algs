#ifndef _A_star_ASTARGRIDMAP_H_
#define _A_star_ASTARGRIDMAP_H_

#include "Node.h"
#include <iostream>
#include <vector>


class AStarGrid{
    int grid_size_X_ = 0, grid_size_Y_ = 0;
    int node_radius_ = 0;
    
    std::vector<std::vector<Node> > grid_;

    public:
        AStarGrid(int gridX, int gridY, int radius) 
                    :   grid_size_X_(gridX), grid_size_Y_(gridY),
                        node_radius_(radius){
              
              int x_nodes = grid_size_X_/(2*node_radius_);
              int y_nodes = grid_size_Y_/(2*node_radius_);

              grid_ = std::vector<std::vector<Node> >(x_nodes, std::vector<Node>(y_nodes));
        }

        void create_grid();
        void start(int,int);
        void goal(int,int);
        void print();
};

#endif


