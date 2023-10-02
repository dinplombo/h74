#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef> //size_t
#include <iostream> //cout
#include <cassert> //assert
#include <utility> //swap
#include "helpers.hpp" //helpers::artimetic_sequence



namespace ds {

template<typename T>
class SymMatrix
{
public:
    explicit SymMatrix(size_t a_dim);

    SymMatrix(SymMatrix<T> const& a_other);
    SymMatrix& operator=(SymMatrix const& a_other);
    ~SymMatrix();

    template<typename U>
    SymMatrix(SymMatrix<U> const& a_other);

    template<typename U>
    SymMatrix& operator=(SymMatrix<U> const& a_other);

    T& operator()(size_t a_row, size_t a_column);
    T const& operator()(size_t a_row, size_t a_column) const;
    
    void swap(SymMatrix& a_other);
    size_t size() const;
    
    SymMatrix& operator+=(SymMatrix const& a_other);

    template<typename U>
    SymMatrix& operator+=(SymMatrix<U> const& a_other);

    template<typename U, typename W>
    friend SymMatrix<U> operator*(SymMatrix<U> const& a_first, W const& a_scalar);

    template<typename U, typename W>
    friend SymMatrix<U> operator*(W const& a_scalar, SymMatrix<U> const& a_first);

    template<typename U>
    friend SymMatrix<U> operator+(SymMatrix<U> const& a_lVal, SymMatrix<U> const& a_rVal);

    template<typename U, typename W>
    friend SymMatrix<U> operator+(SymMatrix<U> const& a_lVal, SymMatrix<W> const& a_rVal);
  
    template<typename U>
    friend std::ostream& operator<<(std::ostream &a_out, const SymMatrix<U> &a_matrix);

private:
    template<typename U>
    friend class SymMatrix;

private:
    size_t m_dimension;
    T* m_data;
};

template <typename T>
SymMatrix<T>::SymMatrix(size_t a_dim)
:m_dimension(a_dim)
,m_data(new T[helpers::artimetic_sequence(a_dim)]{})
{
}

template <typename T>
//require T: op =
SymMatrix<T>::SymMatrix(SymMatrix const &a_other)
:m_dimension(a_other.m_dimension)
,m_data(new T[helpers::artimetic_sequence(a_other.m_dimension)])
{
    size_t total_size = helpers::artimetic_sequence(a_other.m_dimension);
    std::copy(a_other.m_data, a_other.m_data + total_size, m_data);
}

template <typename T>
template <typename U>
SymMatrix<T>::SymMatrix(SymMatrix<U> const& a_other)
:m_dimension(a_other.m_dimension)
,m_data(new T[helpers::artimetic_sequence(a_other.m_dimension)])
{
    size_t total_size = helpers::artimetic_sequence(a_other.m_dimension);
    std::copy(a_other.m_data, a_other.m_data + total_size, m_data);
}

template <typename T>
void SymMatrix<T>::swap(SymMatrix& a_other)
{
    using std::swap;
    swap(m_dimension, a_other.m_dimension);
    swap(m_data, a_other.m_data);
}

template <typename T>
size_t SymMatrix<T>::size() const
{
    return helpers::artimetic_sequence(m_dimension);
}

template <typename T>
SymMatrix<T>& SymMatrix<T>::operator=(SymMatrix const& a_other)
{
    if(this != &a_other){
        SymMatrix dummy_metrix(a_other);
        swap(dummy_metrix);
    }

    return *this;
}

template <typename T>
template <typename U>
SymMatrix<T>& SymMatrix<T>::operator=(SymMatrix<U> const& a_other)
{
    SymMatrix dummy_metrix(a_other);
    swap(dummy_metrix);
    return *this;
}

namespace {
size_t where(size_t a_row, size_t a_column, size_t a_size)
{
    if (a_row < a_column){
        return a_row * a_size + a_column - helpers::artimetic_sequence(a_row);
    }
    else {
        return a_column * a_size + a_row - helpers::artimetic_sequence(a_column);
    }
}

} //namespace

template <typename T>
SymMatrix<T>::~SymMatrix()
{
    delete[] m_data;
}

template <typename T>
//require T: op+=
SymMatrix<T>& SymMatrix<T>::operator+=(SymMatrix const &a_other)
{
    assert(m_dimension == a_other.m_dimension);
    if (m_dimension == a_other.m_dimension){
        size_t total_size = helpers::artimetic_sequence(m_dimension);
        for (size_t i = 0; i < total_size; ++i){
        m_data[i] += a_other.m_data[i];
        }
    }
    return *this;
}

template <typename T>
template <typename U>
//require T: op+=
SymMatrix<T>& SymMatrix<T>::operator+=(SymMatrix<U> const &a_other)
{
    assert(m_dimension == a_other.m_dimension);
    if (m_dimension == a_other.m_dimension){
        size_t total_size = helpers::artimetic_sequence(m_dimension);
        for (size_t i = 0; i < total_size; ++i){
        m_data[i] += a_other.m_data[i];
        }
    }
    return *this;
}


template <typename U>
SymMatrix<U> operator+(SymMatrix<U> const& a_lVal, SymMatrix<U> const& a_rVal)
{
    assert(a_lVal.m_dimension == a_rVal.m_dimension);
    SymMatrix<U> sum_matrix(a_rVal);
    if (a_lVal.m_dimension == a_rVal.m_dimension){
        sum_matrix += a_lVal;  
    }
    return sum_matrix;
}

template <typename U, typename W>
SymMatrix<U> operator+(SymMatrix<U> const& a_lVal, SymMatrix<W> const& a_rVal)
{
    assert(a_lVal.m_dimension == a_rVal.m_dimension);
    SymMatrix<U> sum_matrix(a_rVal);
    if (a_lVal.m_dimension == a_rVal.m_dimension){
        sum_matrix += a_lVal;  
    }
    return sum_matrix;
}

template <typename U, typename W>
SymMatrix<U> operator*(SymMatrix<U> const& a_first, W const& a_scalar)
{
    SymMatrix<U> new_matrix(a_first.m_dimension);
    size_t total_size = helpers::artimetic_sequence(a_first.m_dimension);
    for (size_t i = 0; i < total_size; ++i)
    {
        new_matrix.m_data[i] = a_first.m_data[i] * a_scalar;
    }
    return new_matrix;
}

template <typename U, typename W>
SymMatrix<U> operator*(W const& a_scalar, SymMatrix<U> const& a_first)
{
    SymMatrix<U> new_matrix(a_first.m_dimension);
    size_t total_size = helpers::artimetic_sequence(a_first.m_dimension);
    for (size_t i = 0; i < total_size; ++i)
    {
        new_matrix.m_data[i] = a_first.m_data[i] * a_scalar;
    }
    return new_matrix;
}

template <typename U>
std::ostream &operator<<(std::ostream &a_out, const SymMatrix<U> &a_matrix)
{
    size_t counter = 0;
    for (size_t i = 0; i < a_matrix.m_dimension; ++i){
        for (size_t j = 0; j < a_matrix.m_dimension; ++j){
            a_out << a_matrix.m_data[where(i, j, a_matrix.m_dimension)] << ',';
            ++counter;
            if (counter == a_matrix.m_dimension){
                std::cout << '\n';
                counter = 0;
            }
        }
    }
    return a_out;
}

template <typename T>
//require T: ctor not explicit?
T& SymMatrix<T>::operator()(size_t a_row, size_t a_column) 
{
    assert(a_row < m_dimension && a_column < m_dimension);
    return m_data[where(a_row, a_column, m_dimension)];
}

template <typename T>
T const& SymMatrix<T>::operator()(size_t a_row, size_t a_column) const
{
    assert(a_row < m_dimension && a_column < m_dimension);
    return m_data[where(a_row, a_column, m_dimension)];
}


} // namespace ds

#endif // MATRIX_HPP

