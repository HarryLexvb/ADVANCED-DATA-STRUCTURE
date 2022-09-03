//3.6 Preparing the code for future workgroups projects (figure 21, 22 and 23)

#include <iostream>

using namespace std;

// Code for the student implementing a Linked List
// File LinkedList.h
// Structure for nodes in a Linked List
template <typename T>
struct NODE
{
    T m_data; // The data goes here
    struct NODE<T> *m_pNext; // Pointer to the next node
    long id=0; // Node id
    NODE() // Constructor
            : m_data(0), m_pNext(NULL) {}
// More method go here
    void printNode()
    {
        cout << "Node id: " << id << " Data: " << m_data << endl;
    }
};
//long NODE::id = 0; // Inicialization of the node’s id

// Code for the student implementing a Linked List
// File LinkedList.h
template <typename T>
class CLinkedList
{
private: // Structure for nodes in a Linked List
    struct NODE
    {
        T m_data; // The data goes here
        struct NODE * m_pNext; // Pointer to the next Node
// Some methods go here
    };
    NODE* m_pRoot; // Pointer to the root
public:
    // More methods go here
    void insert(T data){
        NODE* newNode = new NODE;
        newNode->m_data = data;
        newNode->m_pNext = m_pRoot;
        m_pRoot = newNode;
    }
    void print_list(){
        NODE* temp = m_pRoot;
        while(temp != NULL){
            cout << temp->m_data << " ";
            temp = temp->m_pNext;
        }
        cout << endl;
    }
};

// Code for the student implementing a Binary Tree
// File BinaryTree.h
template <typename T>
class CBinaryTree
{
private: // Structure for nodes in a Binary Tree
    struct NODE
    {
        T m_data; // The data goes here
        struct NODE *m_pLeft, *m_pRight;// Pointer to the left and right node
// Some methods go here
    };
    NODE* m_pRoot; // Pointer to the root
public: // More methods go here
    void insert(T data){
        NODE* newNode = new NODE;
        newNode->m_data = data;
        newNode->m_pLeft = NULL;
        newNode->m_pRight = NULL;
        if(m_pRoot == NULL){
            m_pRoot = newNode;
        }else{
            NODE* temp = m_pRoot;
            while(temp != NULL){
                if(data < temp->m_data){
                    if(temp->m_pLeft == NULL){
                        temp->m_pLeft = newNode;
                        break;
                    }else{
                        temp = temp->m_pLeft;
                    }
                }else{
                    if(temp->m_pRight == NULL){
                        temp->m_pRight = newNode;
                        break;
                    }else{
                        temp = temp->m_pRight;
                    }
                }
            }
        }
    }
    void print_tree(){
        NODE* temp = m_pRoot;
        while(temp != NULL){
            cout << temp->m_data << " ";
            temp = temp->m_pRight;
        }
        cout << endl;
    }
};

int main(){

    cout << "list: " << endl;
    CLinkedList<int> list{};
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.print_list();

    cout << "tree: " << endl;
    CBinaryTree<int> tree{};
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.print_tree();
    return 0;
}