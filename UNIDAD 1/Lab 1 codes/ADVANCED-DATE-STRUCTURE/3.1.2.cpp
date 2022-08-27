//3.1.2 Dynamic Vectors and global variables
#include <iostream>

using namespace std;

int *gpVect = nullptr; // Dynamic buffer to save the elements int
int gnCount = 0; // Counter to know the number of used elements int
int gnMax = 0; // Variable containing the size of the allocated memory

void Resize()
{
    const int delta = 10; // Used to increase the vector size
    gpVect = static_cast<int *>(realloc(gpVect, sizeof(int) * (gnMax + delta)));
    int *pTemp, i;
    pTemp = new int[gnMax + delta]; // Alloc a new vector
    for(i = 0 ; i < gnMax ; i++) // Transfer the elements
        pTemp[i] = gpVect[i]; // we can also use the function memcpy
    delete [ ] gpVect; // delete the old vector
    gpVect = pTemp; // Update the pointer
    gnMax += delta; // The Max has to be increased by delta
}
void Insert(int elem)
{
    if( gnCount == gnMax ) // There is no space at this moment for elem
        Resize(); // Resize the vector before inserting elem
    gpVect[gnCount++] = elem; // Insert the element at the end of the sequence
}

void print()
{
    for(int i = 0 ; i < gnCount ; i++)
        cout << gpVect[i] << " ";
    cout << endl;
}

int main()
{
    int i;
    for(i = 1 ; i <= 20 ; ++i)
        Insert(i);

    print();
}