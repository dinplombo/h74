#include "ui.hpp"

#include <sstream> //stringstream
#include <iostream> //stringstream

namespace araknoid {
sf::Font font;

void display_score(sf::RenderWindow& a_window, size_t a_score)
{
    font.loadFromFile("assets/signpainter-housescript_0-webfont.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setPosition(20, 40);
    text.setString("Score: " + std::to_string(a_score));
    a_window.draw(text);
}

void display_souls(sf::RenderWindow& a_window, int a_souls)
{
    font.loadFromFile("assets/signpainter-housescript_0-webfont.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setPosition(20, 80);
    text.setString("Souls: " + std::to_string(a_souls));
    a_window.draw(text);
}

void display_game_over(sf::RenderWindow& a_window)
{ 
    font.loadFromFile("assets/signpainter-housescript_0-webfont.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Red);
    text.setPosition(600, 400);
    text.setString("Game Over");
    a_window.draw(text);
}

void display_you_win(sf::RenderWindow& a_window)
{
    font.loadFromFile("assets/signpainter-housescript_0-webfont.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Green);
    text.setPosition(600, 400);
    text.setString("You Win!");
    a_window.draw(text);
}

sf::Sprite display_play(sf::RenderWindow& a_window)
{
    sf::Texture t_play;
    !t_play.loadFromFile("assets/play1.jpeg");
    sf::Sprite sprite_play(t_play);
    sprite_play.setPosition(800, 350);
    sprite_play.setScale(0.5, 0.5);
    a_window.draw(sprite_play);
    return sprite_play;
}

sf::Sprite display_quit(sf::RenderWindow& a_window)
{
    sf::Texture t_play;
    !t_play.loadFromFile("assets/exit.jpg");
    sf::Sprite sprite_play(t_play);
    sprite_play.setPosition(800, 500);
    sprite_play.setScale(0.5, 0.5);
    a_window.draw(sprite_play);
    return sprite_play;
}

sf::Sprite display_background(sf::RenderWindow& a_window)
{
    sf::Texture t_background;
    !t_background.loadFromFile("assets/new.jpg");
    sf::Sprite sprite_background(t_background);
    sprite_background.setScale(1.05 * a_window.getSize().x / t_background.getSize().x , 1.05 * a_window.getSize().y / t_background.getSize().y);
    a_window.draw(sprite_background);
    return sprite_background;
}

sf::Sprite display_volume(sf::RenderWindow& a_window, bool a_volume_status)
{
    sf::Texture t_volume;
    if(a_volume_status){
        !t_volume.loadFromFile("assets/volume.jpeg");
    } else{
        !t_volume.loadFromFile("assets/mute.jpeg");
    }
    sf::Sprite sprite_volume(t_volume);
    sprite_volume.setPosition(a_window.getSize().x - 100, 80);
    sprite_volume.setScale(0.3, 0.3);
    a_window.draw(sprite_volume);
    return sprite_volume;
}

void display_top_ten(sf::RenderWindow& a_window, ScoreManager& a_score)
{
    font.loadFromFile("assets/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Red);
    text.setPosition(20, 20);
    std::string line;
    std::string top_ten;
    std::stringstream ss;
    a_score.load(ss);
    text.setString("Top ten:\n" + ss.str());
    a_window.draw(text);
}

void set_texture(sf::RectangleShape& a_brick, sf::Texture& a_texture, size_t a_type)
{
    switch (a_type)
    {
    case 11:
        a_texture.loadFromFile("assets/heart_brick.jpeg");
        break;
    
    case 12:
        a_texture.loadFromFile("assets/arrow.jpeg");
        break;

    case 13:
        a_texture.loadFromFile("assets/clock_brick.jpeg");
        break;

    case 14:
        a_texture.loadFromFile("assets/new_brick.jpg");
        break;

    case 15:
        a_texture.loadFromFile("assets/explode_brick.jpeg");
        break;

    
    default:
        break;
    }

    a_brick.setTexture(&a_texture);
}

void set_texture_paddle(sf::RectangleShape& a_paddle, sf::Texture& a_texture)
{
    a_paddle.setFillColor(sf::Color::White);
    a_texture.loadFromFile("assets/paddle.png");
    // sf::IntRect textureRect(0, 0, 100, 50); // Adjust the left and top values accordingly
    // a_paddle.setTextureRect(textureRect);
    a_paddle.setTexture(&a_texture);
}

} //namespace araknoid

