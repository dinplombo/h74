#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef> //size_t
#include <iostream> 
#include <utility> //swap
#include <cassert> //assert
#include "helpers.hpp"

namespace ds {

namespace impl_detail {

template<typename T>
class Node {
public:
    Node(); 
    explicit Node(T const& a_data); 

    ~Node();
    Node(Node const& a_other);
    Node& operator=(Node const& a_other);

    Node& operator+=(Node const& a_other);

    Node& next(Node& m_node);
    Node& prev(Node& m_node);

    Node* next() const;
    Node* prev() const;
    const T& data() const;

    void swap(Node& a_other);
    void swap_data(Node& a_right_node);


private:
    T m_data;
    Node<T>* m_prev;
    Node<T>* m_next;
};


template<typename T>
Node<T>::Node()
:m_data()
,m_prev()
,m_next()
{
}

template<typename T>
Node<T>::Node(T const& a_data)
:m_data(a_data)
,m_prev()
,m_next()
{
}

template <typename T>
Node<T>::~Node()
{   
}

template <typename T>
Node<T>::Node(Node const &a_other)
:m_data(a_other.m_data)
,m_prev(a_other.m_prev)
,m_next(a_other.m_next)
{
}

template <typename T>
Node<T>& Node<T>::operator=(Node const &a_other)
{
    if(this != &a_other){
        Node c(a_other);
        swap(c);
    }
    return *this;
}

template <typename T>
//require T: op+=
Node<T>& Node<T>::operator+=(Node const &a_other)
{
   return (m_data + a_other.m_data);
}

template<typename T>
Node<T>& Node<T>::next(Node& m_node)
{
    m_next = &m_node;
    return *this;
}

template<typename T>
Node<T>& Node<T>::prev(Node& m_node)
{
    m_prev = &m_node;
    return *this;
}

template <typename T>
Node<T>* Node<T>::next() const
{
   return m_next;
}

template <typename T>
Node<T>* Node<T>::prev() const
{
   return m_prev;
}

template <typename T>
const T& Node<T>::data() const
{
   return m_data;
}

template <typename T>
void Node<T>::swap(Node& a_other)
{
    std::swap(m_data, a_other.m_data);
    std::swap(m_prev, a_other.m_prev);
    std::swap(m_next, a_other.m_next);
}

template <typename T>
void Node<T>::swap_data(Node &a_right_node)
{
    using std::swap;
    swap(this->m_data, a_right_node.m_data);
}

} //namespace impl_detail

template<typename T>
class Linked_list {
public:
    Linked_list(); 

    ~Linked_list();
    Linked_list(Linked_list const& a_other);
    Linked_list& operator=(Linked_list const& a_to_add);

    Linked_list& push_head(T const& a_value);
    Linked_list& push_tail(T const& a_value);
    Linked_list& pop_head(T& a_value);
    Linked_list& pop_tail(T& a_value);
    Linked_list& remove(T a_value);

    size_t size() const;
    void clear();
    void swap(Linked_list& a_other);
    
    bool insert_after(T a_key, T a_value);
    bool contains(T a_value) const;
    bool operator==(Linked_list const& a_other);
    bool operator!=(Linked_list const& a_other);
    bool operator<(Linked_list const& a_other);
    
    template <typename C>
    size_t for_each(int (&a_action_func)(T& a_value, C& a_context), C& a_context) const;

    template <typename U>
    friend Linked_list<U> splice(Linked_list<U> const& a_first_list, Linked_list<U> const& a_second_list);

    Linked_list& reverse();
    T sum(T& a_sum) const;

private:

    void insert_befor_first(impl_detail::Node<T>* a_first_node, impl_detail::Node<T>* a_new_node);
    void remove(impl_detail::Node<T>* a_node);
    impl_detail::Node<T>* search(T a_key) const;

private:
    impl_detail::Node<T> m_head;
    impl_detail::Node<T> m_tail;
    size_t m_size;
};

template<typename T>
Linked_list<T>::Linked_list()
:m_head(impl_detail::Node<T>())
,m_tail(impl_detail::Node<T>())
,m_size(0)
{
    m_head.next(m_tail);
    m_head.prev(m_head);
    m_tail.next(m_tail);
    m_tail.prev(m_head);
}

template <typename T>
Linked_list<T>::~Linked_list()
{
    if(m_size){
        impl_detail::Node<T>* delete_node = m_head.next();
        for (size_t i = 0; i < m_size; ++i){
            delete_node = delete_node->next();
            delete delete_node->prev();
        }
    }
}


template <typename T>
Linked_list<T>::Linked_list(Linked_list const& a_to_copy)
: m_head(0)
, m_tail(0)
, m_size(0)
{
    m_head.next(m_tail);
    m_head.prev(m_head);
    m_tail.next(m_tail);
    m_tail.prev(m_head);
    impl_detail::Node<T>* current;
    current = a_to_copy.m_head.next();
    for (size_t i =0; i < a_to_copy.m_size; ++i) {
        this->push_tail(current->data());
        current = current->next();
    }
}

template <typename T>
void Linked_list<T>::swap(Linked_list& a_other)
{
    Linked_list<T> dummy_list(a_other);
    a_other = *this;
    *this = dummy_list;
}

template <typename T>
Linked_list<T>& Linked_list<T>::push_head(T const& a_value)
{
    impl_detail::Node<T>* new_node = new impl_detail::Node<T>(a_value);
	insert_befor_first(this->m_head.next(), new_node);
    return *this;
}

template <typename T>
Linked_list<T>& Linked_list<T>::push_tail(T const& a_value)
{
    impl_detail::Node<T>* new_node = new impl_detail::Node<T>(a_value);
	insert_befor_first(&this->m_tail, new_node);
    return *this;
}

template <typename T>
Linked_list<T>& Linked_list<T>::pop_head(T& a_value)
{
    impl_detail::Node<T>* toRemove = m_head.next();
	a_value = toRemove->data();
	remove(toRemove);
	delete toRemove;
    return *this;
}

template <typename T>
Linked_list<T>& Linked_list<T>::pop_tail(T& a_value)//assertion
{
    impl_detail::Node<T>* toRemove = m_tail.prev();
	a_value = toRemove->data();
	remove(toRemove);
	delete toRemove;
    return *this;
}

template <typename T>
size_t Linked_list<T>::size() const
{
    return m_size;
}

template <typename T>
void Linked_list<T>::clear()
{
    assert(m_size);
    T cleared;
    size_t size  = m_size;
    for (size_t i = 0; i < size; ++i) {
        this->pop_head(cleared);
    }
} 

template <typename T>
bool Linked_list<T>::insert_after(T a_key, T a_value)
{
    impl_detail::Node<T>* next_node = search(a_key);
    if (next_node != &m_tail){
        impl_detail::Node<T>* new_node = new impl_detail::Node<T>(a_value);
        insert_befor_first(next_node->next(), new_node);
        return true;
    }
    return false;
}

template <typename T>
impl_detail::Node<T>* Linked_list<T>::search(T a_key) const
{
    impl_detail::Node<T>* next_node  = m_head.next();
    while(next_node != &m_tail)
    {
        if (next_node->data() == a_key){
            return next_node;
        }
        next_node = next_node->next();
    } 
    return next_node;
}

template <typename T>
Linked_list<T>& Linked_list<T>::remove(T a_key)
{
    impl_detail::Node<T>* next_node = search(a_key);
    if (next_node != &m_tail){
        remove(next_node);
        delete next_node;
        return *this;
    }
    return *this;
}

template <typename T>
bool Linked_list<T>::contains(T a_value) const
{
    impl_detail::Node<T>* next_node = search(a_value);
    if (next_node != &m_tail){
        return true;
    }
    return false;
}

template <typename T>
//require T : != 
bool Linked_list<T>::operator==(Linked_list const &a_other)
{
    if (m_size == a_other.m_size){
        impl_detail::Node<T>* next_node  = m_head.next();
        impl_detail::Node<T>* next_node_other  = a_other.m_head.next();
        for (size_t i = 0 ; i < m_size; ++i){
            if (next_node->data() != next_node_other->data()){
                return false;
            }
        next_node = next_node->next();
        next_node_other = next_node_other->next();
        }
        return true;
    }
    return false;
}

template <typename T>
bool Linked_list<T>::operator!=(Linked_list const &a_other)
{
    return !(*this == a_other);
}

template <typename T>
//require T : < 
bool Linked_list<T>::operator<(Linked_list const &a_other)
{
    if (m_size < a_other.m_size){
        return true;
    }
    if (m_size == a_other.m_size){
        impl_detail::Node<T>* next_node  = m_head.next();// need <T> after node?
        impl_detail::Node<T>* next_node_other  = a_other.m_head.next();
        for (size_t i = 0 ; i < m_size; ++i){
            if (next_node->data() < next_node_other->data()){
                return true;
            }
        next_node = next_node->next();
        next_node_other = next_node_other->next();
        }
        return false;
    }
    return false;
}

template <typename T>
template <typename C>
size_t Linked_list<T>::for_each(int (&a_action_func)(T& a_value, C& a_context), C& a_context) const
{
    size_t i;
    T dummy;
    if (m_size == 0){
        return 0;
    }
    impl_detail::Node<T>* next_node  = m_head.next();
    for (i = 0; i < m_size; ++i){
        dummy = next_node->data();
        if (a_action_func(dummy, a_context) == 0){
            break;
        }
        next_node = next_node->next();
    }
    return i;
}

template <typename T>
Linked_list<T>& Linked_list<T>::reverse()
{
    impl_detail::Node<T>* left_node  = m_head.next();
    impl_detail::Node<T>* right_node  = m_tail.prev();
    for (size_t i = 0; i < m_size / 2; ++i){
        left_node->swap_data(*right_node);
        left_node  = left_node->next();
        right_node  = right_node->prev();
    }
    return *this;
}

template <typename T>
T Linked_list<T>::sum(T& a_sum) const
{
    if (m_size == 0){
        return a_sum;
    }
    for_each(helpers::sum_action, a_sum);
    return a_sum;
}

template <typename T>
void Linked_list<T>::insert_befor_first(impl_detail::Node<T>* a_first_node, impl_detail::Node<T>* a_new_node)
{
    a_new_node->prev(*(a_first_node->prev()));
	a_new_node->next(*a_first_node);
	a_first_node->prev()->next(*a_new_node);
	a_first_node->prev(*a_new_node);
    ++m_size;
}

template <typename T>
void Linked_list<T>::remove(impl_detail::Node<T>* a_node)
{
    a_node->next()->prev(*a_node->prev());
	a_node->prev()->next(*a_node->next());
    --m_size;
}

template <typename T>
Linked_list<T>& Linked_list<T>::operator=(Linked_list const& a_to_add)
{
    if (m_size) {
        clear();
    }
    impl_detail::Node<T>* current;
    current = a_to_add.m_head.next();
    for (size_t i =0; i < a_to_add.m_size; ++i) {
        this->push_tail(current->data());
        current = current->next();
    }
    return *this;
}

template <typename U>
Linked_list<U> splice(Linked_list<U> const& a_first_list, Linked_list<U> const& a_second_list)
{
    Linked_list<U> list(a_first_list);
    size_t size = a_second_list.size();
    impl_detail::Node<U>* current;
    current = a_second_list.m_head.next();
    for (size_t i =0; i < size; ++i) {
        list.push_tail(current->data());
        current = current->next();
    }
    return list;
}

} //namespace ds

template <typename T>
//reruire T: op:+=
int helpers::sum_action(T& a_value, T& a_sum)
{
    a_sum += a_value;
    return 1;
}

#endif // LINKED_LIST_HPP