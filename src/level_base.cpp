#include "level_base.hpp"

#include "collision_manager.hpp"
#include "ui.hpp"
#include <stdexcept>

namespace araknoid
{

LevelBase::LevelBase(std::string const &a_file_name) noexcept
: m_bricks{a_file_name}
, m_ball{}
, m_paddle{}
, m_clock{}
{
}

namespace
{

InteruptResult check_interupt(sf::Event &a_event, Ball &a_ball,
                                bool &a_game_start, LevelBase &a_level, Music& a_music)
{
    if (a_event.type == sf::Event::Closed || (a_event.type == sf::Event::KeyReleased &&
                                                a_event.key.code == sf::Keyboard::Escape)){
        return InteruptResult::ESC;
    }

    if (a_event.type == sf::Event::KeyReleased && a_event.key.code == sf::Keyboard::K) {
        return InteruptResult::WIN;
    }

    if ((a_event.type == sf::Event::KeyReleased && a_event.key.code == sf::Keyboard::Space) && a_game_start == false){
        a_game_start = true;
        a_ball.kick_start();
        a_level.restart_clock();
        return InteruptResult::KEEP_PLAY;
    }

    if (a_event.type == sf::Event::KeyReleased && a_event.key.code == sf::Keyboard::Space){
        a_ball.toggle_pause();
        return InteruptResult::KEEP_PLAY;
    }
    if (a_event.type == sf::Event::KeyReleased && a_event.key.code == sf::Keyboard::Q){
        a_music.toggle_volume();
        return InteruptResult::KEEP_PLAY;
    }
    return InteruptResult::KEEP_PLAY;
}

InteruptResult is_bricks_zero(Bricks &a_bricks, sf::RenderWindow &a_window)
{
    if (a_bricks.size() == 0)
    {
        display_you_win(a_window);
        a_window.display();
        sf::sleep(sf::seconds(2));
        return InteruptResult::WIN;
    }
    return InteruptResult::KEEP_PLAY;
}

void is_ball_fall(sf::RenderWindow &a_window, Paddle &a_paddle, Ball &a_ball, Player &a_player, bool &a_game_start,
                    sf::Vector2f a_reset_ball_position, sf::Vector2f reset_paddle_position)
{
    if (a_ball.get_postion().y > a_window.getSize().y){
        a_ball.set_position(a_reset_ball_position);
        a_paddle.set_position(reset_paddle_position);
        a_ball.pause();
        a_player.kill_soul();
        a_paddle.reset_legnth();
        a_game_start = false;
    }
}

InteruptResult is_player_dead(Player &a_player, sf::RenderWindow &a_window)
{
    if (a_player.souls() == 0){
        display_game_over(a_window);
        a_window.display();
        sf::sleep(sf::seconds(2));
        return InteruptResult::GAME_OVER;
    }
    return InteruptResult::KEEP_PLAY;
}

void draw_window(sf::RenderWindow &a_window, Paddle &a_paddle, Ball &a_ball, Player &a_player, Bricks &a_bricks, Music& a_music)
{
    sf::Sprite volume;
    a_window.clear();
    a_ball.draw(a_window);
    a_paddle.draw(a_window);
    a_bricks.draw(a_window);
    display_score(a_window, a_player.score());
    display_souls(a_window, a_player.souls());
    volume = display_volume(a_window, a_music.volume());
    a_window.display();
}

void check_collision(sf::RenderWindow &a_window, Paddle &a_paddle, Ball &a_ball, Player &a_player,
                        Bricks &a_bricks, size_t a_level_number, Music& a_music)
{
    paddle_collision(a_ball, a_paddle);
    window_collision(a_ball, a_window);
    unsigned int score = brick_collision(a_ball, a_bricks, a_level_number, a_player, a_paddle);
    if (score != 0){
        a_music.play_hit_brick_sound();
        a_player.raise_score(score);
    }
}

} // namespace

InteruptResult LevelBase::run(sf::RenderWindow &a_window, Player &a_player, size_t a_level_number)
{
    bool game_start = false;
    m_bricks.set_bricks(a_window);
    sf::Vector2f middle_position((a_window.getSize().x / 2), (a_window.getSize().y / 2));
    sf::Vector2f paddle_position(middle_position.x - m_paddle.get_size().x / 2, a_window.getSize().y - 50);
    sf::Vector2f reset_paddle_position = paddle_position;
    m_paddle.set_position(paddle_position);
    float ball_radius = m_ball.get_radius();
    sf::Vector2f ball_position(middle_position.x - ball_radius, m_paddle.get_postion().y - ball_radius * 2);
    sf::Vector2f reset_ball_position = ball_position;
    m_ball.set_position(ball_position);
    InteruptResult interupt_result;

    Music music;
    music.play_backgroud_music();
    while (a_window.isOpen())
    {
        sf::Event interupt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_paddle.get_postion().x > 0){
        m_paddle.move_left();
        if (!game_start)
        {
            m_ball.move_ball_with_paddle(m_paddle);
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_paddle.get_postion().x + m_paddle.get_size().x < a_window.getSize().x){
        m_paddle.move_right();
        if (!game_start){
            m_ball.move_ball_with_paddle(m_paddle);
        }
    }
        while (a_window.pollEvent(interupt)){
            interupt_result = check_interupt(interupt, m_ball, game_start, *this, music);
            if (interupt_result == InteruptResult::KEEP_PLAY){
                break;
            } else {
                return interupt_result;
            }
        }

        if (is_bricks_zero(m_bricks, a_window) == InteruptResult::WIN){
            a_player.time(get_elapsed_time());
            music.stop_backgroud_music();
            sf::sleep(sf::seconds(1));
            music.play_win_sound();
            sf::sleep(sf::seconds(3));
            return InteruptResult::WIN;
        }
        if (is_player_dead(a_player, a_window) == InteruptResult::GAME_OVER){
            a_player.time(get_elapsed_time());
            music.stop_backgroud_music();
            sf::sleep(sf::seconds(1));
            music.play_gameover_sound();
            sf::sleep(sf::seconds(3));
            return InteruptResult::GAME_OVER;
        }
        is_ball_fall(a_window, m_paddle, m_ball, a_player, game_start, reset_ball_position, reset_paddle_position);

        m_ball.move();
        ball_position = m_ball.get_postion();
        check_collision(a_window, m_paddle, m_ball, a_player, m_bricks, a_level_number, music);
        draw_window(a_window, m_paddle, m_ball, a_player, m_bricks, music);
    }
    music.stop_backgroud_music();
    return interupt_result;
}

void LevelBase::restart_clock()
{
    m_clock.restart();
}

sf::Time LevelBase::get_elapsed_time()
{
    return m_clock.getElapsedTime();
}

} // namespace araknoid