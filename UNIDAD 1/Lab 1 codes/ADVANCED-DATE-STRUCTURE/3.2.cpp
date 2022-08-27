//3.2 Modular Programming
#include <iostream>

using namespace std;

struct SVector {
    int*m_pVect, // Pointer to the buffer
    m_nCount, // Control how many elements are actually used
    m_nMax, // Control how many are allocated as maximum
    m_nDelta; // To control the growing

    SVector(int nDelta = 10) {
        m_nCount = 0;
        m_nMax = 0;
        m_nDelta = nDelta;
        m_pVect = NULL;
    }

    ~SVector() {
        if (m_pVect != NULL) {
            delete[] m_pVect;
        }
    }

    void insert(SVector *pvect, int elem) {
        /*if (pvect->m_nCount == pvect->m_nMax) {
            pvect->m_nMax += pvect->m_nDelta;
            pvect->m_pVect = (int*)realloc(pvect->m_pVect, pvect->m_nMax * sizeof(int));
        }
        pvect->m_pVect[pvect->m_nCount] = elem;
        pvect->m_nCount++;*/
        if( pvect->m_nCount == pvect->m_nMax ) // Verify the overflow
            resize(pvect); // Resize the vector before inserting elem
// Insert the element at the end of the sequence
        pvect->m_pVect[pvect->m_nCount++] = elem;
    }

    void resize(SVector *pvect) {
        /*pvect->m_nMax = n;
        pvect->m_pVect = (int*)realloc(pvect->m_pVect, pvect->m_nMax * sizeof(int));*/
        pvect->m_nMax += pvect->m_nDelta; // Increase the size of the vector
        pvect->m_pVect = (int*)realloc(pvect->m_pVect, pvect->m_nMax * sizeof(int)); // Reallocate the memory
    }

    int Get(int nIndex) {
        if (nIndex < 0 || nIndex >= m_nCount) {
            return -1;
        }
        return m_pVect[nIndex];
    }

    int GetCount() {
        return m_nCount;
    }

    void Print() {
        for (int i = 0; i < m_nCount; i++) {
            cout << m_pVect[i] << " ";
        }
        cout << endl;
    }
};

int main(){
    SVector vect;
    vect.insert(&vect, 1);
    vect.insert(&vect, 2);
    vect.insert(&vect, 3);
    vect.insert(&vect, 4);
    vect.insert(&vect, 5);
    vect.insert(&vect, 6);
    vect.insert(&vect, 7);
    vect.insert(&vect, 8);
    vect.insert(&vect, 9);
    vect.insert(&vect, 10);
    vect.insert(&vect, 11);
    vect.Print();

}
