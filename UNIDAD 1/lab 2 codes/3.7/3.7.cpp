//3.7 Namespaces

#include <iostream>
#include "MyNS.h"

using namespace MyNS; // Using the namespace

int main(){
    // Using the namespace
    std::cout << "The factorial of 5 is " << factorial(5) << std::endl;
}