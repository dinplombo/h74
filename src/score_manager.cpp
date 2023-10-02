#include "score_manager.hpp"

#include <algorithm> //sort
#include <sstream> //stringstream
#include <cstring> //strcpy
#include <iomanip> // for std::setw

namespace araknoid {

PlayerScore::PlayerScore(char const* a_name, unsigned int a_score, size_t a_time)
: m_name()
, m_score(a_score)
, m_time(a_time)
{
    strcpy(m_name, a_name);
}

void create_file(std::string const& a_file)
{
    std::ofstream file(a_file, std::ifstream::out | std::ifstream::binary);
    if (!file) {
        throw std::runtime_error("Failed to create the file.");
    } else {
        file.close();
    }
}

ScoreManager::ScoreManager(std::string const& a_file) noexcept(false)
: m_top_ten({10})
, m_file_name(a_file)
{
    std::ifstream read(a_file, std::ifstream::in | std::ifstream::binary);
    bool is_new = false;
    if (!read.is_open()) {
        read.close();
        create_file(a_file);
        is_new = true;
    } else if(!read) {
        throw std::runtime_error("Failed to open the file for loading.");
    }
    if (is_new) {
        std::ifstream read(a_file, std::ifstream::in | std::ifstream::binary);
        if (!read) {
            throw std::runtime_error("Failed to open the file for loading.");
        }
    }

    if (!is_new) {
        size_t i = 0;
        char check[sizeof(PlayerScore)];
        read.read(&check[0], sizeof(PlayerScore));
        while(!read.eof() or !read.fail())
        {   
            memcpy((void*)&m_top_ten[i], &check[0],sizeof(PlayerScore)); 
            ++i;
            read.read(&check[0], sizeof(PlayerScore));
        }
    }
}

bool ScoreManager::is_top_ten(Player & a_player)
{
    unsigned int lowest_score = m_top_ten[9].m_score;
    if (a_player.score() < lowest_score) {
        return false;
    } else if (a_player.score() == lowest_score &&  static_cast<size_t>(a_player.m_time.asMicroseconds() / 1.0e6) > m_top_ten[0].m_time) {
        return false;
    } else {
        return true;
    }
}

bool comperator(PlayerScore const& a_first, PlayerScore const& a_second)
{
    return a_first.m_score == a_second.m_score ?
                              a_first.m_time < a_second.m_time :
                              a_first.m_score > a_second.m_score;
}

void ScoreManager::add(Player const& a_player)
{
    struct PlayerScore new_score{a_player.m_name.c_str(), a_player.m_score, static_cast<size_t>(a_player.m_time.asMicroseconds() / 1.0e6)};
    m_top_ten[9] = new_score;
    std::sort(m_top_ten.begin(), m_top_ten.end(), comperator);

    std::ofstream write(m_file_name, std::ofstream::trunc | std::ofstream::binary);
    if (!write) {
        throw std::runtime_error("Failed to open the file for saving.");
    }

    size_t i = 0;
    while (m_top_ten[i].m_score != 0 && i < 10)   {
        write.write((char*)(&m_top_ten[i]), sizeof(PlayerScore));
        ++i;
    }

    write.close();
}

void ScoreManager::load(std::stringstream& a_line)
{
    for (auto player : m_top_ten)
    {
        if (player.m_score == 0)
        {
            continue;
        }
        a_line <<  "name: "  << player.m_name <<  " | score: " <<  player.m_score << " | time: " << player.m_time << '\n';
    }
}

size_t ScoreManager::size() const
{
    return m_top_ten.size();
}

} //araknoid