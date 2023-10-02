#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

#include "paddle.hpp"

namespace araknoid {

class Ball {
public:
    Ball() noexcept;
    ~Ball() noexcept = default; 

    void kick_start();
    void pause();
    void move();
    void move_ball_with_paddle(Paddle& a_paddle);

    void set_position(sf::Vector2f a_position);
    void draw(sf::RenderWindow& a_window);
    void set_velocity(float a_x, float a_y);
    void toggle_pause();
    void slow_down_ball();

    float get_radius() const noexcept;
    sf::FloatRect get_global_bounds() const noexcept;
    sf::Vector2f get_postion() const noexcept;

private:
    sf::Vector2f m_velocity; 
    sf::CircleShape m_circle;
    bool m_pause;
    bool m_slowed; 
    sf::Clock m_slowdown_timer;
};

} //namespace araknoid

#endif // BALL_HPP

