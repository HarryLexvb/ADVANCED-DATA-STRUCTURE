//
// Created by HarryLex on 9/12/2022.
//

#ifndef CONCURRENT_PRIORITY_QUEUE_V1_C_PRIORITY_QUEUE_H
#define CONCURRENT_PRIORITY_QUEUE_V1_C_PRIORITY_QUEUE_H

#include "C_vector.h"
#include <iostream>
#include <algorithm>

//priority queue implementation from https://www.cplusplus.com/reference/queue/priority_queue/
template <class T, class Container = C_vector<T>, class Compare = std::less<typename Container::value_type>>
class C_priority_queue {
public:
    //Member types
    typedef T value_type;                                               //type of the elements
    typedef Container container_type;                                   // type of the underlying container
    typedef std::size_t size_type;                                      // type to represent the size

    typedef Compare value_compare;                                      // not required by C++ but provided for STL compatibility
    typedef typename Container::reference reference;                    //value_type&
    typedef typename Container::const_reference const_reference;        //const value_type&

    //Member functions
    explicit C_priority_queue (const Compare& comp = Compare(),
                               const Container& cont = Container()); // constructor with default values
    template <class InputIterator>
    C_priority_queue (InputIterator first, InputIterator last,
                      const Compare& comp = Compare(),
                      const Container& cont = Container()); // constructor with iterators

    C_priority_queue (const C_priority_queue& x);                    // copy constructor (deep copy)
    C_priority_queue (C_priority_queue&& x)  noexcept;               // move constructor (shallow copy)
    C_priority_queue& operator= (const C_priority_queue& x);         // copy assignment operator (deep copy)
    C_priority_queue& operator= (C_priority_queue&& x) noexcept;     // move assignment operator (shallow copy)
    ~C_priority_queue(){m_c.clear();}                                // destructor
    //Test whether container is empty (public member function)
    [[nodiscard]] bool empty() const; // returns true if the container is empty
    //Return size (public member function)
    [[nodiscard]] size_type size() const; // returns the number of elements
    //Access top element (public member function)
    [[nodiscard]] const value_type& top() const;          // returns a reference to the top element in the container
    template <class... Args>                              // emplace element at the end of the container
    void emplace (Args&&... args);                        // constructs an element in-place at the end of the container
    void push (const value_type& val);                    // inserts a new element at the end of the container
    void push (value_type&& val);                         // inserts a new element at the end of the container

    void heapify(int i) { // heapify the container O(log n)
        int left = 2 * i + 1; // left child
        int right = 2 * i + 2; // right child
        int largest = i; // largest element
        if (left < m_c.size() && m_c[left] > m_c[i]) // if left child is larger than root
            largest = left; // largest is left child
        if (right < m_c.size() && m_c[right] > m_c[largest]) // if right child is larger than largest
            largest = right; // largest is right child
        if (largest != i) { // if largest is not root
            std::swap(m_c[i], m_c[largest]); // swap largest with root
            heapify(largest); // heapify the new root
        }

    }
    void pop();                                           // removes the element on top of the container
    void swap (C_priority_queue& x);                      // swaps the contents

    //push_heap (public member function) - O(log n) - parameter: first, last, comp
    /*void push_heap (typename Container::iterator first, typename Container::iterator last, Compare comp){
        //oldest to youngest O(log n)
        auto len = last - first;                                                          //size of the heap
        auto child = len - 1;                                                             //last element
        while (child > 0){                                                                //while there are elements in the heap
            auto parent = (child - 1) / 2;                                                //parent of the child
            if (comp(*(first + child), *(first + parent))){                               //if child is smaller than parent
                std::iter_swap(first + child, first + parent);                     //swap child and parent
                child = parent;                                                           //child is now parent
            }
            else
                return;                                                                   //if child is not smaller than parent, then we are done
        }
    }*/

    //friend functions
    friend bool operator== (const C_priority_queue<T,Container,Compare>& lhs,
                            const C_priority_queue<T,Container,Compare>& rhs){
        return lhs.m_c == rhs.m_c;
    } // returns true if the contents of lhs and rhs are equal, false otherwise
    friend bool operator!= (const C_priority_queue<T,Container,Compare>& lhs,
                            const C_priority_queue<T,Container,Compare>& rhs){
        return !(lhs == rhs);
    } // returns true if the contents of lhs and rhs are not equal, false otherwise
    friend bool operator< (const C_priority_queue<T,Container,Compare>& lhs,
                           const C_priority_queue<T,Container,Compare>& rhs){
        return lhs.m_c < rhs.m_c;
    } // returns true if the contents of lhs are less than those of rhs, false otherwise
    friend bool operator<= (const C_priority_queue<T,Container,Compare>& lhs,
                            const C_priority_queue<T,Container,Compare>& rhs){
        return !(rhs < lhs);
    } // returns true if the contents of lhs are less than or equal to those of rhs, false otherwise
    friend bool operator> (const C_priority_queue<T,Container ,Compare>& lhs,
                           const C_priority_queue<T,Container,Compare>& rhs){
        return rhs < lhs;
    } // returns true if the contents of lhs are greater than those of rhs, false otherwise
    friend bool operator>= (const C_priority_queue<T,Container,Compare>& lhs,
                            const C_priority_queue<T,Container,Compare>& rhs){
        return !(lhs < rhs);
    }  // returns true if the contents of lhs are greater than or equal to those of rhs, false otherwise
    void print_elements() const;

private:
    //Member variables
    Container m_c;                                      // underlying container
    Compare m_comp;                                     // comparison function
    //Member functions
    void percolate_up(size_type hole_index){ // O(log n)
        value_type tmp = std::move(m_c[hole_index]); // move the element to be percolated
        size_type parent = (hole_index - 1) / 2; // parent of the element to be percolated
        while (hole_index > 0 && m_comp(m_c[parent], tmp)){ // while the element to be percolated is larger than its parent
            m_c[hole_index] = std::move(m_c[parent]); // move the parent down
            hole_index = parent; // move hole_index up
            parent = (hole_index - 1) / 2; // parent of the element to be percolated
        }
        m_c[hole_index] = std::move(tmp);
    }        // this function is used to percolate up the element at the given index in the container
    void percolate_down(size_type hole_index){ // O (log n)
        size_type child; // child index
        value_type tmp = std::move(m_c[hole_index]);        // move hole to tmp
        for(; hole_index * 2 + 1 < m_c.size(); hole_index = child){ // while hole has a child
            child = hole_index * 2 + 1; // left child
            if(child != m_c.size() - 1 && m_comp(m_c[child + 1], m_c[child]))   // if right child is smaller than left child
                ++child;    // right child is smaller
            if(m_comp(m_c[child], tmp)) // if child is smaller than tmp
                m_c[hole_index] = std::move(m_c[child]);    // move child up
            else
                break;  // found right location
        }
        m_c[hole_index] = std::move(tmp);   // move tmp into final hole
    }      // this function is used to percolate down the element at the given index in the container
    void build_heap(){ //O(n)
        for (int i = m_c.size()/2; i >= 0; --i) {   // start at the last parent
            percolate_down(i);  // percolate down each element
        }
    }                              // this function is used to build a heap from the given container

};

///////////////////////////////////// Member functions ///////////////////////////////////////
template<class T, class Container, class Compare>
C_priority_queue<T, Container, Compare>::C_priority_queue(const Compare &comp, const Container &cont) {
    m_c = cont; // copy the container
    m_comp = comp; // copy the comparison function
}

template<class T, class Container, class Compare>
template<class InputIterator>
C_priority_queue<T, Container, Compare>::C_priority_queue(InputIterator first, InputIterator last, const Compare &comp,
                                                          const Container &cont) {
    m_c = cont;
    m_comp = comp;
}

template<class T, class Container, class Compare>
C_priority_queue<T, Container, Compare>::C_priority_queue(const C_priority_queue &x) {
    m_c = x.m_c; // copy the container
}

template<class T, class Container, class Compare>
C_priority_queue<T, Container, Compare>::C_priority_queue(C_priority_queue &&x) noexcept {
    m_c = std::move(x.m_c); // this function is used to move the container
    m_comp = std::move(x.m_comp); // this function is used to move the comparison function
}

template<class T, class Container, class Compare>
typename C_priority_queue<T, Container, Compare>::C_priority_queue &C_priority_queue<T, Container, Compare>::operator=(const C_priority_queue &x) {
    m_c = x.m_c;
    return *this; // this function is used to copy the container
}

template<class T, class Container, class Compare>
typename C_priority_queue<T, Container, Compare>::C_priority_queue &C_priority_queue<T, Container, Compare>::operator=(C_priority_queue &&x) noexcept {
    m_c = std::move(x.m_c);
    m_comp = std::move(x.m_comp);
    return *this; // thsi function return the moved container
}

template<class T, class Container, class Compare>
bool C_priority_queue<T, Container, Compare>::empty() const {
    return m_c.empty(); // this function returns true if the container is empty, false otherwise
}

template<class T, class Container, class Compare>
typename C_priority_queue<T, Container, Compare>::C_priority_queue::size_type C_priority_queue<T, Container, Compare>::size() const {
    return m_c.size();  // this function returns the size of the container
}

template<class T, class Container, class Compare>
const typename C_priority_queue<T, Container, Compare>::value_type &C_priority_queue<T, Container, Compare>::top() const {
    return m_c.front(); // this function returns the top element of the container
}

template<class T, class Container, class Compare>
template<class... Args>
void C_priority_queue<T, Container, Compare>::emplace(Args &&... args) { //O(log n)
    m_c.emplace_back(std::forward<Args>(args)...); // this function is used to add a new element to the container using the given arguments O(1)
    std::push_heap(m_c.begin(), m_c.end(), m_comp); // this function is used to push the element into the container in a heap order O(log n)
    //push_heap(m_c.begin(), m_c.end(), m_comp); // this function is used to push the element into the container in a heap order O(log n)
}

template<class T, class Container, class Compare>
void C_priority_queue<T, Container, Compare>::push(const value_type &val) { //O(log n)
    m_c.push_back(val); // this function is used to add a new element to the container
    std::push_heap(m_c.begin(), m_c.end(), m_comp); // this function is used to push the element into the container O(log n)
    //push_heap(m_c.begin(), m_c.end(), m_comp); // this function is used to push the element into the container O(log n)
}

template<class T, class Container, class Compare>
void C_priority_queue<T, Container, Compare>::push(value_type &&val) {
    m_c.push_back(std::move(val)); // this function is used to add a new element to the container
    std::push_heap(m_c.begin(), m_c.end(), m_comp); // this function is used to push the element into the container
    //push_heap(m_c.begin(), m_c.end(), m_comp); // this function is used to push the element into the container
}

template<class T, class Container, class Compare>
void C_priority_queue<T, Container, Compare>::pop() {
    if(m_c.size() == 1){ // if the container has only one element
        m_c.pop_back(); // this function is used to remove the last element from the container
        return; // return from the function
    }
    m_c[0] = m_c.back(); // this function is used to move the last element to the first position
    m_c.pop_back(); // this function is used to remove the last element from the container
    heapify(0); // this function is used to heapify the container
}

template<class T, class Container, class Compare>
void C_priority_queue<T, Container, Compare>::swap(C_priority_queue &x) {
    std::swap(m_c, x.m_c); // this function is used to swap the containers
}

template<class T, class Container, class Compare>
void C_priority_queue<T, Container, Compare>::print_elements() const {
    for(auto &i : m_c){ // for each element in the container
        std::cout << i << "-"; // print the element
    }
    std::cout << std::endl; // print a new line
}


#endif //CONCURRENT_PRIORITY_QUEUE_V1_C_PRIORITY_QUEUE_H
