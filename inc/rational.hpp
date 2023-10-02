#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstddef>

/**
 * @brief represent a fraction
 *
 */

namespace algebra
{

class Rational {
public:
    Rational(int a_numerator, int a_denomerator); //constrctor function
    Rational(int a_numerator);
    Rational();

    void print() const;
    double value() const;
    // bool operator<(Rational const& a_first, Rational const& a_second);

    Rational& inverse();
    Rational& reduce();
    Rational& swap(Rational& a_ratioal);
    Rational& operator+=(Rational const& a_ratioal);
    Rational& operator*=(Rational const& a_ratioal);
    Rational& operator-=(Rational const& a_ratioal);
    Rational& operator/=(Rational const& a_ratioal);
    Rational& operator++(); 
    Rational operator++(int);
    Rational& operator--(); 
    Rational operator--(int); 

private:
    int m_numerator;
    int m_denomerator;
};

Rational operator+(Rational const& a_first, Rational const& a_second); 
Rational operator*(Rational const& a_first, Rational const& a_second);
Rational operator-(Rational const& a_first, Rational const& a_second);
Rational operator/(Rational const& a_first, Rational const& a_second);
bool operator<(Rational const& a_first, Rational const& a_second);
bool operator>(Rational const& a_first, Rational const& a_second);
bool operator!=(Rational const& a_first, Rational const& a_second);
bool operator==(Rational const& a_first, Rational const& a_second);
bool operator<=(Rational const& a_first, Rational const& a_second);
bool operator>=(Rational const& a_first, Rational const& a_second);
Rational sum(Rational const* a_array, size_t a_size);
double sumd(Rational const* a_array, size_t a_size);
void swap(Rational& a_first, Rational& a_second);

}//namespace algebra





#endif // RATIONAL_HPP
