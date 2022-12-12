#include <iostream>
#include <atomic>
#include <random>
#include <chrono>
#include <thread>
#include "concurrent_priority_queue.h"
#include <fstream>

std::random_device rd;
std::mt19937 gen(rd());

int random(int low, int high){
    std::uniform_int_distribution<> dis(low, high);
    return dis(gen);
}

float thread_test(unsigned int elem,int N_threads){

    concurrent_priority_queue<int> cpq;                              //create cpq
    std::atomic<bool> stop{ false };                              //atomic bool for stop
    unsigned int N_operation_per_thread = elem / N_threads;                                 //number of elements for each thread
    std::thread threads[N_threads];                                  //create threads

    std::chrono::time_point<std::chrono::system_clock> start, end;   //start and end time
    start = std::chrono::system_clock::now();                        //start time

    for (int i = 0; i < N_threads; i++){                             //for each thread
        threads[i] = std::thread([&cpq, &N_operation_per_thread](){             //create thread
            for (int i = 0; i < N_operation_per_thread; i++){                             //for each element
                cpq.push(random(1, N_operation_per_thread));           //push random element
            }
        });
    }

    /*for (int i = 0; i < N_threads; i++){                                              //for each thread
        threads[i].join();                                                            //join thread
    }*/

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "size: " << cpq.size() << std::endl;
    end = std::chrono::system_clock::now();                                           //end time
    std::chrono::duration<double> elapsed_seconds = end-start;                        //elapsed time
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);              //end time
    std::cout << "finished computation at " << std::ctime(&end_time)            //print end time
              << "elapsed time: " << elapsed_seconds.count() << "s\n";                //print elapsed time
    return elapsed_seconds.count();
}

void fake_pq_test1(){
    std::cout << "Fake queue test (int)" << std::endl;

    concurrent_priority_queue<int> q;
    for (int i: {1,8,5,6,3,4,0,9,7,2})
        q.push(i);
    std::cout << "Size: " << q.size() << std::endl;
    //print elements
    std:: cout << "print elements: \n";
    q.print2();
    std::cout << "\nSize: " << q.size() << std::endl;
}

void fake_pq_test2(){
    std::cout << "Fake queue test (char)" << std::endl;

    concurrent_priority_queue<char> q;
    for (int i: {'a','b','c','d','e','f','g','h','i','j'})
        q.push(i);

    std::cout << "Size: " << q.size() << std::endl;
    //print elements
    std:: cout << "print elements: \n";
    q.print2();
    std::cout << "\nSize: " << q.size() << std::endl;
}

int main(){
    /*fake_pq_test1();
    fake_pq_test2();
    thread_test(1000000,4);*/
    std::ofstream file;
    file.open(R"(C:\Users\win 10\Documents\CLION\Concurrent_Priority_Queue_V1\time_8_threads_v1.txt)");
    //int arr[] = {100, 500,1000, 5000, 10000, 50000, 100000, 500000,  1000000, 5000000, 10000000, 50000000, 100000000};
    int arr[] = {100, 500,1000, 5000, 10000, 50000, 100000, 250000,500000,  1000000, 2500000 ,5000000, 10000000};
    for (int i = 0; i < 13; ++i)
        file << arr[i] << " " << thread_test(arr[i],8) << std::endl;
    file.close(); // */
    return 0;
}