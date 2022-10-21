//
// Created by HarryLex on 18/10/2022.
//

#ifndef PRIORITY_QUEUE_C_PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_C_PRIORITY_QUEUE_H

#include "C_vector.h"
#include <iostream>
#include <algorithm>

//priority queue implementation from https://www.cplusplus.com/reference/queue/priority_queue/
template <class T, class Container = C_vector<T>, class Compare = std::less<typename Container::value_type>>
class C_priority_queue {
public:
    //Member types
    typedef T value_type;
    typedef Container container_type;
    typedef std::size_t size_type;

    typedef Compare value_compare; // not required by C++ but provided for STL compatibility
    typedef typename Container::reference reference; //value_type&
    typedef typename Container::const_reference const_reference; //const value_type&

    //Member functions
    explicit C_priority_queue (const Compare& comp = Compare(),
                              const Container& cont = Container());
    template <class InputIterator>
    C_priority_queue (InputIterator first, InputIterator last,
                      const Compare& comp = Compare(),
                      const Container& cont = Container());

    C_priority_queue (const C_priority_queue& x);
    C_priority_queue (C_priority_queue&& x)  noexcept ;
    C_priority_queue& operator= (const C_priority_queue& x);
    C_priority_queue& operator= (C_priority_queue&& x) noexcept ;
    ~C_priority_queue(){
        m_c.clear();
    }
    //Test whether container is empty (public member function)
    [[nodiscard]] bool empty() const;
    //Return size (public member function)
    [[nodiscard]] size_type size() const;
    //Access top element (public member function)
    const value_type& top() const;
    template <class... Args>
    void emplace (Args&&... args);
    void push (const value_type& val);
    void push (value_type&& val);
    void pop();
    void swap (C_priority_queue& x);

    //makw_heap (public member function) - O(log n) - parameter: first, last, comp
    /*
    void push_heap (typename Container::iterator first, typename Container::iterator last, Compare comp){
        if (last - first < 2) return;                                                     //if size < 2, then it is already a heap
        auto len = last - first;                                                          //size of the heap
        for (auto i = len / 2 - 1; i >= 0; --i){                                          //start from the last parent
            auto parent = i;                                                        //parent index
            while (true){                                                                 //while the parent is not a leaf
                auto left = 2 * parent + 1;                                               //left child index
                auto right = 2 * parent + 2;                                              //right child index
                auto largest = parent;                                              //largest element index
                if (left < len && comp(first[left], first[largest]))                      //if left child is larger than parent
                    largest = left;                                                       //largest element is left child
                if (right < len && comp(first[right], first[largest]))                    //if right child is larger than largest element
                    largest = right;                                                      //largest element is right child
                if (largest == parent)
                    break;                                                                //if parent is the largest element, then break
                std::swap(first[parent], first[largest]);                                 //swap largest element with parent
                parent = largest;                                                         //largest element is now the parent
            }
        }
    }
    //pop_heap (public member function) - O(log n) - parameter: first, last, comp
    void pop_heap (typename Container::iterator first, typename Container::iterator last, Compare comp){
        if (last - first < 2) return;                                                     //if size < 2, then it is already a heap
        auto len = last - first;                                                          //size of the heap
        std::swap(first[0], first[len - 1]);                                               //swap the first and last element
        for (auto i = 0; i < len / 2;){                                                    //start from the root
            auto parent = i;                                                        //parent index
            while (true){                                                                 //while the parent is not a leaf
                auto left = 2 * parent + 1;                                               //left child index
                auto right = 2 * parent + 2;                                              //right child index
                auto largest = parent;                                              //largest element index
                if (left < len - 1 && comp(first[left], first[largest]))                 //if left child is larger than parent
                    largest = left;                                                       //largest element is left child
                if (right < len - 1 && comp(first[right], first[largest]))               //if right child is larger than largest element
                    largest = right;                                                      //largest element is right child
                if (largest == parent)
                    break;                                                                //if parent is the largest element, then break
                std::swap(first[parent], first[largest]);                                 //swap largest element with parent
                parent = largest;                                                         //largest element is now the parent
            }
            ++i;                                                                          //go to the next parent
        }
    }
    */

    //friend functions
    friend bool operator== (const C_priority_queue<T,Container,Compare>& lhs,
                            const C_priority_queue<T,Container,Compare>& rhs){
        return lhs.m_c == rhs.m_c;
    }
    friend bool operator!= (const C_priority_queue<T,Container,Compare>& lhs,
                            const C_priority_queue<T,Container,Compare>& rhs){
        return !(lhs == rhs);
    }
    friend bool operator< (const C_priority_queue<T,Container,Compare>& lhs,
                           const C_priority_queue<T,Container,Compare>& rhs){
        return lhs.m_c < rhs.m_c;
    }
    friend bool operator<= (const C_priority_queue<T,Container,Compare>& lhs,
                            const C_priority_queue<T,Container,Compare>& rhs){
        return !(rhs < lhs);
    }
    friend bool operator> (const C_priority_queue<T,Container,Compare>& lhs,
                           const C_priority_queue<T,Container,Compare>& rhs){
        return rhs < lhs;
    }
    friend bool operator>= (const C_priority_queue<T,Container,Compare>& lhs,
                            const C_priority_queue<T,Container,Compare>& rhs){
        return !(lhs < rhs);
    }
    friend void swap (C_priority_queue<T,Container,Compare>& x,
                      C_priority_queue<T,Container,Compare>& y){
        x.swap(y);
    }

private:
    Container m_c;
    Compare m_comp;

    void heapify(long long i){  //O(log n)
        long long l = 2*i + 1; //left child
        long long r = 2*i + 2;  //right child
        long long largest = i;  //largest element
        if(l < m_c.size() && m_comp(m_c[l], m_c[i])){   //if left child is larger than parent
            largest = l;        //largest element is left child
        }
        if(r < m_c.size() && m_comp(m_c[r], m_c[largest])){ //if right child is larger than largest element
            largest = r;    //largest element is right child
        }
        if(largest != i){   //if largest element is not parent
            std::swap(m_c[i], m_c[largest]);    //swap largest element with parent
            heapify(largest);   //heapify the subtree
        }
    }
    void build_heap(){  //O(n)
        for(int i = m_c.size()/2 - 1; i >= 0; --i){ //start from the last parent
            heapify(i); //heapify the subtree
        }
    }

};

///////////////////////////////////// Member functions ///////////////////////////////////////
template<class T, class Container, class Compare>
C_priority_queue<T, Container, Compare>::C_priority_queue(const Compare &comp, const Container &cont) {
    m_c = cont;
    m_comp = comp;
}

template<class T, class Container, class Compare>
template<class InputIterator>
C_priority_queue<T, Container, Compare>::C_priority_queue(InputIterator first, InputIterator last, const Compare &comp,
                                                          const Container &cont) { //this function is O(n)
    m_c = cont; //initialize container
    m_comp = comp; //initialize comparator
    while (first != last){ //while there are elements in the range
        m_c.push_back(*first); //push the element to the back of the container
        first++;   //increment iterator
    }
}

template<class T, class Container, class Compare>
C_priority_queue<T, Container, Compare>::C_priority_queue(const C_priority_queue &x) {
    m_c = x.m_c;
    m_comp = x.m_comp;
}

template<class T, class Container, class Compare>
C_priority_queue<T, Container, Compare>::C_priority_queue(C_priority_queue &&x) noexcept {
    m_c = x.m_c; //move container
    m_comp = x.m_comp; //move comparator
    x.m_c.clear(); //clear x

}

template<class T, class Container, class Compare>
typename C_priority_queue<T, Container, Compare>::C_priority_queue &C_priority_queue<T, Container, Compare>::operator=(const C_priority_queue &x) {
    m_c = x.m_c;
    m_comp = x.m_comp;
    return *this;
}

template<class T, class Container, class Compare>
typename C_priority_queue<T, Container, Compare>::C_priority_queue &C_priority_queue<T, Container, Compare>::operator=(C_priority_queue &&x) noexcept {
    m_c = x.m_c;
    m_comp = x.m_comp;
    x.m_c.clear();
    return *this;
}

template<class T, class Container, class Compare>
bool C_priority_queue<T, Container, Compare>::empty() const {
    return m_c.empty();
}

template<class T, class Container, class Compare>
typename C_priority_queue<T, Container, Compare>::C_priority_queue::size_type C_priority_queue<T, Container, Compare>::size() const {
    return m_c.size();
}

template<class T, class Container, class Compare>
const typename C_priority_queue<T, Container, Compare>::value_type &C_priority_queue<T, Container, Compare>::top() const {
    return m_c.front();
}

template<class T, class Container, class Compare>
template<class... Args>
void C_priority_queue<T, Container, Compare>::emplace(Args &&... args) {
    m_c.emplace_back(std::forward<Args>(args)...);  //emplace element to the back of the container O(1)
    std::make_heap(m_c.begin(), m_c.end(), m_comp); //O(n)
    //make_heap(m_c.begin(), m_c.end(), m_comp); //O(n)
}

template<class T, class Container, class Compare>
void C_priority_queue<T, Container, Compare>::push(const value_type &val) {
    m_c.push_back(val); //push element to the back of the container O(1)
    std::make_heap(m_c.begin(), m_c.end(), m_comp); //O(n)
    //make_heap(m_c.begin(), m_c.end(), m_comp); //O(n)
}

template<class T, class Container, class Compare>
void C_priority_queue<T, Container, Compare>::push(value_type &&val) {  //O(log n)
    m_c.push_back(std::move(val)); //push element to the back of the container
    std::make_heap(m_c.begin(), m_c.end(), m_comp); //O(n)
    //make_heap(m_c.begin(), m_c.end(), m_comp); //O(n)
}

template<class T, class Container, class Compare>
void C_priority_queue<T, Container, Compare>::pop() {
    std::pop_heap(m_c.begin(), m_c.end(), m_comp); //O(n)
    //pop_heap(m_c.begin(), m_c.end(), m_comp); //O(n)
    m_c.pop_back(); //pop element from the back of the container O(1)
}

template<class T, class Container, class Compare>
void C_priority_queue<T, Container, Compare>::swap(C_priority_queue &x) {
    m_c.swap(x.m_c);    //swap containers
    std::swap(m_comp, x.m_comp);    //swap comparators
}

#endif //PRIORITY_QUEUE_C_PRIORITY_QUEUE_H
