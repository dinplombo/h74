#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "global_varibal.hpp"

namespace araknoid {

class LevelManager {
public:
    virtual ~LevelManager() = default;

    virtual InteruptResult run(sf::RenderWindow& a_window, Player& a_player, size_t a_level_number) = 0;

protected:
    LevelManager() = default;
    LevelManager(LevelManager const& a_other) = default;
    LevelManager& operator=(LevelManager const& a_other) = default;
};

} //namespace araknoid

#endif // LEVEL_MANAGER_HPP
