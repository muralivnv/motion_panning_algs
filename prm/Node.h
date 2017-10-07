#ifndef _prm_NODE_H_
#define _prm_NODE_H_

#include <iostream>
#include <vector>

struct Node{
    double pos_x = 0.0, pos_y = 0.0;
    std::vector<Node*> connected_vertices;
    Node(int x, int y) : pos_x(x), pos_y(y){}
};

#endif
