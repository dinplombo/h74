#include "mu_test.h"
#include "score_manager.hpp"
#include "player.hpp"

#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>

#include <cstddef> //size_t

using namespace araknoid;

BEGIN_TEST(add_and_save)
    std::fstream file("top10.dat", std::ios::out); 
    if (!file.is_open()) {
    std::cout << "Failed to open file!" << std::endl;
    } else {
    std::cout << "File opened successfully." << std::endl;
    }
    ScoreManager a_score(file);
    sf::Time time = sf::seconds(10);

    Player player_1;
    std::string yossi("yossi");
    player_1.time(time);
    player_1.name(yossi);
    player_1.raise_score(20);

    Player player_2;
    std::string ori("ori");
    player_2.name(ori);
    player_2.time(time);
    player_2.raise_score(20);

    a_score.add(player_1);
    a_score.add(player_2);
    a_score.save();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(load_to_string)
    std::fstream file("top10.dat");
    ScoreManager a_score(file);
    sf::Time time = sf::seconds(10);

    Player player_1;
    std::string yossi("yossi");
    player_1.time(time);
    player_1.name(yossi);
    player_1.raise_score(20);

    Player player_2;
    std::string ori("ori");
    player_2.name(ori);
    player_2.time(time);
    player_2.raise_score(20);

    a_score.add(player_1);
    a_score.add(player_2);

    std::string line_1;
    std::string line_2;
    a_score.load(line_1);
    a_score.load(line_2);
    std::cout << line_1 << '\n' << line_2 << '\n';
    ASSERT_PASS();
END_TEST

BEGIN_TEST(check_sort)
    std::fstream file("top10.dat");
    ScoreManager a_score(file);
    sf::Time time_1 = sf::seconds(10);
    sf::Time time_2 = sf::seconds(30);
    sf::Time time_3 = sf::seconds(20);
    sf::Time time_4 = sf::seconds(50);

    Player player_1;
    std::string yossi("yossi");
    player_1.name(yossi);
    player_1.time(time_1);
    player_1.raise_score(20);

    Player player_2;
    std::string omer("omer");
    player_2.name(omer);
    player_2.time(time_2);
    player_2.raise_score(5);

    Player player_3;
    std::string ori("ori");
    player_3.name(ori);
    player_3.time(time_3);
    player_3.raise_score(20);

    Player player_4;
    std::string din("din");
    player_4.name(din);
    player_4.time(time_4);
    player_4.raise_score(20);

    a_score.add(player_1);
    a_score.add(player_2);
    a_score.add(player_3);
    a_score.add(player_4);

    a_score.save();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(load)
    std::fstream file("top10.dat");
    ScoreManager a_score(file);
    a_score.load();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(insert_in_full_list)
    std::fstream file("top10.dat", std::ios::in | std::ios::out);
    ScoreManager a_score(file);
    a_score.load();
    a_score.reset_file_position();

    sf::Time time_1 = sf::seconds(50);
    Player player_1;
    std::string omer("omer");
    player_1.name(omer);
    player_1.time(time_1);
    player_1.raise_score(20);

    a_score.add(player_1);
    a_score.save();
    ASSERT_PASS();
END_TEST



TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
	IGNORE_TEST(add_and_save)
    IGNORE_TEST(load_to_string)
    IGNORE_TEST(check_sort)
    IGNORE_TEST(load)
    TEST(insert_in_full_list)
    
    
	
END_SUITE