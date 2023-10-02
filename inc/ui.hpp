#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>

#include "level_base.hpp"
#include "score_manager.hpp"

namespace araknoid {

void display_score(sf::RenderWindow& a_window, size_t a_score);
void display_game_over(sf::RenderWindow& a_window);
void display_you_win(sf::RenderWindow& a_window);
void display_top_ten(sf::RenderWindow& a_window, ScoreManager& a_score);
void display_score(sf::RenderWindow& a_window, int a_score);
void display_souls(sf::RenderWindow& a_window, int a_souls);
void set_texture(sf::RectangleShape& a_brick, sf::Texture& texture, size_t a_type);
void set_texture_paddle(sf::RectangleShape& a_paddle, sf::Texture& a_texture);

sf::Sprite display_background(sf::RenderWindow& a_window);
sf::Sprite display_play(sf::RenderWindow& a_window);
sf::Sprite display_quit(sf::RenderWindow& a_window);
sf::Sprite display_volume(sf::RenderWindow& a_window, bool a_volume_status);


} //namespace araknoid

#endif // UI_HPP
