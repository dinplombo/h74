#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP


#include <string>
#include <sstream>

namespace en
{

class Encryption {
public:
    virtual ~Encryption() = default;
    virtual std::string encode(std::istream& a_message) = 0;

protected:
    Encryption() = default;
    Encryption(Encryption const& a_other) = default;
    Encryption& operator=(Encryption const& a_other) = default;

};

class Uppercase : public Encryption {
public:
    ~Uppercase() override;
    std::string encode(std::istream& a_message) override;

};

} // namespace en

#endif // ENCRYPTION_HPP