//3.5 Design Patterns
#include <vector> // without .h
#include <list>
#include <iostream>

using namespace std;

template <typename Container>
void Write(Container &ds, ostream &os){
    auto it = ds.begin();
    for( ; it != ds.end() ; it++ )
        os << *it << "\n";
}

int main()
{
    list<float> MyList;
    vector<float> MyVector;
    for( int i = 0 ; i < 10 ; i++ )
    {
        MyList .push_back(i );
        MyVector.push_back(i + 50);
    }
    Write(MyList, cout);
    Write(MyVector, cout);
    return 0;
}