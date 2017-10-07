#ifndef _prm_ASTAR_H_
#define _prm_ASTAR_H_

#include "Node.h"
#include "Graph.h"
#include <vector>
#include <iostream>

struct as_node{
    Node* node;
    int g_cost = 0.0, h_cost = 0.0;

    int f_cost()
    { return g_cost+h_cost; }
    
    as_node(Node* n) : node(n){}
};

void calculate_node_weight(as_node* parent, as_node* current_node, Node* goal)
{
    int delta_X = std::abs( current_node->node->pos_x -
                            parent->node->pos_x);

    int delta_Y = std::abs( current_node->node->pos_y -
                            parent->node->pos_y);

    if (delta_X > delta_Y)
    {
        current_node->g_cost = parent->g_cost + 14*delta_Y +
                                               10*(delta_X - delta_Y); 
    }
    else
    {
        current_node->g_cost = parent->g_cost + 14*delta_X +
                                               10*(delta_Y - delta_X); 
    }
    current_node->h_cost = std::abs(current_node->node->pos_x - goal->pos_x) + 
                            std::abs(current_node->node->pos_y - goal->pos_y);
}


std::vector<as_node*>::iterator 
contains(std::vector<as_node*>& list, as_node* node)
{
    std::vector<as_node*>::iterator iter;
    for (   iter = list.begin();
            iter != list.end(); 
            ++iter)
    {
        if (    node->node->pos_x == (*iter)->node->pos_x && 
                node->node->pos_y == (*iter)->node->pos_y )
        { return iter; }
    }

    return iter;
}

bool push_neighbours_to_list(   std::vector<as_node*>& open_list,
                                std::vector<as_node*>& closed_list,
                                as_node* parent, Node* goal)
{
    as_node* current_node;
    for (unsigned int i = 0; i < (parent->node)->connected_vertices.size(); ++i)
    {
        current_node = new as_node((parent->node)->connected_vertices[i]);
        if (contains(closed_list, current_node) == closed_list.end() )
        {
            if (current_node->node->pos_x == goal->pos_x &&
                    current_node->node->pos_y == goal->pos_y)
            {
                return true;
            }
            calculate_node_weight(parent, current_node, goal);
            auto iter = contains(open_list, current_node);

            if (iter == open_list.end())
            {
                open_list.push_back(current_node);
            }
            else
            {
                if ((*iter)->f_cost() > current_node->f_cost())
                {
                    *iter = current_node;
                }
            }
        }
    }
    return false;
}



std::vector<as_node*> A_star(Node* src, Node* goal)
{
    std::vector<as_node*> open_list, closed_list;
    open_list.push_back(new as_node(src));
    bool found_goal = false;
    while (!open_list.empty())
    {
        auto smallest_node = open_list[0];
        std::vector<as_node*>::iterator iter = open_list.begin();
        for (std::vector<as_node*>::iterator it = open_list.begin();
              it != open_list.end(); ++it)
        {
            if (smallest_node->f_cost() > (*it)->f_cost())
            {
                smallest_node = *it;
                iter = it;
            }
        }
        open_list.erase(iter);

        found_goal = push_neighbours_to_list(open_list, closed_list, smallest_node, goal);

        if (found_goal)
        { break; }

        closed_list.push_back(smallest_node);
    }

    return closed_list;
}


#endif
