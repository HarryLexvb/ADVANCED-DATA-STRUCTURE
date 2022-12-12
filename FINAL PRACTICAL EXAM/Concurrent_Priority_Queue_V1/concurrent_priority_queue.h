//
// Created by HarryLex on 9/12/2022.
//

#include <atomic>
#include <mutex>
#include "C_priority_queue.h"


#ifndef CONCURRENT_PRIORITY_QUEUE_V1_CONCURRENT_PRIORITY_QUEUE_H
#define CONCURRENT_PRIORITY_QUEUE_V1_CONCURRENT_PRIORITY_QUEUE_H

//concurrent priority queue
template <typename T, typename Compare=std::less<T>, typename A = std::allocator<T>>
class concurrent_priority_queue
{
public:
    concurrent_priority_queue() = default;                                              //default constructor
    concurrent_priority_queue(const concurrent_priority_queue&) = delete;               //copy constructor
    concurrent_priority_queue& operator=(const concurrent_priority_queue&) = delete;    //copy assignment
    concurrent_priority_queue(concurrent_priority_queue&&) = delete;                    //move constructor
    concurrent_priority_queue& operator=(concurrent_priority_queue&&) = delete;         //move assignment
    ~concurrent_priority_queue() = default;                                             //destructor

    void push(const T& value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);                               //lock mutex
        m_queue.push(value);                                                         //push value
    }

    void push(T&& value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);                              //lock mutex
        m_queue.push(std::move(value));                                             //push value
    }

    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);                             //lock mutex
        if (m_queue.empty())                                                       //if queue is empty
            return false;                                                          //return false
        value = std::move(m_queue.top());                                          //move top element to value
        m_queue.pop();                                                             //pop top element
        return true;                                                               //return true
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lock(m_mutex);                             //lock mutex
        if (m_queue.empty())                                                       //if queue is empty
            return std::shared_ptr<T>();                                           //return empty shared pointer
        std::shared_ptr<T> res(std::make_shared<T>(m_queue.top()));          //create shared pointer to top element
        m_queue.pop();                                                            //pop top element
        return res;                                                               //return shared pointer
    }

    /*T& top()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.top();
    }*/

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);                           //lock mutex
        return m_queue.empty();                                                  //return true if queue is empty
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);                         //lock mutex
        return m_queue.size();                                                 //return size of queue
    }

    //print elements
    void print_elements() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);                       //lock mutex
        m_queue.print_elements();                                            //print elements
    }

    void print2(){
        while(!m_queue.empty()){                                              //while queue is not empty
            std::cout << m_queue.top() << " ";                                //print top element
            m_queue.pop();                                                    //pop top element
        }
    }

private:
    C_priority_queue<T> m_queue;                                             //priority queue
    mutable std::mutex m_mutex;                                              //mutex
};

#endif //CONCURRENT_PRIORITY_QUEUE_V1_CONCURRENT_PRIORITY_QUEUE_H
