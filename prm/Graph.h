#ifndef _prm_GRAPH_H_
#define _prm_GRAPH_H_

#include "Node.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Graph{
    std::vector<Node*> vertices;
public:
    void add_vertex(Node*);
    void create_edge(Node*, Node*);
    bool is_edge_exist(Node*, Node*);
    Node* get_node(int);
    std::vector<Node*> get_neighbour_node(Node*, int );

    int num_of_vertices();
};

void Graph::add_vertex(Node* q)
{
    vertices.push_back(q);
}

void Graph::create_edge(Node* q1, Node* q2)
{
   q1->connected_vertices.push_back(q2);
   q2->connected_vertices.push_back(q1);
}

bool Graph::is_edge_exist(Node* q1, Node* q2)
{
    if (q1->pos_x != q2->pos_x && q1->pos_y != q2->pos_y)
    {
        for (auto elem : q1->connected_vertices)
        {
            if (q2->pos_x == elem->pos_x && q2->pos_y == elem->pos_y)
            {
                return true;
            }
        }
    }
    else
    { return true; }
}

Node* Graph::get_node(int idx)
{
    return vertices[idx];
}

std::vector<Node*> Graph::get_neighbour_node(Node* q, int n_neighbours)
{
    std::sort(  vertices.begin(), 
                vertices.end(),
                
                [&q](Node* left, Node* right){
                    double delta_x_left = (left->pos_x - q->pos_x);
                    double delta_y_left = (left->pos_y - q->pos_y);
                    double delta_x_right = (right->pos_x - q->pos_x);
                    double delta_y_right = (right->pos_y - q->pos_y);

                    double dist_left = std::sqrt( (delta_x_left*delta_x_left) +
                                                    (delta_y_left*delta_y_left) );

                    double dist_right = std::sqrt( (delta_x_right*delta_x_right) +
                                                    (delta_y_right*delta_y_right) );
                    return dist_left < dist_right;
                } );

    std::vector<Node*> neighbours(vertices.begin(),
                                  vertices.begin()+n_neighbours+1);

    return neighbours;
}


int Graph::num_of_vertices()
{
    return vertices.size();
}

#endif
