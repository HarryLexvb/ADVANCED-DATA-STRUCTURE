//
// Created by HarryLex on 9/12/2022.
//

#ifndef CONCURRENT_PRIORITY_QUEUE_V2_LOCK_FREE_SKIPLIST_H
#define CONCURRENT_PRIORITY_QUEUE_V2_LOCK_FREE_SKIPLIST_H

#include <string>
#include <iostream>
#include <limits>
#include <random>
#include <atomic>
#include <cstdint>

#define OUT_PARAM

/*
Markable_Reference is a wrapper for a pointer and a boolean value. It is used to implement the lock-free skip list.
 */

template <class T>
struct Markable_Reference{                                                                  // is a wrapper for a pointer and a boolean value

    T *val = nullptr;                                                                       // pointer to the object
    bool marked = false;                                                                    // boolean value
    Markable_Reference(Markable_Reference &other) : val(other.val), marked(other.marked) {} // copy constructor
    Markable_Reference(T *value, bool mark) : val(value), marked(mark) {}                   // constructor
};

/*
Atomic_Markable_Reference is a wrapper for a Markable_Reference object and provides atomic operations on it.
It is used to implement the lock-free skip list.
*/

// Atomic wrapper for Markable_Reference type
template <typename T>
struct AtomicMarkableReference{                                                          // is a wrapper for a pointer and a boolean value
    std::atomic<Markable_Reference<T> *> ref;                                            // pointer to the object

    AtomicMarkableReference() {                                                          // default constructor
        ref.store(new Markable_Reference<T>(nullptr, false));                            // store pointer to the object
    }

    AtomicMarkableReference(T *val, bool marked){                                      // constructor
        ref.store(new Markable_Reference<T>(val, marked));                             // store pointer to the object
    }

    ~AtomicMarkableReference(){                                                        // destructor
        Markable_Reference<T> *temp = ref.load();                                      // load pointer to the object
        delete temp;                                                                   // delete pointer to the object
    }

    T *get_reference() { return ref.load()->val; }                                    // get pointer to the object

    // Stores the value of this references marked flag in reference
    T *get(OUT_PARAM bool &mark){                                               // get pointer to the object and marked flag
        Markable_Reference<T> *temp = ref.load();                               // load pointer to the object
        mark = temp->marked;                                                    // store marked flag
        return temp->val;                                                       // return pointer to the object
    }

    void set(T *value, bool mark){                                           // set pointer to the object and marked flag
        Markable_Reference<T> *curr = ref.load();                            // load pointer to the object
        if (value != curr->val or mark != curr->marked) {                    // if pointer to the object or marked flag is changed
            ref.store(new Markable_Reference<T>(value, mark));               // store pointer to the object and marked flag
        }
    }

    void set_marked(bool mark){                                       // set marked flag
        Markable_Reference<T> *curr = ref.load();                     // load pointer to the object
        if (mark != curr->marked){                                    // if marked flag is changed
            ref.store(new Markable_Reference<T>(curr->val, mark));    // store pointer to the object and marked flag
        }
    }

    // Atomically sets the value of both the reference and mark to the given
    // update values if the current reference is equal to the expected reference
    // and the current mark is equal to the expected mark. returns true on success
    bool compare_and_swap(T *expected_value, bool expected_mark, T *new_value, bool new_mark){  // compare and swap
        Markable_Reference<T> *curr = ref.load();                                               // load pointer to the object
        return (expected_value == curr->val and expected_mark == curr->marked and
                ((new_value == curr->val and new_mark == curr->marked) or                             // if already equal, return true by shortcircuiting
                 ref.compare_exchange_strong(curr, new Markable_Reference<T>(new_value, new_mark)))); // otherwise, attempt compare and swap
    }
};

/*
Node is a node in the lock-free skip list. It contains a key and a value. It also contains an array of Atomic_Markable_Reference objects.
 Each Atomic_Markable_Reference object points to the next node in the skip list.
    The number of Atomic_Markable_Reference objects is equal to the height of the node.

    The height of a node is a random number between 1 and MAX_HEIGHT.
    The height of the head node is MAX_HEIGHT.
    The height of the tail node is 1.
 */

// BEGIN SKIP LIST IMPLEMENTATION
#define SKIPLIST_TEMPLATE_ARGS template <typename KeyType, typename ValueType>  // template arguments for the skip list class
#define SKIPLIST_TYPE SkipList<KeyType, ValueType>                              // type of the skip list class

/*
 skip list node class template definition for a key of type KeyType and a value of type ValueType
 */

/*
    The skip list is a concurrent priority queue. It is implemented using the algorithm described in the paper "A Pragmatic Implementation of
    Non-Blocking Linked-Lists" by Maged M. Michael. The skip list is a concurrent priority queue. It is implemented using the algorithm described
    in the paper "A Pragmatic Implementation of Non-Blocking Linked-Lists" by Maged M. Michael.

 */

SKIPLIST_TEMPLATE_ARGS
class SkipList{
private:

    /*
     SkipNode is a node in the lock-free skip list. It contains a key and a value. It also contains an array of Atomic_Markable_Reference objects. Each Atomic_Markable_Reference object points to the next node in the skip list.
     */

    struct SkipNode{
        // Constructor for standard nodes
        SkipNode(const KeyType k, const ValueType &v, const int forward_size) : key(k), value(v), top_level(forward_size){
            intialize_forward(forward_size, nullptr); // initialize forward array
        }

        // Constructor for sentinel nodes head  and NIL (NIL: end of list)
        SkipNode(const KeyType k, const int forward_size, SkipNode *forward_target) : key(k), top_level(forward_size){
            intialize_forward(forward_size, forward_target); // initialize forward array
        }
        ~SkipNode(){
            forward.clear(); // calls destructors on AtomicMarkableReferences
        }

        /*
         initialize_forward initializes the forward array of the node. It is called by the constructors of the node.
         It takes the size of the forward array and a pointer to the node to which the forward array should point.
         It initializes the forward array to point to the node passed as the second argument. If the second argument is nullptr,
         it initializes the forward array to point to nullptr. It is used to initialize the forward array of the head node and the tail node.
         It is also used to initialize the forward array of a standard node. The forward array of a standard node is initialized to point to nullptr.
         It is used to initialize the forward array of a standard node. The forward array of a standard node is initialized to point to nullptr.
         */

        void intialize_forward(const int forward_size, SkipNode *forward_target){    // initialize forward array
            forward = std::vector<AtomicMarkableReference<SkipNode>>(forward_size);  // initialize forward array
            for (auto i = 0; i != forward_size; ++i){                                // for each element in the forward array
                forward[i].set(forward_target, false);                               // set forward array element to forward_target
            }
        }

        KeyType key;                       // key of the node
        ValueType value;                   // value of the node

        int top_level;

        // Vector of atomic, markable (logical delete) forward nodes
        std::vector<AtomicMarkableReference<SkipNode>> forward;
    };

public:
    SkipList();
    ~SkipList(){
        delete head;
        delete NIL;
    };
    ValueType *find_wait_free(const KeyType search_key) const;
    bool find_with_gc(const KeyType search_key, SkipNode **preds, SkipNode **succs); // not const, will delete marked nodes
    void insert(const KeyType key, const ValueType &val);
    bool remove(const KeyType key);
    void print(std::ostream &os) const;
    uint32_t size() const;
    //top function
    ValueType& Top() const{
        return head->forward[0].get_reference()->value;
    }
    //pop_front function
    void pop_front(){
        SkipNode* temp = head->forward[0].get_reference();
        head->forward[0].set(temp->forward[0].get_reference(), false);
        delete temp;
    }
    //return size of the list
    size_t Size() const{
        size_t size = 0;
        SkipNode* temp = head->forward[0].get_reference();
        while(temp != NIL){
            size++;
            temp = temp->forward[0].get_reference();
        }
        return size;
    }
    void print();
private:
    int random_level() const;
    SkipNode *head;
    SkipNode *NIL;

    static const int max_levels = 16;
    const float probability;
};

SKIPLIST_TEMPLATE_ARGS
SKIPLIST_TYPE::SkipList() : probability(0.5){                                           // constructor for the skip list class
    NIL = new SkipNode(std::numeric_limits<KeyType>::max(), max_levels + 1, nullptr);   // create sentinel node NIL
    head = new SkipNode(std::numeric_limits<KeyType>::min(), max_levels + 1, NIL);      // create sentinel node head
}

// TODO optimize http://ticki.github.io/blog/skip-lists-done-right/
SKIPLIST_TEMPLATE_ARGS
int SKIPLIST_TYPE::random_level() const{                       // generate random level for new node
    int new_level = 1;

    while (((double)rand() / (RAND_MAX)) < probability){       // while random number is less than probability
        ++new_level;                                           // increment new level
    }
    return (new_level > max_levels ? max_levels : new_level);  // return new level
}

SKIPLIST_TEMPLATE_ARGS
void SKIPLIST_TYPE::print(std::ostream &os) const{                   // print the skip list
    bool marked = false;                                             // initialize marked flag
    auto x = head->forward[0].get(marked);                           // get pointer to the first node
    auto succ = x;                                             // initialize successor pointer
    while (succ->key != std::numeric_limits<KeyType>::max()){        // while successor is not sentinel node NIL
        // traverse to the right
        x = succ;                                                    // set x to successor
        succ = succ->forward[0].get(marked);                         // get pointer to the next node
        if (!marked){                                                // if node is not marked
            os << "Key: " << x->key << " Value: " << x->value << " Level: " << x->top_level << std::endl; // print node
        }
        else{
            os << "DELETED Key: " << x->key << " Value: " << x->value << " Level: " << x->top_level << std::endl; // print node
        }
    }
}

SKIPLIST_TEMPLATE_ARGS
uint32_t SKIPLIST_TYPE::size() const{                                                   // return size of the skip list
    auto x = head;                                                       // initialize x to head
    uint32_t size = 0;                                                                  // initialize size to 0
    bool marked = false;                                                                // initialize marked flag
    while (x->forward[0].get_reference()->key != std::numeric_limits<KeyType>::max()){  // while x is not sentinel node NIL
        x = x->forward[0].get(marked); // traverse to the right
        if (!marked)
            ++size;                   // if node is not marked, increment size
    }
    return size;
}

/*
 find_wait_gc: find a node with key search_key in the skip list. This function is wait-free.
 It is used by the find function. It takes a key to search for as an argument.
 It returns a pointer to the node with the key search_key if it exists in the skip list.
 If the node with the key search_key does not exist in the skip list, it returns nullptr.
 It is used by the find function. It is wait-free. It is used by the find function. It is wait-free.
 */

SKIPLIST_TEMPLATE_ARGS
bool SKIPLIST_TYPE::find_with_gc(const KeyType search_key, SkipNode **preds, SkipNode **succs){ // not const, will delete marked nodes
    bool marked = false;                                                                        // initialize marked flag
    bool snip;                                                                                  // initialize snip flag

    SkipNode *pred, *curr, *succ;                                                               // initialize pred, curr, succ pointers

    RETRY:                                                                                     // retry label
    pred = head;                                                                               // set pred to head
    for (auto level = max_levels; level >= 0; --level){                                   // for each level
        curr = pred->forward[level].get_reference();                                           // set curr to pred's forward pointer
        while (true){                                                                          // while true
            // delete marked nodes
            succ = curr->forward[level].get(marked);                                          // set succ to curr's forward pointer
            while (marked){                                                                   // while curr is marked
                snip = pred->forward[level].compare_and_swap(curr, false, succ, false);       // set pred's forward pointer to succ
                if (!snip) goto RETRY;                                                        // if snip fails, retry
                    goto RETRY; // CAS failed, try again
                curr = pred->forward[level].get_reference();                                 // set curr to pred's forward pointer
                succ = curr->forward[level].get(marked);                                     // set succ to curr's forward pointer
            }
            if (curr->key < search_key){                                                   // if curr's key is less than search key
                pred = curr;                                                               // set pred to curr
                curr = succ;                                                               // set curr to succ
            }
            else{
                break;                                                                    // break out of while loop
            }
        }
        preds[level] = pred;                                                              // set preds[level] to pred
        succs[level] = curr;                                                              // set succs[level] to curr
    }
    return (curr->key == search_key);
}

SKIPLIST_TEMPLATE_ARGS
ValueType *SKIPLIST_TYPE::find_wait_free(const KeyType search_key) const{ // const, will not delete marked nodes
    bool marked = false;                                                  // initialize marked flag
    SkipNode *pred = head, *curr = nullptr, *succ = nullptr;              // initialize pred, curr, succ pointers
    // traverse from top of head
    for (int level = max_levels; level >= 0; --level){                   // for each level
        curr = pred->forward[level].get_reference();                     // set curr to pred's forward pointer
        while (true){                                                    // while true
            succ = curr->forward[level].get(marked);                     // set succ to curr's forward pointer
            while (marked){ // skip over marked nodes
                curr = pred->forward[level].get_reference();             // set curr to pred's forward pointer
                succ = curr->forward[level].get(marked);                 // set succ to curr's forward pointer
            }
            if (curr->key < search_key){                                 // if curr's key is less than search key
                pred = curr;                                             // set pred to curr
                curr = succ;                                             // set curr to succ
            }
            else{
                break;
            }
        }
    }
    return (curr->key == search_key ? &curr->value : nullptr);    // return pointer to value if found, else return nullptr
}

/*
 find_with_gc() and find_wait_free() are similar, but find_with_gc() will delete marked nodes while find_wait_free() will not.
 gc: garbage collection
 */

SKIPLIST_TEMPLATE_ARGS
void SKIPLIST_TYPE::insert(const KeyType key, const ValueType &val){ // insert key, value pair into skip list
    int top_level = random_level();                                 // generate random level for new node
    SkipNode *preds[max_levels + 1];                                // initialize preds array
    SkipNode *succs[max_levels + 1];                                // initialize succs array
    auto new_node = new SkipNode(key, val, top_level);              // create new node
    while (true){                                                   // while true
        bool found = find_with_gc(key, preds, succs);     // find key in skip list
        if (found){                                                 // if key is found
            delete new_node;                                        // delete new node
            return;                                                 // return
        }
        else{                                                   // else key is not found
            for (auto level = 0; level < top_level; ++level){   // for each level in new node
                auto succ = succs[level];            // set succ to succs[level]
                new_node->forward[level].set(succ, false);      // set new node's forward pointer to succ
            }
            auto pred = preds[0];                                          // set pred to preds[0]
            auto succ = succs[0];                                          // set succ to succs[0]
            new_node->forward[0].set(succ, false);                                    // set new node's forward pointer to succ
            if (!pred->forward[0].compare_and_swap(succ, false, new_node, false)){    // if CAS fails
                continue; // CAS failed, try again
            }
            for (auto level = 0; level < top_level; ++level){   // for each level in new node
                while (true) {                                  // keep trying until we succeed
                    pred = preds[level];                        // set pred to preds[level]
                    succ = succs[level];                        // set succ to succs[level]
                    if (pred->forward[level].compare_and_swap(succ, false, new_node, false)) // if CAS succeeds
                        break;                                 // CAS succeeded, move to next level
                    find_with_gc(key, preds, succs); // CAS failed for upper level, search node to update preds and succs
                }
            }
            return; // insert succeeded
        }
    }
}


/*
    remove method is similar to find_with_gc() and find_wait_free(), but it will delete marked nodes. It will also mark nodes as deleted.
 */

SKIPLIST_TEMPLATE_ARGS
bool SKIPLIST_TYPE::remove(const KeyType key){// remove key from skip list
    SkipNode *preds[max_levels + 1];          // initialize preds array
    SkipNode *succs[max_levels + 1];          // initialize succs array
    SkipNode *succ;                           // initialize succ pointer
    while (true){                             // while true
        bool found = find_with_gc(key, preds, succs); // find key in skip list
        if (!found){                                            // if key is not found
            return false;                                       // nothing to delete
        }
        else{                                                   // else key is found
            auto node_to_remove = succs[0];

            // mark as deleted on higher levels
            bool marked = false;
            for (auto level = node_to_remove->top_level-1; level >= 1; --level){ // for each level in node to remove
                succ = node_to_remove->forward[level].get(marked);               // set succ to node to remove's forward pointer
                while (!marked){                                                 // while not marked
                    node_to_remove->forward[level].set_marked(true);             // mark node to remove's forward pointer
                    succ = node_to_remove->forward[level].get(marked);           // set succ to node to remove's forward pointer
                }
            }

            // bottom level
            marked = false;                                   // reset marked flag
            succ = node_to_remove->forward[0].get(marked);    // set succ to node to remove's forward pointer
            while (true){                                     // while true
                bool success = node_to_remove->forward[0].compare_and_swap(succ, false, succ, true); // try to mark node to remove's forward pointer
                succ = succs[0]->forward[0].get(marked);   // set succ to succs[0]'s forward pointer
                if (success){                              // this thread marked the node
                    // TODO we might call find here to physically remove nodes
                    // find_with_gc(key, preds, succs);
                    return true;                          // return true
                }
                else if (marked){ // another thread already deleted the node
                    return false; // return false
                }
            }
        }
    }
}

template<typename KeyType, typename ValueType>
void SkipList<KeyType, ValueType>::print() { // print skip list
    SkipNode *x = head;                      // set x to head
    bool marked = false;                     // initialize marked flag
    while (x->forward[0].get_reference()->key != std::numeric_limits<KeyType>::max()) { // while x's forward pointer is not tail
        x = x->forward[0].get(marked);       // traverse to the right
        std::cout << x->value << "->";       // print value
    }
    std::cout << std::endl;
}

#endif //CONCURRENT_PRIORITY_QUEUE_V2_LOCK_FREE_SKIPLIST_H
