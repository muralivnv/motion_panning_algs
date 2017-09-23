#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Path Planning Search");

    int num_horiz = 800/10;
    int num_vert = 600/10;

    std::vector<sf::VertexArray> horiz_lines(num_horiz);
    std::vector<sf::VertexArray> vert_lines(num_vert);
    std::vector<sf::CircleShape> circles(num_horiz*num_vert -2*(num_horiz+num_vert));

    int height = 50;
    for (uint i = 0; i < horiz_lines.size(); ++i)
    {
        horiz_lines[i] = sf::VertexArray(sf::Lines, 2);
        (horiz_lines[i])[0].position = sf::Vector2f(0, height);
        (horiz_lines[i])[1].position = sf::Vector2f(800, height);
        (horiz_lines[i])[0].color = sf::Color::Black;
        (horiz_lines[i])[1].color = sf::Color::Black;
        height += 50;
    }

    int width = 50;
    for (uint i = 0; i < vert_lines.size(); ++i)
    {
        vert_lines[i] = sf::VertexArray(sf::Lines, 2);
        (vert_lines[i])[0].position = sf::Vector2f(width,0);
        (vert_lines[i])[1].position = sf::Vector2f(width,600);
        (vert_lines[i])[0].color = sf::Color::Black;
        (vert_lines[i])[1].color = sf::Color::Black;
        width += 50;
    }

    int idx = 0; int circle_radius = 3.5;
    for (uint i = 50; i < 800; i+=50)
    {
        for (uint j = 50; j < 600; j+=50)
        {

            circles[idx].setRadius(circle_radius);
            circles[idx].setPosition(sf::Vector2f(i-circle_radius,j-circle_radius));
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
    std::vector<sf::Text> txts(num_horiz*num_vert - num_horiz-num_vert);

    idx = 0;
    for (uint i = 0; i < 800; i+=50)
    {
        for (uint j = 0; j < 600; j+=50)
        {

            txts[idx].setFont(font);
            txts[idx].setString("1");
            txts[idx].setColor(sf::Color::Black);
            txts[idx].setCharacterSize(10);
            txts[idx].setPosition(i+25,j+25);
            ++idx;
        }

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
        for (uint i = 0; i < txts.size(); ++i)
        {
            window.draw(txts[i]);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
