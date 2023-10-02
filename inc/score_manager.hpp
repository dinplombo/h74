#ifndef SCORE_MANAGER_HPP
#define SCORE_MANAGER_HPP

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <fstream>

#include <cstddef> //size_t

#include "player.hpp"

namespace araknoid {

struct PlayerScore {
PlayerScore() = default;
PlayerScore(char const* a_name, unsigned int a_score, size_t a_time);

char m_name[32];
unsigned int m_score;
size_t m_time; 
};

class ScoreManager {
public:
    ScoreManager(std::string const& a_file) noexcept(false);
    ~ScoreManager() noexcept = default;

    bool is_top_ten(Player & a_player) ;
    void add(Player const& a_player);
    size_t size() const;
    void load(std::stringstream& a_line);

public:
    std::vector<PlayerScore> m_top_ten;
    std::string m_file_name;
};

} //namespace araknoid

#endif // SCORE_MANAGER_HPP

