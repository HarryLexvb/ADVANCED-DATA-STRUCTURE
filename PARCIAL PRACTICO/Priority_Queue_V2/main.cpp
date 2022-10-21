#include "test.h"
#include <chrono>
#include <fstream>
double test(int size){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    fill_fake_queue(size);

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n"; //*/
    return elapsed_seconds.count();
}

int main(){

    real_queue_test();
    std::cout << "\n\n";
    fake_queue_test();

    //real_queue_test1();
    std::cout << "\n\n";
    //fake_queue_test1();

    /*
    std::ofstream file;
    file.open(R"(C:\Users\win 10\Documents\CLION\Priority_Queue_V2\time1.txt)");
    int arr[] = {100, 500,1000, 5000, 10000, 50000, 100000, 500000,  1000000, 5000000, 10000000, 50000000, 100000000};
    for (int i = 0; i < 13; ++i)
        file << arr[i] << " " << test(arr[i]) << std::endl;
    file.close(); // */
    //test(10000);
    system("pause");
    return 0;
}