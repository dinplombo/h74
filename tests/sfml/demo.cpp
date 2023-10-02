#include <SFML/Graphics.hpp>


void center_screen(sf::RenderWindow& a_window)

{   
    sf::Vector2i screen_center(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
    a_window.setPosition(screen_center - sf::Vector2i(600/2, 400/2)); //why vector2i dont work
}

void make_shapes(sf::RenderWindow& window, sf::RectangleShape& rectangle, sf::CircleShape& circle)
{
     float outline_thickness = 5.0f;
    sf::Vector2f rectangle_size(window.getSize().x - 2 * outline_thickness, window.getSize().y - 2 * outline_thickness);
    rectangle.setSize(rectangle_size);
    rectangle.setOutlineThickness(outline_thickness);
    rectangle.setOutlineColor(sf::Color::Blue);
    rectangle.setPosition(outline_thickness, outline_thickness);

    circle.setRadius(15.f);
    circle.setOutlineThickness(5);
    circle.setOutlineColor(sf::Color::Red);
}



int main()
{

    sf::RenderWindow window(sf::VideoMode(600, 600), "demo!");
    center_screen(window);

    sf::RectangleShape rectangle;
    sf::CircleShape circle;
    make_shapes(window, rectangle, circle);

    sf::Vector2f circle_position((window.getSize().x / 2) , (window.getSize().y / 2));
    circle.setPosition(circle_position);

    float x_delta = 0.5;
    float y_delta = 0.5;
    while (window.isOpen())
    {
        sf::Event interupt;
        while (window.pollEvent(interupt))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || interupt.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }

        circle_position.x += x_delta;
        circle_position.y += y_delta;

        if (circle_position.x + circle.getRadius() * 2 >= rectangle.getPosition().x + rectangle.getSize().x ||
            circle_position.x <= rectangle.getPosition().x)
        {
            x_delta *= -1;
        }

        if (circle_position.y + circle.getRadius() * 2 >= rectangle.getPosition().y + rectangle.getSize().y ||
            circle_position.y <= rectangle.getPosition().y)
        {
            y_delta *= -1;
        }

        circle.setPosition(circle_position);

        window.clear(sf::Color::White);
        window.draw(rectangle);
        window.draw(circle);
        window.display();
    }

    return 0;
}



       