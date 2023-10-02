#include "paddle.hpp"

#include "ui.hpp"

namespace araknoid {
sf::Texture texture_paddle;

Paddle::Paddle() noexcept
: m_double_length{false}
{
    sf::Vector2f rectangle_size(150,12);
    m_paddle.setSize(rectangle_size);
    m_paddle.setFillColor(sf::Color::Blue);
}

void Paddle::move_left()
{
    m_paddle.move(-8, 0);
}

void Paddle::move_right()
{
    m_paddle.move(8, 0);
}

void Paddle::set_position(sf::Vector2f a_position)
{
    m_paddle.setPosition(a_position);
}

sf::Vector2f Paddle::get_postion() const noexcept
{
    return m_paddle.getPosition();
}

sf::Vector2f Paddle::get_size() const noexcept
{
    return m_paddle.getSize();
}

void Paddle::draw(sf::RenderWindow& a_window)
{
    set_texture_paddle(m_paddle, texture_paddle);
    a_window.draw(m_paddle);
}

sf::FloatRect Paddle::get_global_bounds() const noexcept
{
    return m_paddle.getGlobalBounds();
}

void Paddle::double_length()
{
    sf::Vector2f current_size = m_paddle.getSize();
    current_size.x *= 2;
    m_paddle.setSize(current_size);
    m_double_length = true;
}

void Paddle::reset_legnth()
{
    if(m_double_length){
        sf::Vector2f current_size = m_paddle.getSize();
        current_size.x *= 0.5;
        m_paddle.setSize(current_size);
        m_double_length = false;
    }
}

} //namespace araknoid