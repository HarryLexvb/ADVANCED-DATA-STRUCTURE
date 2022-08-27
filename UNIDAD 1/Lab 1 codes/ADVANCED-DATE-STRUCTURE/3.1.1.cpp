//3.1.1 Fixed size vectors
#include <iostream>

using namespace std;

int gVect[100]; // Buffer to save the elements
int gnCount; // Counter to know the number of elements used

void Insert(int elem)
{
    if( gnCount < 100 ) // we can only insert if there is space
        gVect[gnCount++] = elem; // Insert the element at the end
}

void Remove(int elem)
{
    int i;
    for( i = 0; i < gnCount; i++ )
    {
        if( gVect[i] == elem ) // Found the element
        {
            gVect[i] = gVect[--gnCount]; // Replace the element with the last one
            break;
        }
    }
}

void print()
{
    int i;
    for( i = 0; i < gnCount; i++ )
        cout << gVect[i] << " ";
    cout << endl;
}

int main()
{
    gnCount = 0;
    Insert(1);
    Insert(2);
    Insert(3);
    Insert(4);
    Insert(5);
    print();     
}

