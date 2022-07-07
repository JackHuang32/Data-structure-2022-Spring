#include"function.h"
#include<iostream>
using namespace std;
template<class T>
Node<T>::Node(T _x,T _y,T _fence):x{_x},y{_y},fence{_fence},next{nullptr}{}
template<class T>
T Node<T>::compare(T _x,T _y)
{
    if(y < _y)
    {
        return 1;
    }
    else if(y == _y)
    {
        if(_x > x)return 1;
        else if(_x < x)return 0;
        else
        {
            return 2;
        }
    }
    else    //y > _y
    {
        return 0;
    }
}
template<class T>
LinkedList<T>::LinkedList():length{0},first{nullptr}{}
template<class T>
void LinkedList<T>::insert(T _x,T _y,T _fence)
{
    if(_fence!=0 && _fence!=1)return;
    Node<T>* tmp = first;
    Node<T>* ins = new Node<T>(_x,_y,_fence);
    if(tmp==nullptr)        //if null head then change head to the insert node
    {
        first = ins;
        return;
    }
    if(tmp->compare(_x,_y)==0)      //if insert node should be ahead of head node
    {
        first = ins;
        first->next = tmp;
        return;    
    }
    if(tmp->compare(_x,_y)==2)      //if insert node in the same position as head node
    {
        if(tmp->fence==0)tmp->fence = _fence;
        return;
    }
    while(tmp!=nullptr)   //the case of insert position is between two nodes
    {
        if(tmp->compare(_x,_y)==1)
        {
            if(tmp->next==nullptr)break;
            if(tmp->next->compare(_x,_y)==0) //in between tmp and tmp->next
            {
                Node<T>*cur = ins;
                cur->next = tmp->next;
                tmp->next = cur;
                return;
            }
            tmp = tmp->next;
        }
        else if(tmp->compare(_x,_y)==2)
        {
            if(tmp->fence==0)
            {
                tmp->fence = _fence;
            }
            return;
        }
    }
    tmp->next = ins;
    return;
}
template<class T>
void LinkedList<T>::deletion(T _x,T _y)
{
    Node<T>*cur = first;
    Node<T>*pre = nullptr;
    if(cur==nullptr)            //no need for delete with null head 
    {
        return;
    }
    else if(cur->compare(_x,_y)==2) //delete head
    {
        if(cur->fence==1)              //return if the node has fence
        {
            return;      
        }
        first = first->next;
        delete cur;
        return;
    }
    while(cur!=nullptr)
    {
        if(cur->compare(_x,_y)==0)
        {
            return;
        }
        else if(cur->compare(_x,_y)==2)
        {
            if(cur->fence==1)
            {
                return;
            }
            pre->next = cur->next;
            delete cur;
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    return;
}
template<class T>
void LinkedList<T>::show()
{
    cout<<"Display"<<endl;
    Node<T>* cur = first;
    while(cur!=nullptr)
    {
        cout<<'('<<cur->x<<','<<cur->y<<')'<<endl;
        cur = cur->next;
    }
    return;
}
void tmp_Node()
{
    Node<long long>tmp(1,2,1);
    tmp.compare(1,2);
}
void tmp_link_list()
{
    LinkedList<long long>l;
    l.insert(1,1,1);
    l.deletion(1,1);
    l.show();
}
LinkedList<long long>List;
void plant(long long x,long long y,int withFence)
{
    List.insert(x,y,withFence);
    return;
}

void thief(long long x,long long y)
{
    List.deletion(x-1,y);
    List.deletion(x,y);
    List.deletion(x,y+1);
    List.deletion(x,y-1);
    List.deletion(x+1,y);
    return;
}

void superThief(long long x,long long y)
{
    List.deletion(x-1,y);
    List.deletion(x,y);
    List.deletion(x,y+1);
    List.deletion(x,y-1);
    List.deletion(x+1,y);
    List.deletion(x+1,y+1);
    List.deletion(x-1,y+1);
    List.deletion(x-1,y-1);
    List.deletion(x+1,y-1);
    return;
}

void display()
{
    List.show();
    return;
}