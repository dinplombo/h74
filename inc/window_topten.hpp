#ifndef WINDOW_TOPTEN_HPP
#define WINDOW_TOPTEN_HPP

#include "player.hpp"
#include "global_varibal.hpp"
#include "ui.hpp"
#include "window_manager.hpp"

#include <SFML/Graphics.hpp>

namespace araknoid {

class WindowTopTen : public WindowManager{
public:
    explicit WindowTopTen(sf::RenderWindow& a_window, Player& a_player);
    ~WindowTopTen() noexcept = default;

    bool open() override;

private:
    sf::RenderWindow& m_window;
    Player& m_player;
};

} //namespace araknoid

#endif // WINDOW_TOPTEN_HPP
