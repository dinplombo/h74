#include "rational.hpp"
#include "helpers.hpp"

#include <cstdio>
#include <cassert>

namespace algebra{

Rational::Rational(int a_numerator, int a_denomerator)
{
    assert(a_denomerator != 0);
    if (a_denomerator < 0) {
        a_denomerator *= -1;
        a_numerator *= -1;
    }
    m_numerator = a_numerator;
    m_denomerator = a_denomerator;
}

Rational::Rational(int a_numerator)
{
    m_numerator = a_numerator;
    m_denomerator = 1;
}

Rational::Rational()
{
    m_numerator = 0;
    m_denomerator = 1;
}

void Rational::print() const
{
    printf("%d/%d", m_numerator, m_denomerator);
}

Rational& Rational::inverse()
{
    assert(m_numerator != 0);
    *this = Rational(m_denomerator, m_numerator);
    return *this;
}

Rational& Rational::operator+=(Rational const& a_ratioal) //a += b
{
    m_numerator  = m_denomerator * a_ratioal.m_numerator + m_numerator * a_ratioal.m_denomerator;
    m_denomerator = m_denomerator * a_ratioal.m_denomerator;
    return *this;
}

Rational operator+(Rational const& a_first, Rational const& a_second) // c = a + b
{
    Rational new_rational = a_first;
    new_rational += (a_second);
    return new_rational;
}


Rational& Rational::operator*=(Rational const& a_ratioal) 
{
    m_numerator = m_numerator * a_ratioal.m_numerator;
    m_denomerator = m_denomerator * a_ratioal.m_denomerator;
    return *this;
}

Rational operator*(Rational const& a_first, Rational const& a_second) 
{
    Rational new_rational = a_first;
    new_rational *= (a_second);
    return new_rational;
}

Rational& Rational::operator-=(Rational const& a_ratioal) 
{
    m_numerator = m_numerator * a_ratioal.m_denomerator - m_denomerator * a_ratioal.m_numerator; 
    m_denomerator = m_denomerator * a_ratioal.m_denomerator;
    return *this;
}

Rational operator-(Rational const& a_first, Rational const& a_second) 
{
    Rational new_rational = a_first;
    new_rational -= (a_second);
    return new_rational;
}

Rational& Rational::operator/=(Rational const& a_ratioal) //2/20 \ 2/5 = 4/40 * 100/40 = 104/40
{
    m_numerator  = m_numerator * a_ratioal.m_denomerator;
    m_denomerator = m_denomerator * a_ratioal.m_numerator;
    return *this;
}

Rational operator/(Rational const& a_first, Rational const& a_second) 
{
    Rational new_rational = a_first;
    new_rational /= (a_second);
    return new_rational;
}

Rational& Rational::operator++()
{
    *this += 1;
    return *this;
}

Rational Rational::operator++(int)
{
    Rational original_rational = *this;
    *this += 1;
    return original_rational;
}

Rational& Rational::operator--()
{
    *this -= 1;
    return *this;
}

bool operator<(Rational const& a_first, Rational const& a_second)
{
    Rational result = a_first - a_second;
    return result.value() < 0 ? true : false;
}

bool operator==(Rational const& a_first, Rational const& a_second)
{
    Rational result = a_first - a_second;
    if (result.value() == 0){
        return true;
    }
    return false;
}

bool operator!=(Rational const& a_first, Rational const& a_second)
{
    return !(a_first == a_second);
}

bool operator>(Rational const& a_first, Rational const& a_second)
{
    return (a_second < a_first);
}

bool operator>=(Rational const& a_first, Rational const& a_second)
{
    return !(a_first < a_second);
}

bool operator<=(Rational const& a_first, Rational const& a_second)
{
    return !(a_first > a_second);
}

Rational Rational::operator--(int)
{
    Rational original_rational = *this;
    *this -= 1;
    return original_rational;
}

Rational sum(Rational const* a_array, size_t a_size)
{
    size_t i;
    Rational r_sum;
    if (a_array == 0 || a_size == 0){
        return r_sum;
    }
    for (i = 0; i < a_size; ++i){
        r_sum += a_array[i];
    }
    return r_sum;
}

double sumd(Rational const* a_array, size_t a_size)
{
    Rational sum_array = sum(a_array, a_size);
    return sum_array.value();
}

Rational& Rational::swap(Rational& a_ratioal)//not const&
{
    helpers::swap(m_numerator, a_ratioal.m_numerator);
    helpers::swap(m_denomerator, a_ratioal.m_denomerator);
    return *this;
}

void swap(Rational& a_first, Rational& a_second)
{
    a_first.swap(a_second);
}

Rational& Rational::reduce()
{
    int num1 = m_numerator;
    int num2 = m_denomerator;
    if (num1 < 0){
        num1 *= -1;
    }
    while (num1 != 0 && num2 != 0) {
        if (num1 > num2) {
            num1 = num1 % num2;
        }
        else {
            num2 = num2 % num1;
        }
    }
    int gcd;
    if (num1 > num2) {
        gcd = num1;
    }
    else {
        gcd = num2;
    }
    m_numerator /= gcd;
    m_denomerator /= gcd;
    return *this;
}

double Rational::value() const
{
    return (double)m_numerator / m_denomerator;
}


}//namespace algebra