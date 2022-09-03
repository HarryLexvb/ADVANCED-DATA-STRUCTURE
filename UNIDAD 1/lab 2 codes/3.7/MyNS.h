//
// Created by win 10 on 2/09/2022.
//

#ifndef SOLUCION_MYNS_H
#define SOLUCION_MYNS_H

// File MyNS.h
namespace MyNS
{
    int gnCount; // Global counter
// Some small function implemented inline
    double Addition(double a, double b) // Global function
    { return a+b; }
// Some prototypes
    long factorial(int n) // Global function{
    {
        if (n == 0)
            return 1;
        else
            return n * factorial(n-1);
    }
    class CTest
    {
    public:
        CTest();
        static void Method1();
    };

    CTest::CTest() { gnCount++; }
    void CTest::Method1() { gnCount++; }
// More variables, functions, methods, classes, structs go here
};

#endif //SOLUCION_MYNS_H
