#include "player.hpp"

namespace araknoid {

Player::Player(int a_souls) noexcept
: m_souls(a_souls)
, m_score{}
, m_time{}
{
}

void Player::kill_soul() noexcept 
{
    m_souls -= 1;
}

int Player::souls() const noexcept
{
    return m_souls;
}

void Player::raise_score(size_t a_score) noexcept
{
    m_score += a_score;
}

void Player::add_souls() noexcept
{
    m_souls += 1;
}

size_t Player::score() const noexcept
{
    return m_score;
}

void Player::name(std::string& a_name)
{
    m_name = a_name;
}

void Player::time(sf::Time const& a_time)
{
    m_time = a_time;
}

} //namespace araknoid