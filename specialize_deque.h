//namespace pic10c { template<typename T> class dedue; }
//
//  specialize_deque.h
//  Pic10C_HW8
//
//  Created by Baiting Zhu on 11/14/21.
//

#ifndef specialize_deque_h
#define specialize_deque_h

#include <memory>
#include <climits>
#include <stdexcept>
#include <type_traits>

#include <iostream>


/**
 templated class of deque by T
 */
template<typename T>
class deque;

/**
 boolean specialization of deque
 */
template<>
class deque<bool>;

/**
 sum function in pic10c namespace
 */
template<typename T> // numerical only
const T sum(const deque<T>& target);

template<typename T>
class deque
{
public:
    /**
     nested iterator, has variables pointing to container and curent position
     */
    class iterator;
    /**
     nested const_iterator, has variables pointing to container and curent position
     */
    class const_iterator;
    /**
     default constructor
     */
    deque();
    /**
     copy constructor
     @param other is the other deque
     */
    deque(const deque& other);
    /**
     move constructor
     @param other is the other deque
     */
    deque(deque&& other);
    /**
     destructor
     */
    ~deque();
    /**
     move operation
     @param other is the other deque
     */
    deque& operator=(deque other) &;
    /**
     bracket operation
     @param indice is the indice in the bracket
     */
    T& operator[](const size_t& indice);
    /**
     helper function to double the max size of deque and copy old elements into new places
     */
    void double_cap_and_copy();
    /**
     push an element to the end
     @param input is the element to add
     */
    void push_back(const T& input);
    /**
     push an element to the front
     @param input is the element to add
     */
    void push_front(const T& input);
    /**
     pop the end element
     */
    void pop_back();
    /**
     pop the front element
     */
    void pop_front();
    /**
     swap the deque with another one
     @param other is the other deque
     */
    void swap(deque& other);
    /**
     find the size of deque
     @return a size_t value indicating the size
     */
    const size_t size() const { return sz; }
    /**
     find the cap of deque
     @return a size_t value indicating the cap
     */
    const size_t capacity() const { return cap; }
    /**
     find the begin iterator of the deque
     @return the const iterator to the first elem
     */
    const iterator begin();
    /**
     find the end iterator of the deque
     @return the const iterator to the past the end elem
     */
    const iterator end();
    /**
     find the begin const_iterator of the deque
     @return the const const_iterator to the start
     */
    const const_iterator begin() const;
    /**
     find the end const_iterator of the deque
     @return the const const_iterator to the past the end elem
     */
    const const_iterator end() const;
    /**
     find if the deque is full
     @return a const boolean indicating whether the deque is full
     */
    const bool is_full() { return (sz == cap) ? true : false; }
    /**
     add all values in the deque and find sum
     @return a const T value indicating the sum
     */
    const T get_sum() const;
private:
    std::unique_ptr<T[]> data; // data is a unique pointer to an array of type T
    size_t cap; // max size
    size_t sz; // number of element currently has
    int left; // !!kept as int, not size_t, since pointing_index = -1 indicates the "pass the end" signal!
    int right; // !!kept as int, not size_t, since pointing_index = -1 indicates the "pass the end" signal!
};

template<>
class deque<bool>
{
public:
    /**
     nested proxy class
     */
    class proxy;
    /**
     nested const proxy class
     */
    class const_proxy;
    /**
     nested iterator, has variables pointing to container and curent position
     */
    class iterator;
    /**
     nested const_iterator, has variables pointing to container and curent position
     */
    class const_iterator;
    /**
     default constructor
     */
    deque();
    /**
     copy constructor
     */
    deque(const deque& other);
    /**
     move constructor
     */
    deque(deque&& other);
    /**
     desctructor
     */
    ~deque();
    /**
     move operation
     @param other is the other deque
     */
    deque operator=(deque other) &;
    /**
     bracket operation
     @param indice is the indice in the bracket
     */
    proxy operator[](const size_t& indice);
    /**
     bracket operation
     @param indice is the indice in the bracket
     */
    const_proxy operator[](const size_t& indice) const;
    void double_cap_and_copy();
    /**
     push an element to the end
     @param input is the element to add
     */
    void push_back(const bool& input);
    /**
     push an element to the front
     @param input is the element to add
     */
    void push_front(const bool& input);
    /**
     pop the end element
     */
    void pop_back();
    /**
     pop the front element
     */
    void pop_front();
    /**
     swap the deque with another one
     @param other is the other deque
     */
    void swap(deque& other);
    /**
     find the size of deque
     @return a size_t value indicating the size
     */
    const size_t size() const { return sz; }
    /**
     find the cap of deque
     @return a size_t value indicating the cap
     */
    const size_t capacity() const { return cap; }
    /**
     find the begin iterator of the deque
     @return the const iterator to the first elem
     */
    const iterator begin();
    /**
     find the end iterator of the deque
     @return the const iterator to the past the end elem
     */
    const iterator end();
    /**
     find the begin const_iterator of the deque
     @return the const const_iterator to the start
     */
    const const_iterator begin() const;
    /**
     find the end const_iterator of the deque
     @return the const const_iterator to the past the end elem
     */
    const const_iterator end() const;
    /**
     find if the deque is full
     @return a const boolean indicating whether the deque is full
     */
    const bool is_full() { return (sz == cap) ? true : false; }
    //const bool get_sum() const;
private:
    unsigned char* data = new unsigned char[CHAR_BIT];
    size_t cap; // max size
    size_t sz; // number of lement currently has
    int left; // !!kept as int, not size_t, since pointing_index = -1 indicates the "pass the end" signal!
    int right; // !!kept as int, not size_t, since pointing_index = -1 indicates the "pass the end" signal!
};

template<typename T>
class deque<T>::iterator
{
    friend deque;
public:
    /**
     default constructor
     */
    iterator() : container(nullptr) { pointing_index = -1; }
    /**
     constructor
     @param deque is the container
     @param index is the index pointing to
     */
    iterator(deque* deque, const int& index) : container(deque) { pointing_index = index; }
    /**
     equal operator
     @param other is the irght hand side
     @return a const boolean
     */
    const bool operator==(iterator other) const;
    /**
     unequal operator
     @param other is the irght hand side
     @return a const boolean
     */
    const bool operator!=(iterator other) const;
    /**
     prefix increment operator
     @return iter reference
     */
    iterator& operator++();
    /**
     post increment operator
     @return iter reference
     */
    iterator operator++(int);
    /**
     prefix decrement operator
     @return iter ference
     */
    iterator& operator--();
    /**
     posfix decrement operator
     */
    iterator operator--(int);
    /**
     star operator operator
     */
    const T& operator*() const { return container->data[pointing_index]; }
    /**
     arrow decrement operator
     */
    const T* operator->() const { return &(container->data[pointing_index]); }

private:
    deque* container; // pointer to deque container
    int pointing_index; // kept as int, not size_t, since pointing_index = -1 indicates the "pass the end" signal!
};

template<typename T>
class deque<T>::const_iterator
{
    friend deque;
public:
    /**
     default construcor
     */
    const_iterator() : const_iterator(nullptr) { pointing_index = -1; }
    /**
     constructor
     @param deque is the container
     @paran index is the index pointing to
     */
    const_iterator(const deque* deque, const int& index) : container(deque) { pointing_index = index; }
    /**
     equal operator
     @param other is the irght hand side
     @return a const boolean
     */
    const bool operator==(const_iterator other) const;
    /**
     prefix increment operator
     @return iter reference
     */
    const bool operator!=(const_iterator other) const;
    /**
     prefix increment operator
     @return iter reference
     */
    const_iterator& operator++();
    /**
     post increment operator
     @return iter reference
     */
    const_iterator operator++(int);
    /**
     prefix decrement operator
     @return iter ference
     */
    const_iterator& operator--();
    /**
     posfix decrement operator
     */
    const_iterator operator--(int);
    /**
     star operator operator
     */
    const T& operator*() const { return container->data[pointing_index]; }
    /**
     arrow decrement operator
     */
    const T* operator->() const { return &(container->data[pointing_index]); }

private:
    const deque* container;
    int pointing_index; // kept as int, not size_t, since pointing_index = -1 indicates the "pass the end" signal!
};

class deque<bool>::iterator
{
    friend deque<bool>;
public:
    /**
     default constructor
     */
    iterator() : container(nullptr), data_index(0), bit_index(0) { }
    /**
     constructor
     @param deque is the container
     @param _data_index is the data index
     @param _bit_index is the bit index
     */
    iterator(deque* deque, const size_t& _data_index, const size_t& _bit_index) : container(deque), data_index(_data_index), bit_index(_bit_index) { }
    /**
     equal operator
     @param other is the irght hand side
     @return a const boolean
     */
    const bool operator==(iterator other) const;
    /**
     unequal operator
     @param other is the irght hand side
     @return a const boolean
     */
    const bool operator!=(iterator other) const;
    /**
     prefix increment operator
     @return iter reference
     */
    iterator& operator++();
    /**
     post increment operator
     @return iter reference
     */
    iterator operator++(int);
    /**
     prefix decrement operator
     @return iter ference
     */
    iterator& operator--();
    /**
     posfix decrement operator
     */
    iterator operator--(int);
    /**
     star operator operator
     */
    const bool& operator*() const;
    /**
     arrow decrement operator
     */
    const bool* operator->() const;


private:
    deque* container;
    int data_index;
    int bit_index;
};

class deque<bool>::proxy
{
    friend deque<bool>;
public:
    /**
     equal operator
     */
    const proxy& operator=(bool b) const;
    /**
     bool operator
     */
    operator bool() const;

private:
    /**
     constructor
     */
    proxy(deque* container, size_t _data_index, size_t _bit_index);
    deque* container;
    size_t data_index;
    size_t bit_index;
};

class deque<bool>::const_proxy
{
    friend deque<bool>;
public:
    /**
     equal operator
     */
    const const_proxy& operator=(bool b) const;
    /**
     bool operator
     */
    operator bool() const;

private:
    /**
     constructor
     */
    const_proxy(const deque* _container, const size_t _data_index, const size_t _bit_index);
    const deque* container;
    size_t data_index;
    size_t bit_index;
};

inline const bool& deque<bool>::iterator::operator*() const { return ((container->data)[data_index] >> bit_index) & 1; }
//inline const bool* deque<bool>::iterator::operator->() const { return &((*(container->data)[data_index] >> bit_index) & 1); }
inline deque<bool>::proxy::proxy(deque* _container, size_t _data_index, size_t _bit_index) : container(_container), data_index(_data_index), bit_index(_bit_index) { }
inline deque<bool>::const_proxy::const_proxy(const deque* _container, const size_t _data_index, const size_t _bit_index) : container(_container), data_index(_data_index), bit_index(_bit_index) { }
inline deque<bool>::proxy deque<bool>::operator[] (const size_t& indice)
{
    return proxy(this, data[indice], indice);
}
inline deque<bool>::const_proxy deque<bool>::operator[] (const size_t& indice) const
{
    return const_proxy(this, data[indice], indice);
}
inline deque<bool>::proxy::operator bool() const { return ((container->data)[data_index] >> bit_index) & 1; }
inline deque<bool>::const_proxy::operator bool() const { return ((container->data)[data_index] >> bit_index) & 1; }

inline const deque<bool>::proxy& deque<bool>::proxy::operator=(bool b) const
{
    return *this;
}

template<typename T>
deque<T>::deque() : data(new T[1]), cap(1), sz(0), left(-1), right(-1) { }
deque<bool>::deque() : cap(CHAR_BIT), sz(0), left(-1), right(-1) { }


template<typename T>
deque<T>::deque(const deque& other) : data(other.data), cap(other.cap), sz(other.sz), left(other.left), right(other.right) { }


template<typename T>
deque<T>::deque(deque&& other)
{
    using std::swap;
    swap(data, other.data);
    swap(cap, other.cap);
    swap(sz, other.sz);
    swap(left, other.left);
    swap(right, other.right);
}


template<typename T>
deque<T>::~deque()
{
    cap = 0;
    sz = 0;
    data = nullptr;
    left = -1;
    right = -1;
}
deque<bool>::~deque()
{
    cap = 0;
    sz = 0;
    data = nullptr;
    left = -1;
    right = -1;
}


template<typename T>
deque<T>& deque<T>::operator=(deque<T> other) &
{
    using std::swap;
    deque temp = copy(other);
    swap(data, other.data);
    swap(cap, other.cap);
    swap(sz, other.sz);
    swap(left, other.left);
    swap(right, other.right);
}


template<typename T>
T& deque<T>::operator[](const size_t& indice)
{
    if (indice >= cap) { throw; }
    else { return data[(left+indice)%cap]; }
}


template<typename T>
void deque<T>::double_cap_and_copy()
{
    auto copy = std::move(data);
    if (cap == 0) // if cap is 0, set to 1
    {
        data.reset(new T[1]);
        left = -1;
        right = -1;
        cap = 1;
    }
    else // else double the cap
    {
        data.reset(new T[cap*2]);
        if (left <= right) // move elements to new places if left <= right
        {
            for (size_t i = left; i <= right; ++i) { data[i] = copy[i]; }
        }
        else // if wrapping around, move in two pieces
        {
            size_t tracking_index = 0;
            for (size_t j = left; j <= cap-1; ++j) { data[tracking_index] = copy[j]; ++tracking_index; }
            for (size_t k = 0; k <= right; ++k) { data[tracking_index] = copy[k]; ++tracking_index; }
        }
        cap *= 2;
        left = 0;
        right = sz-1;
    }
}
void deque<bool>::double_cap_and_copy()
{
    auto copy = std::move(data);
    unsigned char* new_data = (unsigned char*)malloc(sizeof(CHAR_BIT) * 2);
    std::memcpy(new_data, data, sizeof(data));
    if (left <= right) // move elements to new places if left <= right
    {
        for (size_t i = left; i <= right; ++i)
        {
            size_t data_index = i / CHAR_BIT;
            size_t bit_index = i % CHAR_BIT;
            unsigned char old_val = (copy[data_index] >> bit_index) & 1;
            old_val ^= 1;
            //data[data_index] |= old_val << bit_index;
            data[data_index] = (data[data_index] & ~(1 << bit_index)) | (old_val << bit_index);
        }
    }
    else // if wrapping around, move in two pieces
    {
        size_t tracking_data_index = 0;
        size_t tracking_bit_index = 0;
        for (size_t j = left; j <= cap-1; ++j) // first piece, from left to right most
        {
            size_t data_index = j / CHAR_BIT;
            size_t bit_index = j % CHAR_BIT;
            unsigned char old_val = (copy[data_index] >> bit_index) & 1;
            old_val ^= 1;
            //data[tracking_data_index] |= old_val << tracking_bit_index;
            data[data_index] = (data[data_index] & ~(1 << bit_index)) | (old_val << bit_index);
            if (tracking_bit_index < 7)
            {
                ++tracking_bit_index;
            }
            else
            {
                tracking_bit_index = 0;
                ++tracking_data_index;
            }
        }
        for (size_t k = 0; k <= right; ++k) // second piece, from front most to right
        {
            size_t data_index = k / CHAR_BIT;
            size_t bit_index = k % CHAR_BIT;
            unsigned char old_val = (copy[data_index] >> bit_index) & 1;
            old_val ^= 1;
            data[data_index] = (data[data_index] & ~(1 << bit_index)) | (old_val << bit_index);
            if (tracking_bit_index < 7) { ++tracking_bit_index; }
            else { tracking_bit_index = 0; ++tracking_data_index; }
        }
    }
    cap *= 2;
    left = 0;
    right = sz-1;
}


template<typename T>
void deque<T>::push_back(const T& input)
{
    if (is_full()) // if current array is full, find way to reallocate more positions
    {
        double_cap_and_copy();
        push_back(input);
    }
    else // if not full, then no need to allocate new indices for the array
    {
        if (right+1 <= cap) // no matter wrapping around or not, if there is a space on the right of back, use it
        {
            data[right+1] = input;
            ++right;
            if (left == -1) { left = 0; }
        }
        else // if array is not full and nothing is on right of back, must have something empty on the left of array
        {
            data[0] = input;
            right = 0;
        }
        ++sz;
    }
}
void deque<bool>::push_back(const bool& input)
{
    if (is_full()) // if current array is full, find way to reallocate more positions
    {
        double_cap_and_copy();
        push_back(input);
    }
    else // if not full, then no need to allocate new indices for the array
    {
        if (right+1 <= cap) // no matter wrapping around or not, if there is a space on the right of back, use it
        {
            size_t target_data_index = (right) / CHAR_BIT;
            size_t target_bit_index = (right+1) % CHAR_BIT;
            data[target_data_index] = (data[target_data_index] & ~(1<<target_bit_index)) | (input << target_bit_index);
            ++right;
            if (left == -1) { left = 0; } // set to not empty
        }
        else // if array is not full and nothing is on right of back, must have something empty on the left of array
        {
            //data[0] |= input << 0;
            data[0] = (data[0] & ~(1 << 0)) | (input << 0);
            right = 0;
        }
        ++sz;
    }
}

template<typename T>
void deque<T>::push_front(const T& input)
{
    if (is_full()) // array full, more pos added and call recurssively
    {
        double_cap_and_copy();
        push_front(input);
    }
    else
    {
        if (left > 0) // if left not at front, use the space in front
        {
            data[left-1] = input;
            --left;
        }
        else // otherwise, wrap around
        {
            data[cap-1] = input;
            left = cap-1;
            if (right == -1) { right = 0; } // set to not empty
        }
        ++sz;
    }
}
void deque<bool>::push_front(const bool& input)
{
    if (is_full()) // array full, more pos added and call recurssively
    {
        double_cap_and_copy();
        push_front(input);
    }
    else
    {
        if (left > 0)  // if left not at front, use the space in front
        {
            size_t target_data_index = (left-1) / CHAR_BIT;
            size_t target_bit_index = (left-1) % CHAR_BIT;
            data[target_data_index] = (data[target_data_index] & ~(1 << target_bit_index)) | (input << target_bit_index);
            --left;
        }
        else// otherwise, wrap around
        {
            size_t target_data_index = (cap-1) / CHAR_BIT;
            size_t target_bit_index = (cap-1) % CHAR_BIT;
            data[target_data_index] = (data[target_data_index] & ~(1 << target_bit_index)) | (input << target_bit_index);
            left = cap-1;
            if (right == -1) { right = 0; } // set to not empty
        }
        ++sz;
    }
}


template<typename T>
void deque<T>::pop_back()
{
    --sz;
    if (sz == 0) { left = -1; right = -1; } // set to empty
    else
    {
        if (right != 0) { --right; } // new right
        else { right = cap-1; } // new right
    }
}
void deque<bool>::pop_back()
{
    --sz;
    if (sz == 0) { left = -1; right = -1; } // set to empty
    else
    {
        if (right != 0) { --right; } // new right
        else { right = cap-1; } // new right
    }
}


template<typename T>
void deque<T>::pop_front()
{
    --sz;
    if (sz == 0) { left = -1; right = -1; } // set to empty
    else
    {
        if (left != cap-1) { ++left; } // new left
        else { left = 0; } // new left
    }
}
void deque<bool>::pop_front()
{
    --sz;
    if (sz == 0) { left = -1; right = -1; } // set to empty
    else
    {
        if (left != cap-1) { ++left; } // new left
        else { left = 0; } // new left
    }
}


template<typename T>
const typename deque<T>::iterator deque<T>::begin() { return iterator(this, left); } //return begin pos
template<typename T>
const typename deque<T>::const_iterator deque<T>::begin() const { return const_iterator(this, left); }// return begin pos
const typename deque<bool>::iterator deque<bool>::begin()
{
    // return begin pos
    return iterator(this, left/CHAR_BIT, left%CHAR_BIT);
}
//const typename deque<bool>::const_iterator deque<bool>::begin() const { return const_iterator(this, left/CHAR_BIT, left%CHAR_BIT); }


template<typename T>
const typename deque<T>::iterator deque<T>::end() { return iterator(this, -1); } // return end pos
template<typename T>
const typename deque<T>::const_iterator deque<T>::end() const { return const_iterator(this, -1); } // return end pos
const typename deque<bool>::iterator deque<bool>::end() { return iterator(this, -1, -1); } // return end pos
//const typename deque<bool>::const_iterator deque<bool>::end() const { return const_iterator(this, -1); }


template<typename T>
typename deque<T>::iterator& deque<T>::iterator::operator++()
{
    if (pointing_index == container->right) { pointing_index = -1; } // next is end
    else
    {
        if (pointing_index+1 > container->cap-1) { pointing_index = 0; } // new pointing index
        else { ++pointing_index; }
    }
    return *this;
}
template<typename T>
typename deque<T>::const_iterator& deque<T>::const_iterator::operator++()
{
    if (pointing_index == container->right) { pointing_index = -1; } // pass the end
    else
    {
        if (pointing_index+1 > container->cap-1) { pointing_index = 0; } // new poitnting index
        else { ++pointing_index; }
    }
    return *this;
}
typename deque<bool>::iterator& deque<bool>::iterator::operator++()
{
    if (data_index == -1 || bit_index == -1) { } // pass the end
    else
    {
        int pointing_index = data_index * CHAR_BIT + bit_index;
        if (pointing_index == container->right) { data_index = -1; bit_index = -1; } // pass the end
        else
        {
            if (pointing_index+1 > container->cap-1) { data_index = 0; bit_index = 0; } // new pointing pos
            else { ++pointing_index; data_index = pointing_index/CHAR_BIT; bit_index = pointing_index%CHAR_BIT; }  // new pointing pos
        }
    }
    return *this;
}


template<typename T>
typename deque<T>::iterator deque<T>::iterator::operator++(int)
{
    // use prefix to define
    iterator temp = *this;
    ++(*this);
    return temp;
}
template<typename T>
typename deque<T>::const_iterator deque<T>::const_iterator::operator++(int)
{
    // use prefix to define
    const_iterator temp = *this;
    ++(*this);
    return temp;
}
typename deque<bool>::iterator deque<bool>::iterator::operator++(int)
{
    // use prefix to define
    iterator temp = *this;
    ++(*this);
    return temp;
}


template<typename T>
typename deque<T>::iterator& deque<T>::iterator::operator--()
{
    if (pointing_index == container->left) { pointing_index = -1; } // before the begin
    else
    {
        if (pointing_index == 0) { pointing_index = container->cap-1; } // new pointing pose
        else { --pointing_index; }
    }
    return *this;
}
template<typename T>
typename deque<T>::const_iterator& deque<T>::const_iterator::operator--()
{
    if (pointing_index == container->left) { pointing_index = -1; }  // before the begin
    else
    {
        if (pointing_index == 0) { pointing_index = container->cap-1; }  // new pointing pose
        else { --pointing_index; }
    }
    return *this;
}
typename deque<bool>::iterator& deque<bool>::iterator::operator--()
{
    if (data_index == -1 || bit_index == -1) { }
    else
    {
        int pointing_index = data_index * CHAR_BIT + bit_index;
        if (pointing_index == container->left) { data_index = -1; bit_index = -1; } // before the begin
        else
        {
            if (pointing_index == 0) { pointing_index = container->cap; }  // new pointing pose
            else { --pointing_index; }
            data_index = pointing_index/CHAR_BIT;
            bit_index = pointing_index%CHAR_BIT;
        }
    }
    return *this;
}


template<typename T>
typename deque<T>::iterator deque<T>::iterator::operator--(int)
{
    // use prefix to define
    iterator temp = *this;
    --(*this);
    return temp;
}
template<typename T>
typename deque<T>::const_iterator deque<T>::const_iterator::operator--(int)
{
    // use prefix to define
    const_iterator temp = *this;
    --(*this);
    return temp;
}
typename deque<bool>::iterator deque<bool>::iterator::operator--(int)
{
    // use prefix to define
    iterator temp = *this;
    --(*this);
    return temp;
}


template<typename T>
const bool deque<T>::iterator::operator==(iterator other) const
{
    // return if two iters are the same
    // both being nullptr are not the same
    if (other.container == nullptr || container == nullptr) { return false; }
    // everything same is the same
    else if (other.container == container && other.pointing_index == pointing_index) { return true; }
    // anything not same is not same
    else { return false; }
}
template<typename T>
const bool deque<T>::const_iterator::operator==(const_iterator other) const
{
    // return if two iters are the same
    // both being nullptr are not the same
    if (other.container == nullptr || container == nullptr) { return false; }
    // everything same is the same
    else if (other.container == container && other.pointing_index == pointing_index) { return true; }
    // anything not same is not same
    else { return false; }
}
const bool deque<bool>::iterator::operator==(iterator other) const
{
    // return if two iters are the same
    // both being nullptr are not the same
    if (other.container == nullptr || container == nullptr) { return false; }
    // everything same is the same
    else if (other.container == container && other.data_index == data_index && other.bit_index == bit_index) { return true; }
    // anything not same is not same
    else { return false; }
}


template<typename T>
const bool deque<T>::iterator::operator!=(iterator other) const
{
    // return if two iters are not same
    // both being nullptr are not the same
    if (other.container == nullptr || container == nullptr) { return true; }
    // everything same is not "not the same"
    else if (other.container == container && other.pointing_index == pointing_index) { return false; }
    // anything not same is not same
    else { return true; }
}
template<typename T>
const bool deque<T>::const_iterator::operator!=(const_iterator other) const
{
    // return if two iters are not same
    // both being nullptr are not the same
    if (other.container == nullptr || container == nullptr) { return true; }
    // everything same is not "not the same"
    else if (other.container == container && other.pointing_index == pointing_index) { return false; }
    // anything not same is not same
    else { return true; }
}
const bool deque<bool>::iterator::operator!=(iterator other) const
{
    // return if two iters are not same
    // both being nullptr are not the same
    if (other.container == nullptr || container == nullptr) { return true; }
    // everything same is not "not the same"
    else if (other.container == container && other.data_index == data_index && other.bit_index == bit_index) { return false; }
    // anything not same is not same
    else { return true; }
}


template<typename T>
const T deque<T>::get_sum() const
{
    T sum = 0;
    if (cap == 0) { return 0; } // return 0 if empty
    else
    {
        // add from left most to right most, two conditions specifying is wrapping around scenario
        if (right >= left) { for (int i = left; i <= right; ++i) { sum += data[i]; } } // not wrapping around
        else // wrapping around
        {
            for (int i = 0; i < cap && (i <= right || i >= left); ++i) { sum += data[i]; }
        }
    }
    return sum;
}

template<typename T>
const T sum(const deque<T>& target) { return target.get_sum(); } // call member helper function to do the work

#endif /* specialize_deque_h */
