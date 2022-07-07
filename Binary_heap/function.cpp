#include "function.h"
#include<math.h>
using namespace std;

Node::Node(std::string id, u32 time){
    this->id = id;
    this->time = time;
}

u32 Node::get_time(){
    return time;
};
void Node::set_time(u32 time){
    this->time = time;
};

std::string Node::get_id(){
    return id;
};

// Operator Overloading
bool operator== (Node& node1, Node& node2){
    return node1.get_time() == node2.get_time();
}

bool operator== (Node& node1, u32 time){
    return node1.get_time() == time;
}

bool operator!= (Node& node1, Node& node2){
    return node1.get_time() != node2.get_time();
}

bool operator!= (Node& node1, u32 time){
    return node1.get_time() != time;
}

bool operator< (Node& node1, Node& node2){
    if(node1.get_time() == node2.get_time()){
        return node1.get_id() < node2.get_id();
    }
    return node1.get_time() < node2.get_time();
}

bool operator< (Node& node1, u32 time){
    return node1.get_time() < time;
}

bool operator> (Node& node1, Node& node2){
    if(node1.get_time() == node2.get_time()){
        return node1.get_id() > node2.get_id();
    }
    return node1.get_time() > node2.get_time();
}

bool operator> (Node& node1, u32 time){
    return node1.get_time() > time;
}

bool operator<= (Node& node1, Node& node2){
    return node1.get_time() <= node2.get_time();
}

bool operator<= (Node& node1, u32 time){
    return node1.get_time() <= time;
}

bool operator>= (Node& node1, Node& node2){
    return node1.get_time() >= node2.get_time();
}

bool operator>= (Node& node1, u32 time){
    return node1.get_time() >= time;
}

void operator+= (Node& node1,u32 time){
    node1.set_time(node1.get_time() + time);
}

ostream& operator<<(ostream& os, Node& n) {
    os << n.id << " AT " << n.time;
    return os;
}

template <class T>
unsigned int BinaryHeap<T>::parent_idx(unsigned int idx){
    return idx/2;
}

template <class T>
unsigned int BinaryHeap<T>::left_idx(unsigned int idx){
    return idx*2;
}

template <class T>
unsigned int BinaryHeap<T>::right_idx(unsigned int idx){
    return idx*2+1;
}

template <class T>
void BinaryHeap<T>::heapify_up(int idx){
    int cur = idx;
    Node tmp = heap[idx];
    while(cur > 1 && tmp < heap[parent_idx(cur)])  //while the current end time is larger than parent
    {
        if(tmp > heap[parent_idx(cur)])//if current node has larger name than the parent do
        {
            break;
        }
        heap[cur] = heap[parent_idx(cur)];//pull down
        cur = parent_idx(cur);
    }
    heap[cur] = tmp;
}

template <class T>
void BinaryHeap<T>::heapify_down(int idx){
    int child = left_idx(idx);
    Node tmp = heap[idx];
    int len = size();
    if(child > len)return; //no child node for the root (single head node)
    else if(right_idx(idx) <= len && heap[left_idx(idx)] > heap[right_idx(idx)])    //if left >= right and there is a right child 
    {
        child = right_idx(idx);
    }
    while(1)
    {
        //cout<<"head value: "<<tmp.get_time()<<" "<<"child value: "<<heap[child].get_time()<<endl;
        if(tmp < heap[child])
        {
            break;
        }
        heap[parent_idx(child)] = heap[child];//pull up the smaller child
        child = left_idx(child);
        if(child > len)//no left child
        {
            break;
        }
        if(child+1 <= len) //if there is a right child
        {
            if(heap[child] > heap[child+1])
            {
                ++child;
            }
        } 
        
    }
    heap[parent_idx(child)] = tmp;
}

template <class T>
u32 BinaryHeap<T>::size(){
    return heap.size()-1;
}

template <class T>
void BinaryHeap<T>::insert(T element){
    heap.push_back(element);
    heapify_up(size());
}

template <class T>
T BinaryHeap<T>::get_min(){
    return heap[1];
}

template <class T>
void BinaryHeap<T>::del_min(){
    heapify_down(1);
}

template <class T>
Manager<T>::Manager(){
    Node dummy = Node("dum",0);
    taQue.heap.push_back(dummy);
    endTime = (u32)INFINITY;
    //cout<<"this is the original endtime:"<<endTime<<endl;
}

template <class T>
int Manager<T>::finish_in_time(u32 costTime,u32 deadLine){
    if(deadLine < endTime)
    {
        return taQue.get_min().get_time() + costTime <= deadLine;
    }
    else
    {
        return taQue.get_min().get_time() + costTime <= endTime;
    }
}

template <class T>
void Manager<T>::cmd_set_endTime(u32 endTime){
    int len = taQue.size();
    for(int i=1;i<=len;i++)
    {
        if(taQue.heap[i].get_time() > endTime)
        {
            cout<<"SET_ENDTIME FAIL"<<endl;
            return;
        }
    }
    this->endTime = endTime;
    cout<< "SET_ENDTIME SUCCESS" <<endl;

}

template <class T>
void Manager<T>::cmd_add_task(string taskName,u32 costTime){
    if(taQue.size()==0)
    {
        cout<<"ADD_TASK "<<taskName<<": FAIL"<<endl;
        return;
    }
    Node TA = taQue.get_min();
    if(TA.get_time()+costTime > endTime)
    {
        cout<<"ADD_TASK "<<taskName<<": FAIL"<<endl;
        return;
    }
    TA += costTime;
    taQue.heap[1] += costTime;
    cout<<"ADD_TASK "<<taskName<<": "<<TA.get_id()<<" AT "<<TA.get_time()<<endl;
    taQue.heapify_down(1);
    /*
    cout<<"current schedule->";
    for(auto i:taQue.heap)
    {
        cout<<i.get_id()<<" "<<i.get_time()<<" ";
    }
    cout<<endl;
    */
}

template <class T>
void Manager<T>::cmd_add_ta(std::string id, u32 begin){
    if(endTime > begin)
    {
        Node TA = Node(id,begin);
        taQue.insert(TA);
        cout<<"ADD_TA SUCCESS"<<endl;
    }
    else
    {
        cout<<"ADD_TA FAIL"<<endl;
    }
    /*
    cout<<"current schedule->";
    for(auto i:taQue.heap)
    {
        cout<<i.get_id()<<" "<<i.get_time()<<" ";
    }
    cout<<endl;
    */
}

template <class T>
void Manager<T>::cmd_check_schedule(u32 costTime,u32 deadLine){
    
    if(taQue.size()==0) // if there is no TA or no TA is available
    {
        cout<<"CHECK_SCHEDULE: NO TA WARNING!"<<endl;
    }
    else if(!finish_in_time(costTime,deadLine))
    {
        cout<<"CHECK_SCHEDULE: OVERTIME WARNING!"<<endl;
    }
    else
    {
        cout<<"CHECK_SCHEDULE: CAN FINISH!"<<endl;
    }
}

template <class T>
void Manager<T>::result(){
    
    if(taQue.size()>0)
    {
        Node TA = taQue.get_min();
        cout<<"NUMBER_TA: "<<taQue.size()<<endl;
        cout<<"EARLIEST FINISH TA: "<<TA.get_id()<<" AT "<<TA.get_time()<<endl;
    }
    else
    {
        cout<<"NUMBER_TA: 0" <<endl;
    }
    
}

template Manager<Node>::Manager();
template void Manager<Node>::cmd_set_endTime(u32 endTime);
template void Manager<Node>::cmd_check_schedule(u32 costTime,u32 deadLine);
template void Manager<Node>::cmd_add_task(string taskName,u32 costTime);
template void Manager<Node>::cmd_add_ta(std::string id, u32 begin);
template void Manager<Node>::result();