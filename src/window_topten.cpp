#include "window_topten.hpp"

#include <iostream>
#include "score_manager.hpp"

namespace araknoid {

WindowTopTen::WindowTopTen(sf::RenderWindow& a_window, Player& a_player)
: m_window{a_window}
, m_player{a_player}
{
}

bool WindowTopTen::open(){
    ScoreManager score_manager("assets/top10.dat");
    std::string name;
    if (score_manager.is_top_ten(m_player) || score_manager.size() < 10) {
        sf::Font font;
        if (!font.loadFromFile("assets/arial.ttf")) {
            return false;
        }

        sf::Text message;
        message.setFont(font);
        message.setCharacterSize(30);
        message.setFillColor(sf::Color::White);
        message.setString("You are in the 'Top 10'!\n Enter your name (up to 16 characters): ");

        sf::Text inputText;
        inputText.setFont(font);
        inputText.setCharacterSize(25);
        inputText.setFillColor(sf::Color::White);

        bool showCursor = true;
        sf::Clock cursorTimer;
        bool top_ten = true;
        while (m_window.isOpen()) {
            m_window.clear();
            if(top_ten){
                display_top_ten(m_window, score_manager);
                m_window.display();
                top_ten = false;
                sf::sleep(sf::seconds(7));
            }
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_window.close();
                    return false;
                }

                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128 && event.text.unicode != '\r') {
                        if (event.text.unicode == '\b' && !name.empty()) {
                            name.pop_back();
                        } else if (name.size() < 16) {
                            name += static_cast<char>(event.text.unicode);
                        }
                    }
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    if (!name.empty()) {
                        m_player.name(name);
                        score_manager.add(m_player);
                        return false;
                    }
                }
            }

            m_window.clear();
            m_window.draw(message);
            inputText.setString(name);
            inputText.setFillColor(sf::Color::Green);
            inputText.setPosition(10, 70); 
            m_window.draw(inputText);

            if (cursorTimer.getElapsedTime().asSeconds() >= 0.5) {
                showCursor = !showCursor;
                cursorTimer.restart();
            }
            if (showCursor && name.size() < 16) {
                sf::Text cursor;
                cursor.setFont(font);
                cursor.setCharacterSize(20);
                cursor.setFillColor(sf::Color::White);
                cursor.setString("_");
                cursor.setPosition(inputText.getPosition().x + inputText.getLocalBounds().width, inputText.getPosition().y);
                m_window.draw(cursor);
            }

            m_window.display();
        }
    }

    return false;
}

} //namespace araknoid