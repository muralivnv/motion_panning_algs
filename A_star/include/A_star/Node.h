#ifndef _A_star_NODE_H_
#define _A_star_NODE_H_

struct Node{
    Node* parent;
    bool is_obstacle = false;
    int pos_x = 0, pos_y = 0;

    double g_cost = 1000.0, h_cost = 1000.0;
};

#endif
