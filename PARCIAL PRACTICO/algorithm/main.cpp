#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

//algorithm implement from https://www.cplusplus.com/reference/algorithm/make_heap/
template <class RandomAccessIterator, class Compare>
void make_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp){ //O(n)
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

template <class RandomAccessIterator, class Compare>
void push_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp){ //O(log n)
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
}

template <class RandomAccessIterator, class Compare>
void pop_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp){ //O(log n)
    std::iter_swap(first, last - 1); //swap first and last element
    auto len = last - first - 1; //size of the heap
    auto root = first; //root of the subtree
    while (true){ //while there are elements in the heap
        auto child = root * 2 + 1; //left child of the root
        if (child < first + len){ //if left child exists
            if (child + 1 < first + len && comp(*(child + 1), *child)) //if right child exists and is smaller than left child
                ++child; //child is right child
            if (comp(*child, *root)){ //if child is smaller than root
                std::iter_swap(root, child); //swap child and root
                root = child; //root is now child
                child = root * 2 + 1; //left child of the root
            }
        }
        return; //if child is not smaller than root, then we are done
    }
}

template <class RandomAccessIterator, class Compare>
void sort_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp){ //O(n log n)
    while (last - first > 1){
        pop_heap(first, last--, comp);
    }
}

void test_make(){
    // generate random values
    std::vector<int> v(10000000);
    for (int i = 0; i < 10000000; ++i) v[i] = rand() % 100;
    std::cout << '\n';
    // make heap
    std::less<int> comp;
    std::make_heap(v.begin(), v.end(), comp);
    std::cout << std::endl;

}

void test_push(){
    // generate random values
    std::vector<int> v(10000000);
    for (int i = 0; i < 10000000; ++i) v[i] = rand() % 100;
    std::cout << '\n';
    // make heap
    std::less<int> comp;
    std::push_heap(v.begin(), v.end(), comp);
    std::cout << std::endl;
}

int main() {
    //measure time in microseconds
    /*auto start = std::chrono::high_resolution_clock::now();
    test_make();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "make_heap: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    test_push();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "push_heap: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;*/
    {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        test_make();

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "finished computation at " << std::ctime(&end_time)
                  << "elapsed time: " << elapsed_seconds.count() << "s\n"; //*/

    }

    {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        test_push();

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "finished computation at " << std::ctime(&end_time)
                  << "elapsed time: " << elapsed_seconds.count() << "s\n"; //*/
    }
    system("pause");
    return 0;
}