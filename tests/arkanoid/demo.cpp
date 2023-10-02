#include "level_base.hpp"
#include "player.hpp"
#include "ui.hpp"
#include "window_topten.hpp"
#include "window_opening.hpp"
#include "global_varibal.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace araknoid;

namespace {
std::vector<LevelBase> initlize_levels()
{
    std::vector<LevelBase> levels;
    levels.emplace_back("assets/level_special.dat");
    levels.emplace_back("assets/level_explose.dat");
    levels.emplace_back("assets/Level-3.dat");
    levels.emplace_back("assets/Level-1.dat");
    levels.shrink_to_fit();
    return levels;
}

} //namespace

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "demo!");
    window.setFramerateLimit(64);
    WindowOpening window_opening{window};
    InteruptResult run_result = InteruptResult::KEEP_PLAY;
    while(true) {
        size_t levels_number = 0;
        auto levels = initlize_levels();
        Player player;
        WindowTopTen window_top_ten{window, player};
        if(window_opening.open()){
            while(true){
                if (levels_number < levels.size()){
                    run_result = levels[levels_number].run(window, player, levels_number);
                }
                if(run_result == InteruptResult::ESC){
                    return 0;  
                } else {
                    if( run_result == InteruptResult::GAME_OVER || levels_number == levels.size()){
                        if(!window_top_ten.open()){
                            break;
                        }
                    }   
                    if(run_result == InteruptResult::WIN){
                        ++levels_number;
                        continue;
                    } 
                }
            }
        } else {
            break;
        }
    }

    return 0;
}

