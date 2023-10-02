#ifndef LEVLE_BASE_HPP
#define LEVLE_BASE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cstddef>

#include "level_manager.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "player.hpp"
#include "music.hpp"
#include "bricks.hpp"
#include "global_varibal.hpp"

namespace araknoid {

class LevelBase : public LevelManager {
public:
    LevelBase(std::string const& a_file_name) noexcept;
    ~LevelBase() = default;

    InteruptResult run(sf::RenderWindow& a_window, Player& a_player, size_t a_level_number) override;
    void restart_clock();
    sf::Time get_elapsed_time();

private:
    Bricks m_bricks;
    Ball m_ball;
    Paddle m_paddle;
    sf::Clock m_clock;
};

} //namespace araknoid

#endif // LEVLE_BASE_HPP
