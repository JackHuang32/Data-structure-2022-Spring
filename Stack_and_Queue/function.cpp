#include"function.h"
#include<iostream>
using namespace std;


template<class T>
BaseQueue<T>::BaseQueue():capacity{2000000},_queue{new T[2000000]},_front{-1},_rear{-1}{cout<<"constructor"<<endl;}

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
}

    // Delete one element from front
template<class T>
void BaseQueue<T>:: pop()
{
    _queue[front]=-1;
    _front+=1;
}
void tmpqq()
{
    BaseQueue<int>tmp;
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
    _top-=1;
    _stack[_top]=-1;
}
void tmpStack()
{
    BaseStack<int> tmp;
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