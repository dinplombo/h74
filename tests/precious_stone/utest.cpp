#include "mu_test.h"
#include "uppercase.hpp"
#include "vowels.hpp"
#include "caesar_encryption.hpp"
#include "text_message.hpp"
#include "message.hpp"
#include "transposition_ciper.hpp"
#include "rot13.hpp"
#include "leetcode.hpp"
#include "scytale.hpp"
#include "substitution_encoder.hpp"
#include "precious_stone.hpp"
#include "consol_source.hpp"
#include "consol_destination.hpp"
#include "file_source.hpp"
#include "file_destination.hpp"
#include "udp_client.hpp"


#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#include <string>
#include <iostream>

BEGIN_TEST(uppercase)
    AbsMessage::TextMessage str("hellow h74");
    AbsMessage::TextMessage str_check("HELLOW H74");
    AbsMessage::UpperCase uc;
    AbsMessage::TextMessage encoded;
    uc.encode(str, encoded);
    std::string::iterator source_current = str.begin();
    std::string::iterator result_current = encoded.begin();
    std::string::iterator result_end = encoded.end();
    while (result_current != result_end){
        ASSERT_THAT(*result_current == toupper(*source_current));
        ++result_current;
        ++source_current;
    }
    ASSERT_THAT(encoded == str_check);
END_TEST

BEGIN_TEST(vowel)
    AbsMessage::TextMessage str("hellow h74");
    AbsMessage::TextMessage str_check("h*ll*w h74");
    AbsMessage::Vowels v;
    AbsMessage::TextMessage encoded;
    v.encode(str, encoded);
    ASSERT_THAT(encoded == str_check);
END_TEST

BEGIN_TEST(leetcoode)
    AbsMessage::TextMessage str("hellow h74");
    AbsMessage::TextMessage str_check("|-|3|_|_()\\/\\/|-|");
    AbsMessage::LeetCode lc;
    AbsMessage::TextMessage encoded;
    lc.encode(str, encoded);
    ASSERT_THAT(encoded == str_check);
END_TEST

BEGIN_TEST(caeser)
    AbsMessage::TextMessage str("THE QUICK BROWN");
    AbsMessage::TextMessage str_check("GUR DHVPX OEBJA");
    int shift_num = 13;
    AbsMessage::CaesarEncryption ce(shift_num);
    AbsMessage::TextMessage encoded;
    ce.encode(str, encoded);
    ASSERT_THAT(encoded == str_check);
END_TEST

BEGIN_TEST(caeser_decode)
    AbsMessage::TextMessage str("GUR DHVPX OEBJA");
    AbsMessage::TextMessage str_check("THE QUICK BROWN");
    int shift_num = 13;
    AbsMessage::CaesarEncryption ce(shift_num);
    AbsMessage::TextMessage encoded;
    ce.encode(str, encoded);
    ASSERT_THAT(encoded == str_check);
END_TEST

BEGIN_TEST(rot)
    AbsMessage::TextMessage str("THE QUICK BROWN");
    AbsMessage::TextMessage str_check("GUR DHVPX OEBJA");
    AbsMessage::RotThirteen rt;
    AbsMessage::TextMessage encoded;
    rt.encode(str, encoded);
    ASSERT_THAT(encoded == str_check);
END_TEST

BEGIN_TEST(transposition)
    AbsMessage::TextMessage str("keep the code clean");
    AbsMessage::TextMessage str_check("h*ll*w h74");
    std::string str1("LISPER");
    AbsMessage::TranspositionEncryption te(str1);
    AbsMessage::TextMessage encoded;
    te.encode(str, encoded);
    ASSERT_THAT(encoded == str_check);
END_TEST

BEGIN_TEST(scytale)
    AbsMessage::Scytale scyt{5};
    AbsMessage::TextMessage origin("i am hurt very badly help");
    AbsMessage::TextMessage encrypted{""};
    AbsMessage::TextMessage expected{"iryyatbhmvaehedlurlp"};
    scyt.encode(origin, encrypted);
    std::string::iterator target_begin = encrypted.begin();
    std::string::iterator target_end = encrypted.end();
    std::string::iterator expected_begin = expected.begin();
    while (target_begin != target_end) {
        ASSERT_THAT(*target_begin == *expected_begin);
        ++expected_begin;
        ++target_begin;
    }
    ASSERT_THAT(*target_begin == 0);
END_TEST

BEGIN_TEST(console_test)
    AbsMessage::UpperCase uc;
    AbsMessage::ConsolSource input;
    AbsMessage::ConsolDestination out;
    AbsMessage::PreciousStone ps{input, out, uc};
    ps.execute();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(file_consol_test)
    AbsMessage::UpperCase uc;
    AbsMessage::FileSource input("test.txt");
    AbsMessage::ConsolDestination out;
    AbsMessage::PreciousStone ps{input, out, uc};
    ps.execute();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(consol_file_test)
    AbsMessage::UpperCase uc;
    AbsMessage::ConsolSource input;
    AbsMessage::FileDestination out("newfile.txt");
    AbsMessage::PreciousStone ps{input, out, uc};
    ps.execute();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(file_file_test)
    AbsMessage::UpperCase uc;
    AbsMessage::FileSource input("test.txt");
    AbsMessage::FileDestination out("newfile.txt");
    AbsMessage::PreciousStone ps{input, out, uc};
    ps.execute();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(console_client_test)
    AbsMessage::UpperCase uc;
    AbsMessage::ConsolSource input;
    AbsMessage::UdpServer out;
    AbsMessage::PreciousStone ps{input, out, uc};
    ps.execute();
    ASSERT_PASS();
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

    TEST(uppercase)
    TEST(vowel)
    TEST(caeser)
    TEST(caeser_decode)
    TEST(rot)
    IGNORE_TEST(transposition)
    TEST(leetcoode)
    TEST(scytale)
    IGNORE_TEST(console_test)
    IGNORE_TEST(file_consol_test)
    IGNORE_TEST(consol_file_test)
    IGNORE_TEST(file_file_test)
    TEST(console_client_test)
	
END_SUITE
