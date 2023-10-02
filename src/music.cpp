#include "music.hpp"

namespace araknoid {

Music::Music()
: m_volume{true}
{
    if (!m_backgroud_music.openFromFile("assets/file_example_WAV_1MG.wav")){
        throw std::runtime_error("file not open");
    }

    if(!m_win_buffer.loadFromFile("assets/win_sound.wav")) {
        throw std::runtime_error("file not open!");
    } else { m_win_sound.setBuffer(m_win_buffer);
    }

    if(!m_lose_buffer.loadFromFile("assets/game_over_sound.wav")) {
        throw std::runtime_error("file not open!");
    } else { m_lose_sound.setBuffer(m_lose_buffer);
    }

    if(!m_hit_buffer.loadFromFile("assets/hit_brick_sound.wav")) {
        throw std::runtime_error("file not open!");
    } else {m_hit_sound.setBuffer(m_hit_buffer);
    }
}

void Music::play_backgroud_music()
{
    m_backgroud_music.setLoop(true);
    m_backgroud_music.play();
    m_backgroud_music.setVolume(20); 
}

void Music::stop_backgroud_music()
{
    m_backgroud_music.stop();
}

void Music::play_win_sound()
{
    m_win_sound.play();
}
void Music::play_hit_brick_sound()
{
    m_hit_sound.play();
}
void Music::play_gameover_sound()
{
    m_lose_sound.play();
}

void Music::toggle_volume()
{
    float volume = m_backgroud_music.getVolume();
    if (volume > 0) {
        m_backgroud_music.setVolume(0);
        m_hit_sound.setVolume(0);
        m_lose_sound.setVolume(0);
        m_win_sound.setVolume(0);
    } else {
        m_backgroud_music.setVolume(100);
        m_hit_sound.setVolume(100);
        m_lose_sound.setVolume(100);
        m_win_sound.setVolume(100);
    }
    m_volume = !m_volume;
}

bool Music::volume() const
{
    return m_volume;
}

} //namespace araknoid