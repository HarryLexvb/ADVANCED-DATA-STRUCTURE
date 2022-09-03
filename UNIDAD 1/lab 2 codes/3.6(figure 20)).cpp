//3.6 Preparing the code for future workgroups projects

#include <iostream>
#include <vector>

using namespace std;

class CMyComplexDataStructure{
    vector<float> m_container;
public:
    void Insert(float fVal) { m_container.push_back(fVal); }
    template <typename ObjClass>
    void sumone(ObjClass funobj)
    {
        auto it = m_container.begin();
        for (; it != m_container.end() ; ++it)
            funobj(*it);
    }
    void print_1()
    {
        auto it = m_container.begin();
        for (; it != m_container.end() ; ++it)
            cout << *it << endl;
    }
};

template <typename objclass>
class FuncObjClass{
    objclass m_obj;
public:
    void operator ()(objclass& objinstance){
        objinstance++;
    }
};

//print function
void print_2(float fVal){
    cout << fVal << endl;
}

int main(int argc, char* argv[])
{
    CMyComplexDataStructure ds;
    ds.Insert(3.5);
    ds.Insert(4.5);
    ds.Insert(6.5);
    ds.Insert(3.9);
    FuncObjClass<float> x{};
    ds.sumone(x);
    //ds.print_1();
    ds.sumone(print_2);
    return 0;
}