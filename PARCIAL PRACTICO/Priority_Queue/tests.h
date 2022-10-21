//
// Created by HarryLex on 18/10/2022.
//

#ifndef PRIORITY_QUEUE_TESTS_H
#define PRIORITY_QUEUE_TESTS_H

#include "C_priority_queue.h"
#include "C_vector.h"
#include <queue>
#include <vector>


template <class T>
void print_queue(T &q){
    while(!q.empty()){
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << std::endl;
}
void real_queue_test(){
    std::cout << "\nreal queue test" << std::endl;
    std::priority_queue<int> q;
    /*q.push(3);
    q.push(14);
    q.push(12);
    q.push(7);
    q.push(10);
    q.push(1);
    q.push(6);
    q.push(8);
    q.push(9);
    q.push(5);*/

    for (int i: {1,8,5,6,3,4,0,9,7,2})
        q.push(i);

    std::cout << "Size: " << q.size() << std::endl;
    std::cout << "Top: " << q.top() << std::endl;
    std::cout << "Empty?: " << q.empty() << std::endl;
    ///print elements
    std:: cout << "print elements: \n";
    print_queue(q);
    std::cout << "\nEmpty?: " << q.empty() << std::endl;
}
void fake_queue_test(){
    std::cout << "\nfake queue test" << std::endl;

    C_priority_queue<int> q;
    /*q.push(3);
    q.push(14);
    q.push(12);
    q.push(7);
    q.push(10);
    q.push(1);
    q.push(6);
    q.push(8);
    q.push(9);
    q.push(5);*/

    for (int i: {1,8,5,6,3,4,0,9,7,2})
        q.push(i);

    std::cout << "Size: " << q.size() << std::endl;
    std::cout << "Top: " << q.top() << std::endl;
    std::cout << "Empty?: " << q.empty() << std::endl;
    //print elements
    std:: cout << "print elements: \n";
    print_queue(q);
    std::cout << "\nEmpty?: " << q.empty() << std::endl;
}
void real_vector_test(){
    std::cout << "\nreal vector test" << std::endl;
    C_vector<int> v;
    v.push_back(12);
    v.push_back(6);
    v.push_back(20);
    v.push_back(45);

    std::cout <<"print" << std::endl;
    for (int i : v) {
        std::cout << i << std::endl;
    }

    std::cout << v.size() << std::endl; // 4
    v.pop_back(); //remove 45
    std::cout << v.back() << std::endl; //20
    std::cout << v.size() << std::endl; //3
    std::cout << v.empty() << std::endl; //false
    std::cout << v.front() << std::endl; //12

    std::cout <<"print" << std::endl;
    for (int i : v) {
        std::cout << i << std::endl;
    }
}
void fake_vector_test(){
    std::cout << "\nfake vector test" << std::endl;
    std::vector<int> v;
    v.push_back(12);
    v.push_back(6);
    v.push_back(20);
    v.push_back(45);

    //print vector
    for (int i : v) {
        std::cout << i << std::endl;
    }

    std::cout << v.size() << std::endl; // 4
    v.pop_back(); //remove 45
    std::cout << v.back() << std::endl; //20
    std::cout << v.size() << std::endl; //3
    std::cout << v.empty() << std::endl; //false
    std::cout << v.front() << std::endl; //12

    //print vector
    for (int i : v) {
        std::cout << i << std::endl;
    }
}
void real_queue_test1(){
    std::cout << "\nreal queue test" << std::endl;
    std::priority_queue<char> q;
    for (int i: {'a','b','c','d','e','f','g','h','i','j'})
        q.push(i);

    std::cout << "Size: " << q.size() << std::endl;
    std::cout << "Top: " << q.top() << std::endl;
    std::cout << "Empty?: " << q.empty() << std::endl;
    ///print elements
    std:: cout << "print elements: \n";
    print_queue(q);
    std::cout << "\nEmpty?: " << q.empty() << std::endl;
}
void fake_queue_test1(){
    std::cout << "\nfake queue test" << std::endl;

    C_priority_queue<char> q;
    for (int i: {'a','b','c','d','e','f','g','h','i','j'})
        q.push(i);

    std::cout << "Size: " << q.size() << std::endl;
    std::cout << "Top: " << q.top() << std::endl;
    std::cout << "Empty?: " << q.empty() << std::endl;
    ///print elements
    std:: cout << "print elements: \n";
    print_queue(q);
    std::cout << "\nEmpty?: " << q.empty() << std::endl;
}

void fill_fake_queue(int size){
    C_priority_queue<int> q;
    for (int i = 0; i < size; ++i)
        q.push(rand() % 100 + 1);

    std::cout << "Size: " << q.size() << std::endl;
    /*std::cout << "Top: " << q.top() << std::endl;
    std::cout << "Empty?: " << q.empty() << std::endl;*/
    //print elements
    //std:: cout << "print elements: \n";
    //print_queue(q);
}
void fill_real_queue(int size){
    std::priority_queue<int> q;
    for (int i = 0; i < size; ++i)
        q.push(rand() % 100 + 1);

    /*std::cout << "Size: " << q.size() << std::endl;
    std::cout << "Top: " << q.top() << std::endl;
    std::cout << "Empty?: " << q.empty() << std::endl;*/
    //print elements
    //std:: cout << "print elements: \n";
    //print_queue(q);
}

#endif //PRIORITY_QUEUE_TESTS_H
