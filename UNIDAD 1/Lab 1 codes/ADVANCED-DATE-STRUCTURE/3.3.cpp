//3.3 Object Oriented Programming
#include <iostream>

using namespace std;

// Class CVector definition
class CVector
{
private:
    int *m_pVect{}, // Pointer to the buffer
    m_nCount{}, // Control how many elements are actually used
    m_nMax{}, // Control how many are allocated as maximum
    m_nDelta{}; // To control the growing
    void Init(int delta); // Init our private variables, etc
    void Resize(); // Resize the vector when occurs an overflow
public:
    explicit CVector(int delta = 10); // Constructor
    void Insert(int elem); // Insert a new element
    void Print(); // Print the vector
// More methods go here
};

CVector::CVector(int delta) {
    Init(delta); // Init the private variables
}

void CVector::Insert(int elem)
{
    Resize(); // Resize the vector before inserting elem
    m_pVect[m_nCount++] = elem; // Insert the element at the end
}

void CVector::Init(int delta) {
    m_nCount = 0; // No elements yet
    m_nMax = 0; // No elements yet
    m_nDelta = delta; // Set the delta
    m_pVect = nullptr; // No buffer yet
}

void CVector::Resize() {
    int *pNewVect; // Pointer to the new buffer
    m_nMax += m_nDelta; // Increase the maximum
    pNewVect = new int[m_nMax]; // Allocate the new buffer
    for(int i = 0; i < m_nCount; i++) // Copy the old buffer
        pNewVect[i] = m_pVect[i];
    delete [] m_pVect; // Free the old buffer
    m_pVect = pNewVect; // Set the new buffer
}

void CVector::Print() {
    for(int i = 0; i < m_nCount; i++)
        cout << m_pVect[i] << " ";
    cout << endl;

}

int main(){
    CVector v(5); // Create a vector with delta = 5
    for(int i = 0; i < 20; i++) // Insert 20 elements
        v.Insert(i);
    v.Print(); // Print the vector
    return 0;
}

