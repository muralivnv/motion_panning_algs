#include <A_star/AStarGrid.h>

inline bool operator == (const Node& lhs, const Node& rhs)
{
    return (lhs.pos_x == rhs.pos_x) 
            && (lhs.pos_y == rhs.pos_y);
}

void AStarGrid::create_grid()
{
    for (uint x = 0; x < grid_.size(); ++x)
    {
        for (uint y = 0; y < grid_[0].size(); ++y)
        {
            grid_[x][y].pos_x = x + node_radius_;
            grid_[x][y].pos_y = y + node_radius_;
        }
    }
}

void AStarGrid::start(int x, int y)
{
    start_x_ = x;
    start_y_ = y;
    grid_[start_x_][start_y_].g_cost = 0.0;
    grid_[start_x_][start_y_].h_cost = 0.0;
}

void AStarGrid::goal(int x, int y)
{
    goal_x_ = x;
    goal_y_ = y;
    grid_[goal_x_][goal_y_].g_cost = 0.0;
    grid_[goal_x_][goal_y_].h_cost = 0.0;
}

void AStarGrid::add_obstacle(int x, int y)
{
    grid_[x][y].is_obstacle = true;
}

void AStarGrid::calc_node_weights(Node& parent_node, Node& successor_node)
{
    int delta_X = std::abs(successor_node.pos_x - parent_node.pos_x);
    int delta_Y = std::abs(successor_node.pos_y - parent_node.pos_y);

    if (delta_X > delta_Y)
    {
        successor_node.g_cost = parent_node.g_cost + 2*delta_Y + 
                                                     1*(delta_X - delta_Y);
    }
    else
    {
        successor_node.g_cost = parent_node.g_cost + 2*delta_X + 
                                                     1*(delta_Y - delta_X);
    }

    successor_node.h_cost = 5*(std::abs(successor_node.pos_x - goal_x_) + 
                             std::abs(successor_node.pos_y - goal_y_));
}

bool contains(std::vector<Node>& list, Node& node)
{
    auto iter = std::find(list.begin(),list.end(), node);
    return (iter != list.end());
}

bool contains(std::set<std::pair<int, int> >& list, Node& node)
{
    return !(list.find(std::make_pair(node.pos_x, node.pos_y)) == list.end());
}

bool AStarGrid::push_neighbours_to_list(std::set<std::pair<int, int> >& list,
                                        std::vector<Node>& closed_list, 
                                        int lower_idx_x, int lower_idx_y)
{
    Node& node = grid_[lower_idx_x][lower_idx_y];

    for (int i = node.pos_x - 1; i <= node.pos_x + 1; i++)
    {
        for (int j = node.pos_y - 1; j <= node.pos_y + 1; j++)
        {
            if (grid_[i][j].is_obstacle)
            { continue; }
            else if (!contains(closed_list, grid_[i][j]))
            {
                if (i == goal_x_ && j == goal_y_)
                { return true; }

                if (i == node.pos_x && j == node.pos_y)
                { continue; }
                else
                {
                    auto current_node = grid_[i][j];
                    calc_node_weights(node,current_node);

                    if (!contains(list, current_node) || list.empty())
                    {
                        list.insert(std::make_pair(i,j));
                        grid_[i][j] = current_node;
                    }
                    else if (grid_[i][j].g_cost + 
                            grid_[i][j].h_cost 
                                >
                            current_node.g_cost + 
                            current_node.h_cost )
                    {
                            grid_[i][j] = current_node;
                    }
                }
            }
        }
    }
    return false;
}

void AStarGrid::generate_shortest_path()
{
    std::set<std::pair<int,int> > open_list;
    std::vector<Node> closed_list;

    open_list.insert(std::make_pair(start_x_, start_y_));
    bool found_goal = false;

    while (!open_list.empty())
    {
        std::pair<int, int> lowest_idx;

        auto smaller = open_list.begin();

        for (std::set<std::pair<int,int> >::iterator elem  = open_list.begin()++; 
                elem != open_list.end(); ++elem)
        {
            int smaller_f_cost = grid_[smaller->first][smaller->second].g_cost + 
                                  grid_[smaller->first][smaller->second].h_cost;
            
            int elem_f_cost = grid_[elem->first][elem->second].g_cost + 
                              grid_[elem->first][elem->second].h_cost ;

            if ( ( smaller_f_cost > 
                   elem_f_cost) || 
                  (smaller_f_cost == elem_f_cost && grid_[smaller->first][smaller->second].h_cost > 
                                                    grid_[elem->first][elem->second].h_cost))
            {
                smaller = elem;
            }
        }

        int lower_idx_x = smaller->first;
        int lower_idx_y = smaller->second;

        open_list.erase(smaller);
        closed_list.push_back(grid_[lower_idx_x][lower_idx_y]);

        found_goal = push_neighbours_to_list(open_list,closed_list, lower_idx_x, lower_idx_y);
        
        if (found_goal)
        { break; }
    }
    
    closed_list.push_back(grid_[goal_x_][goal_y_]);

    draw_grid(closed_list);
}

void AStarGrid::print()
{
    for (uint x = 0; x < grid_.size(); ++x)
    {
        for (uint y = 0; y < grid_[0].size(); ++y)
        {
            std::cout<< "( " << grid_[x][y].pos_x << ",";
            std::cout<< grid_[x][y].pos_y << " )";

            std::cout << "    ";
        }
        std::cout << '\n';
    }
}

void AStarGrid::draw_grid(std::vector<Node>& list)
{
    std::cout << "List-->size\n" << list.size() << '\n';
    sf::RenderWindow window(sf::VideoMode(800,600), "Path Planning Search");

    int number_of_blocks_x = grid_size_X_/(2*node_radius_);
    int number_of_blocks_y = grid_size_Y_/(2*node_radius_);

    int block_width_in_pixel = 800/number_of_blocks_x;
    int block_height_in_pixel = 600/number_of_blocks_y;

    std::vector<sf::VertexArray> horiz_lines(number_of_blocks_x);
    std::vector<sf::VertexArray> vert_lines(number_of_blocks_y);
    std::vector<sf::CircleShape> circles(number_of_blocks_x*number_of_blocks_y );
    std::vector<sf::CircleShape> sol_circles(list.size());

    int height = block_height_in_pixel;
    for (uint i = 0; i < horiz_lines.size(); ++i)
    {
        horiz_lines[i] = sf::VertexArray(sf::Lines, 2);
        (horiz_lines[i])[0].position = sf::Vector2f(0, height);
        (horiz_lines[i])[1].position = sf::Vector2f(800, height);
        (horiz_lines[i])[0].color = sf::Color::Black;
        (horiz_lines[i])[1].color = sf::Color::Black;
        height += block_height_in_pixel;
    }

    int width = block_width_in_pixel;
    for (uint i = 0; i < vert_lines.size(); ++i)
    {
        vert_lines[i] = sf::VertexArray(sf::Lines, 2);
        (vert_lines[i])[0].position = sf::Vector2f(width,0);
        (vert_lines[i])[1].position = sf::Vector2f(width,600);
        (vert_lines[i])[0].color = sf::Color::Black;
        (vert_lines[i])[1].color = sf::Color::Black;
        width += block_width_in_pixel;
    }

    int idx = 0; int circle_radius = 2.5;
    for (uint i = block_width_in_pixel; i < 800; i += block_width_in_pixel)
    {
        for (uint j = block_height_in_pixel; j < 600; j += block_height_in_pixel)
        {
            circles[idx].setRadius(circle_radius);
            circles[idx].setPosition(sf::Vector2f(i - circle_radius, j - circle_radius));
            circles[idx].setFillColor(sf::Color(204,102,0));
            ++idx;
        }
    }

    sf::Font font;
    if (!font.loadFromFile("/home/vnv/Downloads/BebasNeue.otf"))
    {
        std::cerr << "Can't load Font\n";
        exit(-1);
    }
    std::vector<sf::Text> txts(number_of_blocks_x*number_of_blocks_y);

    idx = 0; int pos_x_idx = 0, pos_y_idx = 0;
    std::stringstream SS;

    for (int i = 0; i < (800 - block_width_in_pixel); i += block_width_in_pixel)
    {
        for (int j = 0; j < (600 - block_height_in_pixel); j += block_height_in_pixel)
        {
            SS << grid_[pos_x_idx][pos_y_idx].pos_x << "," <<grid_[pos_x_idx][pos_y_idx].pos_y;
            txts[idx].setFont(font);
            txts[idx].setString(SS.str());
            txts[idx].setColor(sf::Color::Black);
            txts[idx].setCharacterSize(8);
            txts[idx].setPosition(i + (block_width_in_pixel/2) ,
                                  j + (block_height_in_pixel/2));
            ++idx; ++pos_y_idx;
            SS.str("");
        }
        pos_y_idx = 0;
        ++pos_x_idx;
    }

    idx = 0;

    for (auto elem : list)
    {
        sol_circles[idx].setRadius(5);
        sol_circles[idx].setPosition(sf::Vector2f(  elem.pos_x*block_width_in_pixel  - 5- (block_width_in_pixel/2), 
                                                    elem.pos_y*block_height_in_pixel - 5-(block_height_in_pixel/2)));
        sol_circles[idx].setFillColor(sf::Color(255,0,0));
        ++idx;
    }


    sf::Event event;
    while(window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            { window.close(); }
        }

        window.clear(sf::Color::White);
        for (uint i = 0; i < horiz_lines.size(); ++i)
        {
            window.draw(horiz_lines[i]);
        }
        for (uint i = 0; i < vert_lines.size(); ++i)
        {
            window.draw(vert_lines[i]);
        }
        for (uint i = 0; i < circles.size(); ++i)
        {
            window.draw(circles[i]);
        }
        for (uint i = 0; i < sol_circles.size(); ++i)
        {
            window.draw(sol_circles[i]);
        }
        /*for (uint i = 0; i < txts.size(); ++i)
        {
            window.draw(txts[i]);
        }*/
        window.display();
    }
}