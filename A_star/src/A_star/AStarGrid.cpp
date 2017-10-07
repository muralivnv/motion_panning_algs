#include <A_star/AStarGrid.h>

void AStarGrid::create_grid()
{
    for (uint x = 0; x < grid_.size(); ++x)
    {
        for (uint y = 0; y < grid_[0].size(); ++y)
        {
            grid_[x][y].pos_x = x;
            grid_[x][y].pos_y = y;
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

void AStarGrid::calc_node_weights(Node& parent_node, Node& successor_node)
{
}

auto contains(std::set<std::pair<int, int> >& list, Node& node)
{
    return list.find(std::make_pair(node.pos_x, node.pos_y));
}

bool AStarGrid::push_neighbours_to_list(std::set<std::pair<int, int> >& list,
                                        std::set<std::pair<int, int> >& closed_list, 
                                        int lower_idx_x, int lower_idx_y)
{

}

void AStarGrid::generate_shortest_path()
{

}

void AStarGrid::draw_grid(std::set<std::pair<int,int>>& list)
{
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

    int idx = 0; int circle_radius = 3.5;
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
            txts[idx].setCharacterSize(5);
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
        sol_circles[idx].setPosition(sf::Vector2f(  elem.first*block_width_in_pixel  - 5- (block_width_in_pixel/2), 
                                                    elem.second*block_height_in_pixel - 5-(block_height_in_pixel/2)));
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
//        for (uint i = 0; i < circles.size(); ++i)
//        {
//            window.draw(circles[i]);
//        }
        for (uint i = 0; i < sol_circles.size(); ++i)
        {
            window.draw(sol_circles[i]);
        }
//        for (uint i = 0; i < txts.size(); ++i)
//        {
//            window.draw(txts[i]);
//        }
        window.display();
    }
}

