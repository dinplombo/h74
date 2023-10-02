#include "mu_test.h"
#include "frequency_table.hpp"

#include <sstream>
#include <iostream>
#include <cstddef>
#include <vector>
#include <map>



BEGIN_TEST(count)
    std::stringstream ss("green red,  green red red greenr red");
    std::string line;
    std::vector<size_t> vec;
    std::map<std::string, size_t> word_map;
    vec = ds::frequency_table(ss,1);
    // ds::print(vec);
    // ds::print(word_map);

    
    ASSERT_PASS();
END_TEST




TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

    TEST(count)
	
END_SUITE
