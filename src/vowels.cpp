#include "vowels.hpp"

#include <string>
#include <unordered_map>

namespace AbsMessage
{

Vowels::Vowels(std::string a_replacer)
: m_replacer(a_replacer)
, m_vowels{'a', 'e', 'i', 'o', 'u', 'U', 'O', 'A', 'E','I'}
{
}

std::string Vowels::translate(char a_char)
{
	std::string str_return;
	if (m_vowels.count(a_char)){;
		return m_replacer;
	}
	str_return.push_back(a_char);
    return str_return;
}

} // namespace AbsMessage
