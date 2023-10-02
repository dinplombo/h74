#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>

namespace araknoid {

class Music {
public:
    Music();
    ~Music() noexcept = default;

    void play_backgroud_music();
    void stop_backgroud_music();
    void play_win_sound();
    void play_hit_brick_sound();
    void play_gameover_sound();
    void toggle_volume();
    bool volume() const;

private:
    bool m_volume;
    sf::Music m_backgroud_music;
    sf::SoundBuffer m_win_buffer;
    sf::Sound m_win_sound;
    sf::Sound m_lose_sound;
    sf::SoundBuffer m_lose_buffer;
    sf::SoundBuffer m_hit_buffer;
    sf::Sound m_hit_sound;
};

} //namespace araknoid

#endif // WINDOW_OPENING_HPP
