
#include<iostream>
#include<algorithm>
#include"function.h"
using namespace std;
class group
{
private:
    long long int number_of_people;
    long long int arrive;
    long long int leave;
    string shop_name;
public:
    group():number_of_people{0},arrive{0},leave{0},shop_name{""}{}
    group(long long int n,long long int a,long long int l,string name):number_of_people{n},arrive{a},leave{l},shop_name{name}{}
    long long int get_number(){return number_of_people;}
    long long int get_arrive(){return arrive;}
    long long int get_leave(){return leave;}
    string get_name(){return shop_name;}
};
typedef pair<long long int,long long int>time_number;

void prune(string* arr,int& size)
{
    int len = 0;
    for(int i=1;i<size;i++)
    {
        if(arr[i-1]!=arr[i])
        {
            arr[++len]=arr[i];
        }       
    }
    size=len+1;
}

template<typename T>
void my_merge_sort(T* arr_begin,T* arr_end,T* buffer_begin,T* buffer_end)
{
    int size = (int)(arr_end-arr_begin);
    T* arr_mid = arr_begin+size/2;
    T* buffer_mid = buffer_begin+size/2;
    if(size>1)
    {
        my_merge_sort(arr_begin,arr_mid,buffer_begin,buffer_mid);
        my_merge_sort(arr_mid,arr_end,buffer_mid,buffer_end);
        merge(arr_begin,arr_mid,arr_mid,arr_end,buffer_begin);
        copy(buffer_begin,buffer_end,arr_begin);
    }
    return;
}
template<typename T>
void merge_sort(T* arr,int size)
{
    T buffer[size];
    my_merge_sort(arr,arr+size,buffer,buffer+size);
}

void solve()
{
    int n,arr_size,name_size,max_size;
    
    cin>>n;
    arr_size=n;
    name_size=n;
    max_size = 2*n;
    group group_array[n];
    string store_name[n];
    long long int arrive_time[n];
    time_number max_traffic[2*n];
    for(int t=0;t<n;t++)
    {
        long long int p,a,l; 
        string name;
        cin>>p>>a>>l>>name;
        group_array[t] = group(p,a,l,name);
        store_name[t]=name;
        arrive_time[t]=a;
        max_traffic[2*t]=make_pair(a,p);
        max_traffic[2*t+1]=make_pair(l,-p);
    }
    merge_sort(store_name,name_size);
    merge_sort(arrive_time,arr_size);
    merge_sort(max_traffic,max_size);
    prune(store_name,name_size);
    for(int i=1;i<max_size;i++)
    {
        max_traffic[i].second += max_traffic[i-1].second;
    }
     
    long long int max_number = max_traffic[max_size-1].second;
    long long int max_time = max_traffic[max_size-1].first;
    for(int i = max_size-1;i > 0;i--)
    {   
        if(max_traffic[i-1].first != max_traffic[i].first)
        {
            if(max_number < max_traffic[i-1].second)
            {
                max_time = max_traffic[i-1].first;
                max_number = max_traffic[i-1].second;
            }
        }
    }
    
    int m;
    cin>>m;
    while(m--)
    {
        string command;
        cin>>command;
        if(command == "TIME_ARRIVE")
        {
            int K;
            cin>>K;
            cout<<arrive_time[K-1]<<endl;
        }
        else if(command == "TRAFFIC_AT")
        {
            int T;
            cin>>T;
            int ans=0;
            for(int i=0;i<n;i++)
            {
                if(group_array[i].get_arrive() <= T && T < group_array[i].get_leave())
                {
                    ans += group_array[i].get_number();
                }
            }
            cout<<ans<<endl;
        }
        else if(command == "MAX_TRAFFIC")
        {
            cout<<max_time<<" "<<max_number<<endl;

        }
        else if(command == "STORE_LIST")
        {
            for(int i=0;i<name_size;i++)
            {
                if(i!=name_size-1)cout<<store_name[i]<<" ";
                else
                {
                    cout<<store_name[i]<<endl;
                }
            }
        }
    }
}

