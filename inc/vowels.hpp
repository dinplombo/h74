#ifndef VOWELS_HPP
#define VOWELS__HPP

#include "message.hpp"
#include "substitution_encoder.hpp"

#include <string>
#include <set>


namespace AbsMessage
{

class Vowels : public SubstitutionEncoder {
public:
	explicit Vowels(std::string a_replacer = "*");
    ~Vowels() override = default;

    Vowels(Vowels const& a_other) = default;
    Vowels& operator=(Vowels const& a_other) = default;

private:
    std::string translate(char a_char) override;

private:
	std::string m_replacer;
	std::set<char> m_vowels;
};

} // namespace AbsMessage

#endif // VOWELS__HPP
