//
// Created by win 10 on 20/10/2022.
//

#ifndef PRIORITY_QUEUE_V2_C_VECTOR_H
#define PRIORITY_QUEUE_V2_C_VECTOR_H
#include <iostream>

//C_vector implementation from https://www.cplusplus.com/reference/vector/vector/
template <class T, class Alloc = std::allocator<T>> // default allocator for T
class C_vector {
public:
    // types:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    //typedef typename allocator_type::template rebind<T>::other allocator_type;
    typedef typename allocator_type::template rebind<T>::other::pointer iterator;
    typedef typename allocator_type::template rebind<T>::other::const_pointer const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;

    // construct/copy/destroy:
    explicit C_vector (const allocator_type& alloc = allocator_type());
    explicit C_vector (size_type n, const value_type& val = value_type(),
                       const allocator_type& alloc = allocator_type());
    template <class InputIterator>
    C_vector (InputIterator first, InputIterator last,
              const allocator_type& alloc = allocator_type());
    C_vector (const C_vector& x);
    C_vector (C_vector&& x) noexcept ;
    C_vector& operator= (const C_vector& x);
    C_vector& operator= (C_vector&& x) noexcept;
    ~C_vector() = default;

    // iterators:
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // capacity:
    size_type size() const noexcept; // return size
    size_type max_size() const noexcept; // return maximum possible size
    void resize (size_type n, value_type val = value_type()); // resize
    size_type capacity() const noexcept; // return allocated storage capacity
    [[nodiscard]] bool empty() const noexcept; // test whether vector is empty
    void reserve (size_type n); // request a change in capacity
    //void shrink_to_fit();

    // element access:
    reference operator[] (size_type n);
    const_reference operator[] (size_type n) const;
    reference at (size_type n);
    const_reference at (size_type n) const;
    reference front(); // access first element
    const_reference front() const;
    reference back();   // access last element
    const_reference back() const;
    //value_type* data() noexcept;

    //modifiers:
    template <class... Args>    //emplace_back
    void emplace_back (Args&&... args); // construct and insert element at end
    void push_back (const value_type& val); // insert element at end
    void push_back (value_type&& val); // insert element at end
    void pop_back(); // delete last element
    iterator insert (const_iterator position, const value_type& val);
    iterator erase (const_iterator position); // erase element at position
    void swap (C_vector& x); // swap content
    void clear() noexcept; // clear content
    template <class... Args>
    iterator emplace (const_iterator position, Args&&... args);
    iterator insert (const_iterator position, size_type n, const value_type& val);

    //allocator
    allocator_type get_allocator() const noexcept;

    //Non-member function overloads
    friend bool operator== (const C_vector<T,Alloc>& lhs, const C_vector<T,Alloc>& rhs){
        return lhs.size() == rhs.size();
    }
    friend bool operator!= (const C_vector<T,Alloc>& lhs, const C_vector<T,Alloc>& rhs){
        return lhs.size() != rhs.size();
    }
    friend bool operator<  (const C_vector<T,Alloc>& lhs, const C_vector<T,Alloc>& rhs){
        return lhs.size() < rhs.size();
    }
    friend bool operator<= (const C_vector<T,Alloc>& lhs, const C_vector<T,Alloc>& rhs){
        return lhs.size() <= rhs.size();
    }
    friend bool operator>  (const C_vector<T,Alloc>& lhs, const C_vector<T,Alloc>& rhs){
        return lhs.size() > rhs.size();
    }
    friend bool operator>= (const C_vector<T,Alloc>& lhs, const C_vector<T,Alloc>& rhs){
        return lhs.size() >= rhs.size();
    }
    friend void swap (C_vector<T,Alloc>& x, C_vector<T,Alloc>& y){
        x.swap(y);
    }

private:
    size_type _size; // size
    size_type _capacity; // capacity
    allocator_type _allocator; // allocator
    iterator _data; // data
};

//////////////////////////////////////////// construct/copy/destroy ////////////////////////////////////////////
template<class T, class Alloc>
C_vector<T, Alloc>::C_vector(const allocator_type &alloc) { // default constructor
    _size = 0;
    _capacity = 0;
    _allocator = alloc;
    _data = nullptr;
}

template<class T, class Alloc>
C_vector<T, Alloc>::C_vector(size_type n, const value_type &val, const allocator_type &alloc) { // fill constructor
    _size = n;
    _capacity = n;
    _allocator = alloc;
    _data = _allocator.allocate(n);
    for (int i = 0; i < n; ++i) {
        _allocator.construct(_data + i, val);
    }
}

template<class T, class Alloc>
template<class InputIterator>
C_vector<T, Alloc>::C_vector(InputIterator first, InputIterator last, const allocator_type &alloc) { // range constructor
    _size = last - first;
    _capacity = _size;
    _allocator = alloc;
    _data = _allocator.allocate(_size);
    for (int i = 0; i < _size; ++i) { // copy elements
        _allocator.construct(_data + i, *(first + i)); // construct element
    }
}

template<class T, class Alloc>
C_vector<T, Alloc>::C_vector(const C_vector &x) { // copy constructor
    _size = x._size;
    _capacity = x._capacity;
    _allocator = x._allocator;
    _data = _allocator.allocate(_size);
    for (int i = 0; i < _size; ++i) { // copy elements
        _allocator.construct(_data + i, x._data[i]); // construct element
    }
}

template<class T, class Alloc>
C_vector<T, Alloc>::C_vector(C_vector &&x) noexcept { // move constructor
    _size = x._size;
    _capacity = x._capacity;
    _allocator = x._allocator;
    _data = x._data;
    x._size = 0;
    x._capacity = 0;
    x._data = nullptr;
}

template<class T, class Alloc>
C_vector<T, Alloc> &C_vector<T, Alloc>::operator=(const C_vector &x) { // copy assignment operator
    if (this == &x) {
        return *this; // self-assignment check
    }
    _size = x._size;
    _capacity = x._capacity;
    _allocator = x._allocator;
    _data = _allocator.allocate(_size);
    for (int i = 0; i < _size; ++i) { // copy elements
        _allocator.construct(_data + i, x._data[i]); // construct element
    }
    return *this; // return reference to this object
}

template<class T, class Alloc>
C_vector<T, Alloc> &C_vector<T, Alloc>::operator=(C_vector &&x)  noexcept {
    if (this == &x) {
        return *this;
    }
    _size = x._size;
    _capacity = x._capacity;
    _allocator = x._allocator;
    _data = x._data;
    x._size = 0;
    x._capacity = 0;
    x._data = nullptr;
    return *this;
}

//////////////////////////////////////////// iterators ////////////////////////////////////////////
template<class T, class Alloc>
typename C_vector<T, Alloc>::iterator C_vector<T, Alloc>::begin() noexcept { // return iterator to beginning
    return _data;
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_iterator C_vector<T, Alloc>::begin() const noexcept { // return const_iterator to beginning
    return _data;
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::iterator C_vector<T, Alloc>::end() noexcept { // return iterator to end
    return _data + _size;
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_iterator C_vector<T, Alloc>::end() const noexcept { // return const_iterator to end
    return _data + _size;
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::reverse_iterator C_vector<T, Alloc>::rbegin() noexcept { // return reverse iterator to reverse beginning
    return reverse_iterator(_data + _size);
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_reverse_iterator C_vector<T, Alloc>::rbegin() const noexcept { // return const_reverse_iterator to reverse beginning
    return const_reverse_iterator(_data + _size);
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::reverse_iterator C_vector<T, Alloc>::rend() noexcept { // return reverse iterator to reverse end
    return reverse_iterator(_data);
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_reverse_iterator C_vector<T, Alloc>::rend() const noexcept { // return const_reverse_iterator to reverse end
    return const_reverse_iterator(_data);
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_iterator C_vector<T, Alloc>::cbegin() const noexcept { // return const_iterator to beginning
    return _data;
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_iterator C_vector<T, Alloc>::cend() const noexcept { // return const_iterator to end
    return _data + _size;
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::C_vector::const_reverse_iterator C_vector<T, Alloc>::crbegin() const noexcept { // return const_reverse_iterator to reverse beginning
    return const_reverse_iterator(_data + _size);
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::C_vector::const_reverse_iterator C_vector<T, Alloc>::crend() const noexcept { // return const_reverse_iterator to reverse end
    return const_reverse_iterator(_data);
}

//////////////////////////////////////////// capacity ////////////////////////////////////////////
template<class T, class Alloc>
typename C_vector<T, Alloc>::size_type C_vector<T, Alloc>::size() const noexcept { // return size
    return _size;
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::size_type C_vector<T, Alloc>::max_size() const noexcept { // return maximum size
    return _allocator.max_size();
}

template<class T, class Alloc>
void C_vector<T, Alloc>::resize(size_type n, value_type val) { // resize
    if (n > _size) { // if n is greater than current size
        if (n > _capacity) { // if n is greater than current capacity
            reserve(n); // reserve new memory
        }
        for (int i = _size; i < n; ++i) { // construct new elements
            _allocator.construct(_data + i, val); // construct element
        }
    } else {
        for (int i = n; i < _size; ++i) { // destroy elements
            _allocator.destroy(_data + i); // destroy element
        }
    }
    _size = n; // set new size
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::size_type C_vector<T, Alloc>::capacity() const noexcept { // return capacity
    return _capacity;
}

template<class T, class Alloc>
bool C_vector<T, Alloc>::empty() const noexcept { // test whether vector is empty
    return _size == 0;
}

template<class T, class Alloc>
void C_vector<T, Alloc>::reserve(size_type n) { // request a change in capacity
    if (n > _capacity) { // if n is greater than current capacity
        pointer new_data = _allocator.allocate(n); // allocate new memory
        for (int i = 0; i < _size; ++i) { // copy elements
            _allocator.construct(new_data + i, _data[i]); // construct element
        }
        for (int i = 0; i < _size; ++i) { // destroy elements
            _allocator.destroy(_data + i); // destroy element
        }
        _allocator.deallocate(_data, _capacity); // deallocate old memory
        _data = new_data; // set new data
        _capacity = n; // set new capacity
    }
}

//////////////////////////////////////////// allocators ////////////////////////////////////////////
template<class T, class Alloc>
typename C_vector<T, Alloc>::allocator_type C_vector<T, Alloc>::get_allocator() const noexcept {
    return _allocator;
}

//////////////////////////////////////////// element access ////////////////////////////////////////////
template<class T, class Alloc>
typename C_vector<T, Alloc>::reference C_vector<T, Alloc>::operator[](size_type n) { // subscript non-const vector
    return _data[n];
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_reference C_vector<T, Alloc>::operator[](size_type n) const { // subscript const vector
    return _data[n];
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::reference C_vector<T, Alloc>::at(size_type n) { // subscript non-const vector with checking
    if (n >= _size) { // if n is greater than or equal to size
        throw std::out_of_range("out of range"); // throw exception
    }
    return _data[n]; // return element
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_reference C_vector<T, Alloc>::at(size_type n) const { // subscript const vector with checking
    if (n >= _size) {   // if n is greater than or equal to size
        throw std::out_of_range("out of range"); // throw exception
    }
    return _data[n];    // return element
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::reference C_vector<T, Alloc>::front() {    // return first element
    return _data[0];
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_reference C_vector<T, Alloc>::front() const { // return first element
    return _data[0];
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::reference C_vector<T, Alloc>::back() { // return last element
    return _data[_size - 1];
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_reference C_vector<T, Alloc>::back() const { // return last element
    return _data[_size - 1];
}

/*template<class T, class Alloc>
typename C_vector<T, Alloc>::pointer C_vector<T, Alloc>::data() noexcept {
    return _data;
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::const_pointer C_vector<T, Alloc>::data() const noexcept {
    return _data;
}*/

//////////////////////////////////////////// modifiers ////////////////////////////////////////////
template<class T, class Alloc>
template<class... Args> //Args is a parameter pack
void C_vector<T, Alloc>::emplace_back(Args &&... args) { // construct and insert element at end
    if (_size == _capacity) {   // if size is equal to capacity
        reserve(_capacity == 0 ? 1 : _capacity * 2);    // reserve new memory
    }
    _allocator.construct(_data + _size, std::forward<Args>(args)...); // construct element
    ++_size;    // increment size
}

template<class T, class Alloc>
void C_vector<T, Alloc>::push_back(const value_type &val) { // insert element at end
    if (_size == _capacity) {   // if size is equal to capacity
        reserve(_capacity == 0 ? 1 : _capacity * 2);    // reserve new memory
    }
    _allocator.construct(_data + _size, val);   // construct element
    ++_size;    // increment size
}

template<class T, class Alloc>
void C_vector<T, Alloc>::push_back(value_type &&val) {  // insert element at end
    if (_size == _capacity) {   // if size is equal to capacity
        reserve(_capacity == 0 ? 1 : _capacity * 2);    // reserve new memory
    }
    _allocator.construct(_data + _size, std::move(val));
    ++_size;    // increment size
}

template<class T, class Alloc>
void C_vector<T, Alloc>::pop_back() {   // delete last element
    _allocator.destroy(_data + _size - 1);  // destroy element
    --_size;    // decrement size
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::iterator C_vector<T, Alloc>::insert(const_iterator position, const value_type &val) {
    size_type pos = position - begin(); // get position
    if (_size == _capacity) {   // if size is equal to capacity
        reserve(_capacity == 0 ? 1 : _capacity * 2);    // reserve new memory
    }
    for (int i = _size; i > pos; --i) { // move elements
        _allocator.construct(_data + i, _data[i - 1]);  // construct element
    }
    _allocator.construct(_data + pos, val); // construct element
    ++_size;        // increment size
    return begin() + pos;   // return iterator
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::iterator C_vector<T, Alloc>::erase(const_iterator position) { // erase element
    size_type pos = position - begin(); // get position
    for (int i = pos; i < _size - 1; ++i) { // move elements
        _allocator.construct(_data + i, _data[i + 1]); // construct element
    }
    _allocator.destroy(_data + _size - 1);  // destroy element
    --_size;    // decrement size
    return begin() + pos;  // return iterator
}

template<class T, class Alloc>
void C_vector<T, Alloc>::swap(C_vector &x) { // swap contents
    std::swap(_data, x._data); // swap data
    std::swap(_size, x._size); // swap size
    std::swap(_capacity, x._capacity); // swap capacity
}

template<class T, class Alloc>
void C_vector<T, Alloc>::clear() noexcept {
    for (int i = 0; i < _size; ++i) {  // destroy elements
        _allocator.destroy(_data + i); // destroy element
    }
    _size = 0; // set size to 0
}

template<class T, class Alloc>
template<class... Args>
typename C_vector<T, Alloc>::iterator C_vector<T, Alloc>::emplace(const_iterator position, Args &&... args) {
    size_type pos = position - begin(); // get position
    if (_size == _capacity) {  // if size is equal to capacity
        reserve(_capacity == 0 ? 1 : _capacity * 2);    // reserve new memory
    }
    for (int i = _size; i > pos; --i) { // move elements
        _allocator.construct(_data + i, _data[i - 1]); // construct element
    }
    _allocator.construct(_data + pos, std::forward<Args>(args)...); // construct element
    ++_size;   // increment size
    return begin() + pos; // return iterator
}

template<class T, class Alloc>
typename C_vector<T, Alloc>::iterator C_vector<T, Alloc>::insert(const_iterator position, size_type n, const value_type &val) {
    size_type pos = position - begin(); // get position
    if (_size + n > _capacity) {   // if size + n is greater than capacity
        reserve(_capacity == 0 ? n : _capacity * 2); // reserve new memory
    }
    for (int i = _size + n - 1; i >= pos + n; --i) { // move elements
        _allocator.construct(_data + i, _data[i - n]); // construct element
    }
    for (int i = pos; i < pos + n; ++i) { // insert elements
        _allocator.construct(_data + i, val); // construct element
    }
    _size += n; // increment size
    return begin() + pos; // return iterator
}

//////////////////////////////////////////// non-member functions ////////////////////////////////////////////
/*
template<class T, class Alloc>
bool operator==(const C_vector<T, Alloc> &lhs, const C_vector<T, Alloc> &rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (int i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template<class T, class Alloc>
bool operator!=(const C_vector<T, Alloc> &lhs, const C_vector<T, Alloc> &rhs) {
    return !(lhs == rhs);
}

template<class T, class Alloc>
bool operator<(const C_vector<T, Alloc> &lhs, const C_vector<T, Alloc> &rhs) {
    for (int i = 0; i < lhs.size() && i < rhs.size(); ++i) {
        if (lhs[i] < rhs[i]) {
            return true;
        }
        if (lhs[i] > rhs[i]) {
            return false;
        }
    }
    return lhs.size() < rhs.size();
}

template<class T, class Alloc>
bool operator<=(const C_vector<T, Alloc> &lhs, const C_vector<T, Alloc> &rhs) {
    return !(rhs < lhs);
}

template<class T, class Alloc>
bool operator>(const C_vector<T, Alloc> &lhs, const C_vector<T, Alloc> &rhs) {
    return rhs < lhs;
}

template<class T, class Alloc>
bool operator>=(const C_vector<T, Alloc> &lhs, const C_vector<T, Alloc> &rhs) {
    return !(lhs < rhs);
}

template<class T, class Alloc>
void swap(C_vector<T, Alloc> &x, C_vector<T, Alloc> &y) {
    x.swap(y);
}*/

#endif //PRIORITY_QUEUE_V2_C_VECTOR_H
