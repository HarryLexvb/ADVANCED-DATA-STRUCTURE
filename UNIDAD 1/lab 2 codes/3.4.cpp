// 3.4 Abstract Data Types
#include <iostream>

using namespace std;

template <class T> class CVector
{
private:
    T *m_pVect; // Pointer to the buffer
    int m_nCount{}, // Control how many elements are actually used
    m_nMax{}, // Control the number of allocated elements
    m_nDelta{}; // To control the growing
    void Init(int delta); // Init our private variables, etc
    void Resize(); // Resize the vector when occurs an overflow
public:
    explicit CVector(int delta = 10); // Constructor
    void Insert(T elem); // Insert a new element
    void print(); // Print the vector
// ...
};

// Class CVector implementation
template <class T>
CVector<T>::CVector(int delta)
{
    Init(delta);
}

template<class T>
void CVector<T>::Insert(T elem) {
    if( m_nCount == m_nMax ) // Verify the overflow
        Resize(); // Resize the vector before inserting elem
    m_pVect[m_nCount++] = elem; // Insert the element at the end
}

template<class T>
void CVector<T>::Init(int delta) {
    m_nCount = 0;
    m_nMax = 0;
    m_nDelta = delta;
    m_pVect = nullptr;
}

template<class T>
void CVector<T>::Resize() {
    m_nMax += m_nDelta; // Increase the number of allocated elements
    T *pNewVect = new T[m_nMax]; // Allocate a new buffer
    for( int i = 0; i < m_nCount; ++i ) // Copy the elements
        pNewVect[i] = m_pVect[i];
    delete[] m_pVect; // Free the old buffer
    m_pVect = pNewVect; // Update the pointer
}

template<class T>
void CVector<T>::print() {
    for( int i = 0; i < m_nCount; ++i )
        cout << m_pVect[i] << " ";
    cout << endl;
}

int main(){
    CVector<int> v(5); // Create a vector with delta = 5
    for( int i = 0; i < 20; ++i ) // Insert 20 elements
        v.Insert(i);
    v.print(); // Print the vector
    return 0;
}