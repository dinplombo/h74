#include "ball.hpp"

#include <cmath> //cos sin

namespace araknoid {

Ball::Ball() noexcept
: m_velocity(0 , 0)
, m_circle(6)
, m_pause(false)
, m_slowed(false)
{
    m_circle.setFillColor(sf::Color::Red);
}

void Ball::kick_start()
{
    std::srand(std::time(0));

    float min_angle = 60.0f;
    float max_angle = 120.0f;
    float random_angle = static_cast<float>(std::rand()) / RAND_MAX * (max_angle - min_angle) + min_angle;
    float radian_angle = random_angle * 3.14 / 180.0;

    float ballSpeed = 11.0f; 
    m_velocity.x = ballSpeed * std::cos(radian_angle);
    m_velocity.y = -ballSpeed * std::sin(radian_angle);
}

void Ball::pause()
{
    m_velocity.x = 0;
    m_velocity.y = 0;
}

void Ball::move()
{
    if (!m_pause){
        if (m_slowed){
            if (m_slowdown_timer.getElapsedTime().asSeconds() >= 10.0f) {
                m_velocity *= 2.0f;
                m_slowed = false; 
            }
        }
        m_circle.move(m_velocity.x, m_velocity.y);
    }
}

void Ball::move_ball_with_paddle(Paddle& a_paddle)
{
    sf::Vector2f ballPosition(a_paddle.get_postion().x + a_paddle.get_size().x / 2.0f - m_circle.getRadius(),
    a_paddle.get_postion().y - 2.0f * m_circle.getRadius()); 
    m_circle.setPosition(ballPosition);
}

float Ball::get_radius() const noexcept
{
    return m_circle.getRadius();
}

void Ball::set_position(sf::Vector2f a_position)
{
    m_circle.setPosition(a_position);
}

void Ball::draw(sf::RenderWindow& a_window)
{
    a_window.draw(m_circle);
}

sf::FloatRect Ball::get_global_bounds() const noexcept
{
    return m_circle.getGlobalBounds();
}

sf::Vector2f Ball::get_postion() const noexcept
{
    return m_circle.getPosition();
}

void Ball::set_velocity(float a_x, float a_y)
{
    m_velocity.x *= a_x;
    m_velocity.y *= a_y;
}

void Ball::toggle_pause()
{
    m_pause = !m_pause;
}

void Ball::slow_down_ball()
{
    if (!m_slowed) {
        m_velocity *= 0.5f;
        m_slowed = true;
        m_slowdown_timer.restart();
    }
}

} //namespace araknoid
