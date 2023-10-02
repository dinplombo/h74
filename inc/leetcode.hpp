#ifndef LEETCODE_HPP
#define LEETCODE_HPP

#include "substitution_encoder.hpp"
#include "message.hpp"
#include <unordered_map>


namespace AbsMessage
{
class LeetCode : public SubstitutionEncoder {
public:
    LeetCode();
    ~LeetCode() override = default;

private:
    std::string translate(char a_char) override;

private:
std::unordered_map<char, std::string> m_leet;
};

} //namespace AbsMessage

#endif // LEETCODE_HPP