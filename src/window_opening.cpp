#include "window_opening.hpp"

#include <iostream>

namespace araknoid {

WindowOpening::WindowOpening(sf::RenderWindow& a_window)
: m_window{a_window}
{
}

namespace {

bool check_interupt(sf::Event& a_event, sf::RenderWindow& a_window, sf::Sprite& a_sprite_play, sf::Sprite& a_sprite_quit)
{
    while (true){
        a_window.pollEvent(a_event);
        if (a_event.type == sf::Event::Closed || (a_event.type == sf::Event::KeyReleased && 
            a_event.key.code == sf::Keyboard::Escape)){
            return false;
        }
        if (a_event.type == sf::Event::MouseButtonReleased) {
            if (a_event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse_position = sf::Mouse::getPosition(a_window);
                sf::FloatRect play_bounds = a_sprite_play.getGlobalBounds();
                if (play_bounds.contains(mouse_position.x, mouse_position.y)) {
                    return true;
                }

                sf::FloatRect quit_bounds = a_sprite_quit.getGlobalBounds();
                if (quit_bounds.contains(mouse_position.x, mouse_position.y)) {
                    a_window.close();
                    return false;
                }
            }
        }
        continue;
    }
    return false;
}

} //namespace

bool WindowOpening::open()
{
    sf::Sprite sprite_play;
    sf::Sprite sprite_quit; 
    sf::Sprite sprite_background; 
    while (m_window.isOpen()){
        m_window.clear();
        sprite_background = display_background(m_window);
        sprite_play = display_play(m_window);
        sprite_quit = display_quit(m_window);
        m_window.display();

        sf::Event interupt;
        return check_interupt(interupt, m_window, sprite_play, sprite_quit);
    }
    return false;
}

} //namespace araknoid