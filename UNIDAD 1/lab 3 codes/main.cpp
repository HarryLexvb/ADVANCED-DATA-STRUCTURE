#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <chrono>

using namespace std;
vector<vector<double>> dis;

int SIZE = 1000; // number of vectors to generate

int f(){
    return rand()%1000; // random number between 0 and 1000
}

template <class T>
T Distance(vector<T> a,vector<T> b){ // distance between two vectors
    T sum = 0;
    for(int i = 0; i < a.size(); ++i)
        sum += pow(a[i] - b[i], 2);
    return sqrt(sum);
}

bool Valid(double a){  // check if the distance is already in the vector
    for(auto i=dis.begin(); i!= dis.end(); i++) {
        if((*i)[0]==a)return false;
    }
    return true;
}

int main() {
    int n=50000; //dimension of the vector
    vector<double> C; // vector of distances
    vector<double> A(n);  // first vector

    auto start = chrono::high_resolution_clock::now(); // start the timer

    generate(A.begin(), A.end(), f); // generate random numbers for the first vector
    for(int j = 0; j < SIZE; ++j){ // generate SIZE vectors
        vector<double> B(n);  // second vector
        generate(B.begin(), B.end(), f);    // generate random numbers for the second vector
        C.push_back(Distance<double>(A,B)); // calculate the distance between the first vector and the new vector
    }

    for (auto i=C.begin(); i!= C.end(); ++i) { // for each distance in the vector
        if(Valid(*i)){
            int count = 0;
            auto j = i;
            while(j != C.end()){
                if(*j == *i) count++;
                ++j;
            }
            vector<double> tmp;
            tmp.push_back(*i); tmp.push_back(count);
            dis.push_back(tmp);
        }
    }
    auto stop = chrono::high_resolution_clock::now(); // stop the timer
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); // calculate the time
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl; // print the time


    /*fstream file;
    file.open(R"(C:\Users\win 10\Documents\UCSP\VI CICLO\EDA\trabajos del otro grupo de eda\info.txt)", ios::out);
    for(auto & di : dis)
        file << di[0] << "  " << di[1] << endl; // write the distances and the number of times they appear in the vector
    file.close();*/
}

