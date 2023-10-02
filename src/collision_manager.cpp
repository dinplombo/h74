#include "collision_manager.hpp"

#include <iostream>

namespace araknoid {

void paddle_collision(Ball& a_ball, Paddle& a_paddle)
{
    if (a_ball.get_global_bounds().intersects(a_paddle.get_global_bounds())) {
        if(a_ball.get_postion().y < a_paddle.get_postion().y && a_ball.get_postion().x > a_paddle.get_postion().x
        &&  a_ball.get_postion().x < a_paddle.get_postion().x + a_paddle.get_size().x){
            a_ball.set_velocity(1.0f, -1.0f);
        }else if(a_ball.get_postion().y < a_paddle.get_postion().y){
            a_ball.set_velocity(1.0f, -1.0f);
        } else{
            a_ball.set_velocity(-1.0f, 1.0f);
        }
    }
}

void window_collision(Ball& a_ball, sf::RenderWindow& a_window)
{
    if (a_ball.get_postion().x <= 0 || a_ball.get_postion().x >= a_window.getSize().x - a_ball.get_radius()*2) {
            a_ball.set_velocity(-1.0f,1.0f);
        }
    if (a_ball.get_postion().y <= 0) {
        a_ball.set_velocity(1.0f,-1.0f);
    }
}

namespace{

void special_bricks(size_t a_level_number, unsigned int& a_score, Player& a_player,Paddle& a_paddle, Ball& a_ball)
{
    switch (a_score)
    {
    case 10:
        a_ball.slow_down_ball();
        break;
    case 20:
        a_paddle.double_length();
        break;
    case 30:
        a_player.add_souls();
        break;
    case 40:
        a_score *= a_level_number;
        break;
    
    default:
        break;
    }

}
} //namespace

unsigned int brick_collision(Ball& a_ball, Bricks& a_brick, size_t a_level_number, Player& a_player, Paddle& a_paddle)
{
    auto next_brick = a_brick.begin();
    auto end_itr = a_brick.end();
    sf::FloatRect ball_bounds = a_ball.get_global_bounds();
    unsigned int score;
    while (next_brick != end_itr) {
        sf::FloatRect brick_bounds = (*next_brick).getGlobalBounds();
        if (ball_bounds.intersects(brick_bounds)) {
            if (ball_bounds.top <= brick_bounds.top + brick_bounds.height && ball_bounds.top > brick_bounds.top + 0.25 * brick_bounds.height \
            && ball_bounds.left + a_ball.get_radius() >= brick_bounds.left \
            && ball_bounds.left + a_ball.get_radius() <= brick_bounds.left + brick_bounds.width) {
                a_ball.set_velocity(1, -1);
                score = a_brick.erase(next_brick);
                special_bricks(a_level_number, score, a_player, a_paddle, a_ball);
                return score;
            }
            if (ball_bounds.top + ball_bounds.height >= brick_bounds.top \
            && ball_bounds.left + a_ball.get_radius() >= brick_bounds.left \
            && ball_bounds.left + a_ball.get_radius() <= brick_bounds.left + brick_bounds.width) {
                a_ball.set_velocity(1, -1);
                score = a_brick.erase(next_brick);
                special_bricks(a_level_number, score, a_player, a_paddle, a_ball);
                return score;
            }
            if (ball_bounds.left <= brick_bounds.left + brick_bounds.width && ball_bounds.left > brick_bounds.left + 0.25 * brick_bounds.width\
            && ball_bounds.top + a_ball.get_radius() >= brick_bounds.top \
            && ball_bounds.top + a_ball.get_radius() <= brick_bounds.top + brick_bounds.height) {
                a_ball.set_velocity(-1, 1);
                score = a_brick.erase(next_brick);
                special_bricks(a_level_number, score, a_player, a_paddle, a_ball);
                return score;
            }
            if (ball_bounds.left + ball_bounds.width >= brick_bounds.left\
            && ball_bounds.top + a_ball.get_radius() >= brick_bounds.top \
            && ball_bounds.top + a_ball.get_radius() <= brick_bounds.top + brick_bounds.height) {
                a_ball.set_velocity(-1, 1);
                score = a_brick.erase(next_brick);
                special_bricks(a_level_number, score, a_player, a_paddle, a_ball);
                return score;
            }
        }
        ++next_brick;
    }
    return 0;
}

} //namespace araknoid
