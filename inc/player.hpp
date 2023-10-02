#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include <cstddef> //size_t
#include <string>

namespace araknoid {

class Player {
public:
    explicit Player(int a_souls = 2) noexcept;
    ~Player() noexcept = default; 

    void kill_soul() noexcept;
    void raise_score(size_t a_score) noexcept;
    void name(std::string& a_name);
    void time(sf::Time const& a_time);
    int souls() const noexcept;
    size_t score() const noexcept; 
    void add_souls() noexcept;

    friend class ScoreManager;

private:
    int m_souls; 
    unsigned int m_score;
    sf::Time m_time;
    std::string m_name;
};

} //namespace araknoid

#endif // PLAYER_HPP
