#ifndef BRICKS_HPP
#define BRICKS_HPP

#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "paddle.hpp"
#include "ball.hpp"

#include <cstddef>
#include <vector>
#include <string>
#include <map>
#include <utility> //pair

namespace araknoid {

struct BrickInfo {
    BrickInfo();
    BrickInfo(std::string a_type, sf::Color a_color,  unsigned int a_score, int a_lives, int a_radius,
    sf::RectangleShape a_rectangle);

    std::string m_type;
    sf::Color m_color;
    unsigned int m_score;
    int m_lives;
    int m_radius;
    sf::RectangleShape m_rectangle;
};

class Bricks {
public:
    Bricks(std::string const& a_file_name);
    ~Bricks() noexcept = default;

    void draw(sf::RenderWindow& a_window);
    void set_bricks(sf::RenderWindow& a_window);
    unsigned int erase(std::vector<sf::RectangleShape>::iterator& brick_itr);
    size_t size() const;
    void sign_bricks_to_remove(sf::RectangleShape& a_brick);
    
    std::vector<sf::RectangleShape>::iterator begin();
    std::vector<sf::RectangleShape>::iterator end();

private:
    void build_bricks_type();
    std::vector<int> build_bricks_matrix();

private:
    std::vector<sf::RectangleShape> m_bricks;
    std::string m_file_name;
    std::map<int, BrickInfo> m_brick_info;
    std::vector<BrickInfo> m_id_bricks;
    size_t m_counter_indestrutible_bricks;
};

} //namespace araknoid

#endif // BRICKS_HPP
