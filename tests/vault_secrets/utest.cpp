#include "mu_test.h"
#include "vault_secrets.hpp"
#include "uppercase.hpp"
#include "caesar_encryption.hpp"
#include "encoder.hpp"

#include <string>
#include <fstream>
#include <iostream>

using namespace AbsMessage;
using namespace vault;


BEGIN_TEST(is_singlton)
    auto& v = VaultSecrets<int>::get_instance();
    auto& s = VaultSecrets<int>::get_instance();

    ASSERT_EQUAL(&v, &s);
END_TEST

BEGIN_TEST(instet_int)
    auto& vault = VaultSecrets<int>::get_instance();
    int tw_secret = 1234;
    int wa_secret = 5678;
    vault.add("twitter", tw_secret);
    vault.add("walla", wa_secret);
    int result;
    vault.get("twitter", result);
    ASSERT_THAT(result == tw_secret);
END_TEST

BEGIN_TEST(instet_string)
    auto& vault = VaultSecrets<std::string >::get_instance();
    std::string tw_secret = "password";
    std::string wa_secret = "pas12s";
    vault.add("twitter", tw_secret);
    vault.add("walla", wa_secret);
    std::string  result;
    vault.get("twitter", result);
    ASSERT_THAT(result == tw_secret);
END_TEST

BEGIN_TEST(insert_differnt_secret)
    auto& vault = VaultSecrets<std::string >::get_instance();
    std::string secret = "fake password";
    ASSERT_THAT(!(vault.add("twitter", secret)));
END_TEST

BEGIN_TEST(get_from_another_vault)
    auto& vault1 = VaultSecrets<std::string >::get_instance();
    std::string  result;
    vault1.get("twitter", result);
    ASSERT_THAT(result == "password");
END_TEST

BEGIN_TEST(get_worng_key)
    auto& vault1 = VaultSecrets<std::string >::get_instance();
    std::string  result;
    ASSERT_THAT(!(vault1.get("paypal", result)));
END_TEST

BEGIN_TEST(save)
    auto& vault1 = VaultSecrets<std::string >::get_instance();
    std::ofstream out_file;
    Encoder* uc = new CaesarEncryption(13);
    out_file.open("my_secrets.txt");
    if(out_file){
        vault1.save(out_file,*uc);
    }
    ASSERT_PASS();
END_TEST

BEGIN_TEST(save_in_non_exist_file)
    auto& vault1 = VaultSecrets<std::string >::get_instance();
    std::ofstream fake_file;
    Encoder* uc = new CaesarEncryption(13);
    vault1.save(fake_file,*uc);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(load1)
    auto& vault1 = VaultSecrets<std::string >::get_instance();
    std::ifstream in_file("load_test.txt");
    Encoder* uc = new CaesarEncryption(13);
    load<std::string>(vault1,in_file,*uc);
    std::string  result;
    vault1.get("facebook", result);
    ASSERT_THAT(result == "password");
    std::string  result1;
    vault1.get("amazon", result1);
    ASSERT_THAT(result1 == "pas12s");
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
        TEST(is_singlton)
        TEST(instet_int)
        TEST(instet_string)
        TEST(insert_differnt_secret)
        TEST(get_from_another_vault)
        TEST(get_worng_key)
        TEST(save)
        TEST(load1)
        TEST(save_in_non_exist_file)
        
END_SUITE