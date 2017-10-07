#ifndef _prm_PRM_H_
#define _prm_PRM_H_

#include "Node.h"
#include "Graph.h"
#include <random>

class PRM{
    int map_size_x = 0.0, map_size_y = 0.0;
    Graph* G;

    int start_x_ = 0.0, start_y_ = 0.0;
    int goal_x_ = 0.0, goal_y_ = 0.0;
public:
    PRM(int x, int y ): map_size_x(x), 
                        map_size_y(y),
                        G(new Graph()){}

    void new_vertex(int, int);
    void new_edge(Node*, Node*);
    void create_road_map(int, int);
    bool is_edge_collision_free(Node*, Node*);

    void set_start(int x, int y){
        start_x_ = x;
        start_y_ = y;
    }

    void set_goal (int x, int y){
        goal_x_ = x;
        goal_y_ = y;
    }

    std::vector<Node*> update_road_map(int);

    Graph* get_graph();
};

void PRM::new_vertex(int x, int y)
{
    Node* node = new Node(x,y);
    G->add_vertex(node);
}

void PRM::new_edge(Node* q1, Node* q2)
{
    G->create_edge(q1, q2);
}

void PRM::create_road_map(int num_of_vertices, int n_neighbours)
{
    std::random_device rand_gen;
    std::mt19937 uniform_rand(rand_gen());
    std::uniform_int_distribution<> x_rand_gen(0, map_size_x);
    std::uniform_int_distribution<> y_rand_gen(0, map_size_y);

    int vertex = 0;
    
    while (vertex < num_of_vertices)
    {
        int rand_x = x_rand_gen(uniform_rand);
        int rand_y = y_rand_gen(uniform_rand);

        new_vertex(rand_x, rand_y);
        ++vertex;
    }

    for ( int i = 0; i < vertex; ++i)
    {
        auto q = G->get_node(i);
        auto Nq = G->get_neighbour_node(q, n_neighbours);

        for (unsigned int j = 0; j < Nq.size(); j++)
        {
            if (! G->is_edge_exist(q,Nq[j]) &&  is_edge_collision_free(q,Nq[j]) )
            {
                new_edge(q, Nq[j]);
            }
        }
    }
}

std::vector<Node*> PRM::update_road_map(int n_neighbours)
{
    new_vertex(start_x_, start_y_);
    new_vertex(goal_x_, goal_y_);

    auto start_node = G->get_node(G->num_of_vertices()-2);
    auto goal_node = G->get_node(G->num_of_vertices()-1);

    auto Nq = G->get_neighbour_node(start_node, n_neighbours);
    for (unsigned int j = 0; j < Nq.size(); j++)
    {
        if (! G->is_edge_exist(start_node, Nq[j] ) &&  is_edge_collision_free(start_node, Nq[j]) )
        {
            new_edge(start_node, Nq[j]);
            break;
        }
    }

    Nq = G->get_neighbour_node(goal_node, n_neighbours);
    for (unsigned int j = 0; j < Nq.size(); j++)
    {
        if (! G->is_edge_exist(goal_node, Nq[j] ) &&  is_edge_collision_free(goal_node, Nq[j]) )
        {
            new_edge(goal_node, Nq[j]);
            break;
        }
    }
    return {start_node, goal_node};
}

Graph* PRM::get_graph()
{ return G; }

bool PRM::is_edge_collision_free(Node* q1, Node* q2)
{ return true; }

#endif
