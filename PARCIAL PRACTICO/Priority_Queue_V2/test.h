//
// Created by win 10 on 20/10/2022.
//

#ifndef PRIORITY_QUEUE_V2_TEST_H
#define PRIORITY_QUEUE_V2_TEST_H
#include "C_priority_queue.h"
#include "C_vector.h"
#include <queue>
#include <vector>
/*
void fake_vector_test(){
    C_vector<int> v;
    v.push_back(12);
    v.push_back(6);
    v.push_back(20);
    v.push_back(45);
    v.push_back(2);
    v.push_back(9);

    std::cout << v[0] << std::endl;
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    v.pop_back();
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "empty: " << v.empty() << std::endl;
    std::cout << "front: " << v.front() << std::endl;
    std::cout << "back: " << v.back() << std::endl;
    std::cout << "data: " << v.data() << std::endl;
    std::cout << "at: " << v.at(1) << std::endl;


    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << std::endl;
    }
}
*/

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

#endif //PRIORITY_QUEUE_V2_TEST_H
