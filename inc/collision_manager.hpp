#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include <SFML/Graphics.hpp>

#include "ball.hpp"
#include "paddle.hpp"
#include "bricks.hpp"
#include "player.hpp"

namespace araknoid {

void paddle_collision(Ball& a_ball, Paddle& a_paddle);
void window_collision(Ball& a_ball, sf::RenderWindow& a_window);
unsigned int brick_collision(Ball& a_ball, Bricks& a_brick, size_t a_level_number, Player &a_player, Paddle& a_paddle);

} //namespace araknoid

#endif // COLLISION_MANAGER_HPP