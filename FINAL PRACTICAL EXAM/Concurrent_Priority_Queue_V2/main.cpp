/*Author: Harold Alejandro Villanueva Borda
 * Date: 9/12/2022
 * Department: Computer Science
 * Curse: Advance Data Structures
 * Institution: San Pablo Catholic University of Arequipa
*/

#include <iostream>
#include <list>
#include <algorithm>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>
#include "Concurrent_PriorityQueue"

//random
std::random_device rd;
std::mt19937 gen(rd());

int random(int low, int high){
    std::uniform_int_distribution<> dis(low, high);
    return dis(gen);
}

//priority queue using thread test
double run_threaded_priority_queue_test(int N_operations, int N_thread){
    Concurrent_PriorityQueue<int, int> pq;
    //std::list<std::thread> threads;

    std::thread threads[N_thread];
    int N_operation_per_thread = N_operations/N_thread;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for (int i = 0; i < N_thread; ++i) {
        //for (int i = 0; i < N_thread; i++){
            //threads.emplace_back([&pq, &N_operations](){
            threads[i] = std::thread([&pq,&N_operation_per_thread](){
                for (int j = 0, k = 0; j < N_operation_per_thread; ++j) {
                    pq.push(k++, random(0, N_operation_per_thread));
                }
        });
        //std::cout << "size: " << pq.size() << std::endl;
    }
    for (auto& t : threads) {
        t.join();
    }

    /*for (int i = 0; i < N_thread; i++){
        threads[i].join();
    }*/

    //pq.print();

    std::cout << "size: " << pq.size() << std::endl;
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();
}

//priority queue test
void run_simple_priority_queue_test()
{
    Concurrent_PriorityQueue<int, int> pq = Concurrent_PriorityQueue<int, int>();
    pq.push(6, 3);
    pq.push(5, 4);
    pq.push(4, 8);
    pq.push(3, 6);
    pq.push(2, 1);
    pq.push(1, 9);

    //size of priority queue
    std::cout << std::endl << "Size of priority queue: " << pq.size() << std::endl;

    //show elements in priority queue
    std::cout << "Elements in priority queue: " << std::endl;
    /*while (!pq.empty())
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }*/
    pq.print2();
}

int main(){

    std::ofstream file;
    file.open(R"(C:\Users\win 10\Documents\CLION\Concurrent_Priority_Queue_V2\time_16_threads.txt)");
    int arr[] = {100, 500,1000, 5000, 10000, 50000, 100000, 250000,500000,  1000000, 2500000 ,5000000, 10000000};
    //int arr[] = {100, 500,1000, 5000, 10000, 50000, 100000, 500000,  1000000, 5000000, 10000000, 50000000, 100000000};
    for (int i = 0; i < 13; ++i)
        //file << arr[i] << " " << run_threaded_priority_queue_test(arr[i],8) << std::endl;
        file << arr[i] << " " << run_threaded_priority_queue_test(arr[i],16) << std::endl;
    file.close();
    //run_simple_priority_queue_test();
    return 0;
}