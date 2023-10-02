#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

namespace araknoid {

class Paddle {
public:
    Paddle() noexcept;
    ~Paddle() noexcept = default; 

    void move_left(); 
    void move_right(); 
    void set_position(sf::Vector2f a_position);
    void draw(sf::RenderWindow& a_window);
    void double_length();
    void reset_legnth();
    
    sf::Vector2f get_postion() const noexcept;
    sf::Vector2f get_size() const noexcept;
    sf::FloatRect get_global_bounds() const noexcept;

private:
    sf::RectangleShape m_paddle;
    bool m_double_length;
};

} //namespace araknoid

#endif // PADDLE_HPP
