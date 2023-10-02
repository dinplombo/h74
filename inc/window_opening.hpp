#ifndef WINDOW_OPENING_HPP
#define WINDOW_OPENING_HPP

#include "ui.hpp"
#include "window_manager.hpp"

#include <SFML/Graphics.hpp>

namespace araknoid {

class WindowOpening : public WindowManager{
public:
    explicit WindowOpening(sf::RenderWindow& a_window);
    ~WindowOpening() noexcept = default;

    bool open() override;

private:
    sf::RenderWindow& m_window;
};

} //namespace araknoid

#endif // WINDOW_OPENING_HPP
