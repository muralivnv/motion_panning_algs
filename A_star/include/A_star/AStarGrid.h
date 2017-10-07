#ifndef _A_star_ASTARGRIDMAP_H_
#define _A_star_ASTARGRIDMAP_H_

#include "Node.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <list>
#include <set>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;


class AStarGrid{
    int grid_size_X_ = 0, grid_size_Y_ = 0;
    double node_radius_ = 0.0;
    
    std::vector<std::vector<Node> > grid_;
    int start_x_ = 0, start_y_ = 0;
    int goal_x_ = 0, goal_y_ = 0;

    public:
        AStarGrid(int gridX, int gridY, double radius) 
                    :   grid_size_X_(gridX), grid_size_Y_(gridY),
                        node_radius_(radius){
              
              int x_nodes = grid_size_X_/(2*node_radius_);
              int y_nodes = grid_size_Y_/(2*node_radius_);

              grid_ = std::vector<std::vector<Node> >(x_nodes, std::vector<Node>(y_nodes));
        }

        void create_grid();
        void start(int,int);
        void goal(int,int);
        void calc_node_weights(Node&, Node&);
        bool push_neighbours_to_list(std::set<std::pair<int, int>>&,
                                     std::set<std::pair<int, int>>&,
                                     int, int);
        void generate_shortest_path();

        void draw_grid(std::set<std::pair<int,int>>& );
};

#endif


