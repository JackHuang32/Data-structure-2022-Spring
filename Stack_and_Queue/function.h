#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <string>
#include<iostream>
using namespace std;

// TODO: Implement all member functions in BaseStack
template < class T >
class BaseStack
{
public:
    // Constructor
    BaseStack();

    // Destructor
    ~BaseStack();

    // Check if the stack is empty
    bool empty();

    // Return the size of the stack
    int size();

    // Return the top element
    T& top();

    // Insert a new element at top
    void push(const T& item);

    // Delete one element from top
    void pop();

private:
    T* _stack;
    int _top;
    int capacity;
};

// TODO: Implement all member functions in BaseQueue
template < class T >
class BaseQueue
{
public:
    // Constructor
    BaseQueue();

    // Destructor
    ~BaseQueue();

    // Check if the stack is empty
    bool empty();

    // Return the size of the queue
    int size();

    // Return the front element
    T& front();

    // Insert a new element at rear
    void push(const T& item);

    // Delete one element from front
    void pop();

private:
    T* _queue;
    int _front, _rear;
    int capacity;
};

// TODO: Implement five types of cards
// card type of "INSERT"
void insert(int L);

// card type of "BOTTOM_ROW"
// The function name of "first_row" is actually misleading.
// Actually, you need to implement card type of "BOTTOM_ROW" in this function.
// Also, we purposely design the function to have return type of string,
// although we do not have a variable to receive the return value in partial judge code.
// You can think of the reason for having such design.
string first_row(int L, bool print = false);

// card type of "QUERY"
void query(int L);

// card type of "FLUSH"
void flush();

// card type of "RESET"
void reset(int L);

template<class T>
BaseQueue<T>::BaseQueue():capacity{2000000},_queue{new T[2000000]},_front{0},_rear{0}{cout<<"constructor"<<endl;}

    // Destructor
template<class T>
BaseQueue<T>::~BaseQueue()
{
    delete []_queue;
}

    // Check if the stack is empty
template<class T>
bool BaseQueue<T>:: empty()
{
    if(_front==_rear)return true;
    else return false;
}

    // Return the size of the queue
template<class T>
int BaseQueue<T>:: size()
{
    return _rear-_front;
}

    // Return the front element
template<class T>
T& BaseQueue<T>:: front(){return _queue[_front];}

    // Insert a new element at rear
template<class T>
void BaseQueue<T>:: push(const T& item)
{
    _queue[_rear+1]=T(item);
    _rear++;
}

    // Delete one element from front
template<class T>
void BaseQueue<T>:: pop()
{
    _queue[_front]=-1;
    _front+=1;
}

template<class T>
BaseStack<T>::BaseStack():capacity{2000000},_top{-1},_stack{new T[2000000]}{}
template<class T>
BaseStack<T>::~BaseStack()
{
    delete []_stack;
}
template<class T>
bool BaseStack<T>::empty()
{
    if(_top==-1)return true;
    else return false;
} 
template<class T>
int BaseStack<T>::size()
{
    return _top+1;
}
template<class T>
T& BaseStack<T>::top()
{
    return _stack[_top];
}
template<class T>
void BaseStack<T>::push(const T& item)
{
    _top+=1;
    _stack[_top]=T(item);
}
template<class T>
void BaseStack<T>::pop()
{
    _stack[_top]=-1;
    _top-=1;
}

// TODO: Implement five types of cards
// card type of "INSERT"
void insert(int L){return;}

// card type of "BOTTOM_ROW"
// The function name of "first_row" is actually misleading.
// Actually, you need to implement card type of "BOTTOM_ROW" in this function.
// Also, we purposely design the function to have return type of string,
// although we do not have a variable to receive the return value in partial judge code.
// You can think of the reason for having such design.
string first_row(int L, bool print){return "";}

// card type of "QUERY"
void query(int L){return;}

// card type of "FLUSH"
void flush(){return;}

// card type of "RESET"
void reset(int L){return;}
// The codes bellow prevent you from importing C++ containers.
// Nothing needed to be implemented below.
// Do not modify the codes below.
#endif
#ifndef vector
#define vector
#endif
#ifndef list
#define list
#endif
#ifndef forward_list
#define forward_list
#endif
#ifndef deque
#define deque
#endif
#ifndef array
#define array
#endif
#ifndef set
#define set
#endif
#ifndef multiset
#define multiset
#endif
#ifndef map
#define map
#endif
#ifndef multimap
#define multimap
#endif
#ifndef unordered_set
#define unordered_set
#endif
#ifndef unordered_multiset
#define unordered_multiset
#endif
#ifndef unordered_map
#define unordered_map
#endif
#ifndef unordered_multimap
#define unordered_multimap
#endif
#ifndef bitset
#define bitset
#endif
#ifndef valarray
#define valarray
#endif
#ifndef stack
#define stack
#endif
#ifndef queue
#define queue
#endif
#ifndef priority_queue
#define priority_queue
#endif
