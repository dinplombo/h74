#include "bricks.hpp"
#include "ui.hpp"

#include <nlohmann/json.hpp>

#include <sstream> //stringstream
#include <fstream> //ifstream
#include <iostream> //ifstream

namespace araknoid {
sf::Texture texture1;
sf::Texture texture2;
sf::Texture texture3;
sf::Texture texture4;
sf::Texture texture5;

BrickInfo::BrickInfo()
: m_type{}
, m_color{}
, m_score{}
, m_lives{}
, m_radius{}
, m_rectangle{}
{
}

BrickInfo::BrickInfo(std::string a_type, sf::Color a_color,  unsigned int a_score, int a_lives, int a_radius, sf::RectangleShape a_rectangle)
: m_type{a_type}
, m_color{a_color}
, m_score{a_score}
, m_lives{a_lives}
, m_radius{a_radius}
, m_rectangle{a_rectangle}
{
}

Bricks::Bricks(std::string const& a_file_name)
: m_bricks{}
, m_file_name{a_file_name}
, m_brick_info{}
, m_id_bricks{}
, m_counter_indestrutible_bricks{}
{
}

void Bricks::draw(sf::RenderWindow& a_window)
{
    for (auto& brick : m_bricks){
        a_window.draw(brick);
    }
}

std::vector<sf::RectangleShape>::iterator Bricks::begin()
{
    return m_bricks.begin();
}

std::vector<sf::RectangleShape>::iterator Bricks::end()
{
    return m_bricks.end();
}

namespace{

bool check_explosion_radius(sf::RectangleShape const& a_lhs, sf::Vector2f a_rhs_center, int a_ratio_explosion)
{
    sf::Vector2f lhs_center = a_lhs.getPosition() + sf::Vector2f(a_lhs.getSize().x / 2.0f, a_lhs.getSize().y / 2.0f);
    float distance = std::sqrt(std::pow(a_rhs_center.x - lhs_center.x, 2) + std::pow(a_rhs_center.y - lhs_center.y, 2));
    float explosion_radius = a_lhs.getSize().x  *1.2* a_ratio_explosion;
    return distance <= explosion_radius;
}

unsigned int special_bricks(BrickInfo& a_brick)
{
    if (std::stoi(a_brick.m_type) == 13){
        return 10;
    }
    if (std::stoi(a_brick.m_type) == 12){
        return 20;
    }
    if (std::stoi(a_brick.m_type) == 11){
        return 30;
    }
    if (std::stoi(a_brick.m_type) == 2){
        return 40;
    }
    return 0;
}

void special_texture(size_t a_type, sf::RectangleShape& a_new_brick)
{
    switch (a_type)
    {
    case 11:
        a_new_brick.setFillColor(sf::Color::White);
        set_texture(a_new_brick, texture1, a_type);
        break;
    
    case 12:
        a_new_brick.setFillColor(sf::Color::White);
        set_texture(a_new_brick, texture2, a_type);
        break;

    case 13:
        a_new_brick.setFillColor(sf::Color::White);
        set_texture(a_new_brick, texture3, a_type);
        break;

    case 14:
        a_new_brick.setFillColor(sf::Color::White);
        set_texture(a_new_brick, texture4, a_type);
        break;

    case 15:
        a_new_brick.setFillColor(sf::Color::White);
        set_texture(a_new_brick, texture5, a_type);
        break;

    
    default:
        break;
    }
}

} //namespace

void Bricks::sign_bricks_to_remove(sf::RectangleShape& a_brick)
{
    for (auto& brick : m_id_bricks){
        if (brick.m_rectangle.getPosition() == (a_brick).getPosition()){
            if (brick.m_lives > 0){
                --brick.m_lives;
                if (std::stoi(brick.m_type) > 14 && brick.m_lives == 0){
                    sf::Vector2f rhs_center = (a_brick).getPosition() + sf::Vector2f((a_brick).getSize().x / 2.0f, (a_brick).getSize().y / 2.0f);
                    
                    for(auto& brick_explode : m_bricks) {
                        if(check_explosion_radius(brick_explode, rhs_center, brick.m_radius)){
                            sign_bricks_to_remove(brick_explode);
                        }

                    }
                }
            }
        }
    }
}

unsigned int Bricks::erase(std::vector<sf::RectangleShape>::iterator& brick_itr)
{
    unsigned int score = 0;
    sign_bricks_to_remove(*brick_itr); 

    for(auto& erase_brick : m_id_bricks){
        if(erase_brick.m_lives == 0 && erase_brick.m_color != sf::Color(255,255,0)){
           auto next_brick = m_bricks.begin(); 

           while(next_brick != m_bricks.end()){
                if (erase_brick.m_rectangle.getPosition() == (*next_brick).getPosition()){
                    score += special_bricks(erase_brick);
                    score += erase_brick.m_score;
                    m_bricks.erase(next_brick);
                }else{
                    ++next_brick;
                }
           }
        }
    }
    return score;
}

size_t Bricks::size() const
{
    return m_bricks.size() - m_counter_indestrutible_bricks;
}

void Bricks::build_bricks_type()
{   
    std::ifstream file("assets/special_brick.json");
    if (!file) {
        throw std::runtime_error("file not open");
    }

    nlohmann::json json_data = nlohmann::json::parse(file);

    for(auto it =  json_data.begin(); it != json_data.end(); ++it){
        BrickInfo brick_type;
        brick_type.m_type = it.key();
        int int_type = std::stoi(brick_type.m_type);
        brick_type.m_color = sf::Color(it.value()["color"][0], it.value()["color"][1], it.value()["color"][2]);
        brick_type.m_score = it.value()["value"];
        brick_type.m_lives = it.value()["lives"];
        if (int_type > 14){
            brick_type.m_radius = it.value()["radius"];
        }

        m_brick_info.insert(std::pair<int, BrickInfo>(int_type, brick_type));
    } 
}

std::vector<int> Bricks::build_bricks_matrix()
{   
    std::ifstream file(m_file_name);
    if (!file) {
        throw std::runtime_error("file not open");
    }

    nlohmann::json json_data = nlohmann::json::parse(file);
    std::vector<int> matrix = json_data["matrix"];
    return matrix;
}
    
void Bricks::set_bricks(sf::RenderWindow& a_window)
{
    size_t row = 10;
    size_t coulmn = 10;
    sf::Vector2f brick_size(60, 30);
    float brickWidth = brick_size.x;
    float brickHeight = brick_size.y;
    float offset = 1.f;
    float totalWidth = coulmn * brickWidth + (coulmn - 1) * offset;
    float startX = (a_window.getSize().x - totalWidth) / 2;
    float startY = 10.f;

    std::vector<int> bricks_matrix = build_bricks_matrix();
    build_bricks_type();
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < coulmn; ++j) {
            size_t type = bricks_matrix[j + i * coulmn];
            if (type == 1){
                ++m_counter_indestrutible_bricks;
            }
            if (type > 0 && type < 17){
                sf::RectangleShape new_brick{brick_size};
                new_brick.setOutlineColor(sf::Color::Black);
                sf::Vector2f brick_position(startX + offset + j * (brickWidth + offset),
                    startY + offset + i * (brickHeight + offset));
                new_brick.setPosition(brick_position);
                new_brick.setFillColor(m_brick_info[type].m_color);
                if (10 < type && type < 16){
                    special_texture(type, new_brick);
                }
                m_bricks.push_back(new_brick);
                BrickInfo id_brick{m_brick_info[type].m_type, m_brick_info[type].m_color, m_brick_info[type].m_score,
                 m_brick_info[type].m_lives, m_brick_info[type].m_radius, new_brick};
                m_id_bricks.push_back(id_brick);
            }
        }
    }
}

} //namespace araknoid


