#include<iostream>
#include<vector>
#include<math.h>
#include<queue>
#include<map>
#include<stack>
#include<cctype>
using namespace std;
typedef pair<double,vector<int>> dis_pi;
class node{
private:    
    int id;
    string name;
    int ps;
    bool open;
public:
    node():id{-1},name{""},ps{-1},open{true}{}
    node(int _id,string _name,int _ps):id{_id},name{_name},ps{_ps},open{true}{}
    int get_id()
    {
        return id;
    }
    string get_name()
    {
        return name;
    }
    int get_ps()
    {
        return ps;
    }
    bool is_open()
    {
        return open;
    }
    void set_open()
    {
        open = true;
        //cout<<"set open "<<get_name()<<" !"<<endl;
    }
    void set_close()
    {
        open = false;
        //cout<<"set open "<<get_name()<<" !"<<endl;
    }
};
vector<node>place(100);
map<string,node>check_info;


bool relax_by_time(vector<vector<double>>&graph,vector<double>&distance,vector<int>&pi,int u,int v)
{
    if(u==v)return false;
    //cout<<"relax "<<u<<" "<<v<<endl;
    if(distance[v] >= distance[u]+graph[u][v])
    {
        if(distance[v]==distance[u]+graph[u][v])
        {
            if(place[u].get_ps() > place[pi[v]].get_ps())
            {
                //cout<<"successfully relax "<<u<<" "<<v<<endl;
                distance[v] = distance[u]+graph[u][v];
                pi[v] = u;
                return true;
            }
            else if(place[u].get_ps() == place[pi[v]].get_ps() && place[u].get_id() > place[pi[v]].get_id())
            {
                //cout<<"successfully relax "<<u<<" "<<v<<endl;
                distance[v] = distance[u]+graph[u][v];
                pi[v] = u;
                return true;
            }
        }
        else if(distance[v] > distance[u]+graph[u][v])
        {
            //cout<<"successfully relax "<<u<<" "<<v<<endl;
            distance[v] = distance[u]+graph[u][v];
            pi[v] = u;
            return true;
        }
    }
    return false;
}
double metric(double tmp)
{
    return abs(log(tmp));
}
bool relax_by_flow(vector<vector<double>>&graph,vector<double>&distance,vector<int>&pi,int u,int v)
{
    /*
    if(u==v)return false;
    //cout<<"relax "<<u<<" "<<v<<endl;
    if(distance[v] <= distance[u]+metric(graph[u][v]))
    {
        if(distance[v]==distance[u]+metric(graph[u][v]))
        {
            if(place[u].get_ps() > place[pi[v]].get_ps())
            {
                //cout<<"successfully relax "<<u<<" "<<v<<endl;
                distance[v] = distance[u]+metric(graph[u][v]);
                pi[v] = u;
                return true;
            }
            else if(place[u].get_ps() == place[pi[v]].get_ps() && place[u].get_id() > place[pi[v]].get_id())
            {
                //cout<<"successfully relax "<<u<<" "<<v<<endl;
                distance[v] = distance[u]+metric(graph[u][v]);
                pi[v] = u;
                return true;
            }
        }
        else if(distance[v] < distance[u]+metric(graph[u][v]))
        {
            //cout<<"successfully relax "<<u<<" "<<v<<endl;
            distance[v] = distance[u]+metric(graph[u][v]);
            pi[v] = u;
            return true;
        }
    }
    */
   if(u==v)return false;
    //cout<<"relax "<<u<<" "<<v<<endl;
    if(distance[v] <= distance[u]*graph[u][v])
    {
        if(distance[v]==distance[u]*graph[u][v])
        {
            if(place[u].get_ps() > place[pi[v]].get_ps())
            {
                //cout<<"successfully relax "<<u<<" "<<v<<endl;
                distance[v] = distance[u]*graph[u][v];
                pi[v] = u;
                return true;
            }
            else if(place[u].get_ps() == place[pi[v]].get_ps() && place[u].get_id() > place[pi[v]].get_id())
            {
                //cout<<"successfully relax "<<u<<" "<<v<<endl;
                distance[v] = distance[u]*graph[u][v];
                pi[v] = u;
                return true;
            }
        }
        else if(distance[v] < distance[u]*graph[u][v])
        {
            //cout<<"successfully relax "<<u<<" "<<v<<endl;
            distance[v] = distance[u]*graph[u][v];
            pi[v] = u;
            return true;
        }
    }
    
    return false;
}
typedef pair<double,int> dis_id;
void out_put_path(vector<int>&pi,int origin_idx,int des,string type,string metric)
{
    //cout<<"This is the optimal path:"<<endl;
    if(origin_idx == des )
    {
        cout<<type<<" "<<metric<<" : ";
        cout<<place[des].get_name()<<endl;
        return;
    }
    if(pi[des] == -1)
    {
        if(type == "Optimal")cout<<"No such optimal path to "<<place[des].get_name()<<endl;
        else
        {
            cout<<"No such limited path to "<<place[des].get_name()<<endl;
        }
        return;
    }
    else
    {
        stack<string>tmp;
        tmp.push(place[des].get_name());
        while(pi[des] != origin_idx)
        {
            //cout<<"backtracking "<<pi[des]<<endl;
            tmp.push(place[pi[des]].get_name());
            des = pi[des];
        }
        //cout<<"finish backtracking"<<endl;
        tmp.push(place[origin_idx].get_name());
        cout<<type<<" "<<metric<<" : ";
        while(!tmp.empty())
        {
            if(tmp.size()>1)cout<<tmp.top()<<" -> ";
            else
            {
                cout<<tmp.top()<<endl;
            }
            tmp.pop();
        }
    }
}
void Dijk(vector<vector<double>>&graph,int origin_idx,int N,int des,string metric,int limit,string type)//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
{
    vector<double>distance;
    vector<int>pi(N,-1);
    if(metric == "TIME")
    {
        vector<double>tmp(N,(double)INFINITY);
        distance = tmp;
        distance[origin_idx] = 0;
    }
    else
    {
        vector<double>tmp(N,0);
        //vector<double>tmp(N,(double)INFINITY);
        distance = tmp;
        distance[origin_idx] = 1;
        //distance[origin_idx] = (double)INFINITY;
    }
    priority_queue<dis_id,vector<dis_id>,greater<dis_id>>pq;
    pq.push(make_pair(0,origin_idx));
  	vector<int>relax_time(N,limit);
    while((!pq.empty()))
    {
        int cur_idx = pq.top().second;
        pq.pop();
        for(int i=0;i<N;i++)
        {
            if(place[i].is_open())
            {
                if(metric == "TIME")
                {
                    if(relax_time[i]&&relax_by_time(graph,distance,pi,cur_idx,i))
                    {
                        int relax_len = distance[i];
                      	relax_time[i]--;
                        pq.push(make_pair(relax_len,i));
                    }
                }
                else
                {
                    if(relax_time[i]&&relax_by_flow(graph,distance,pi,cur_idx,i))
                    {
                        int relax_len = distance[i];
                      	relax_time[i]--;
                        pq.push(make_pair(relax_len,i));
                    }
                }
                
            }
        }
    }
    /*
    for(auto d:distance)cout<<d<<" ";
    cout<<endl;
    for(auto p:pi)cout<<p<<" ";
    cout<<endl;
    */
    out_put_path(pi,origin_idx,des,type,metric);
}
typedef pair<double,int> dis_id;
void out_put_path_limit(vector<int>&pi,int origin_idx,int des,string type,string metric)
{
    //cout<<"This is the optimal path:"<<endl;
    if(origin_idx == des )
    {
        cout<<type<<" "<<metric<<" : ";
        cout<<place[des].get_name()<<endl;
        return;
    }
    if(pi.empty())
    {
        if(type == "Optimal")cout<<"No such optimal path to "<<place[des].get_name()<<endl;
        else
        {
            cout<<"No such limited path to "<<place[des].get_name()<<endl;
        }
        return;
    }
    else
    {
        cout<<type<<" "<<metric<<" : ";
        for(auto idx:pi)
        {
            //cout<<idx<<endl;
            
            cout<<place[idx].get_name()<<" -> "; 
        }
        cout<<place[des].get_name()<<endl;
        //cout<<"here"<<endl;
    }
}
void Dijk_limit(vector<vector<double>>&graph,int origin_idx,int N,int des,string metric,int limit,string type)//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
{
    //vector<double>distance;
    //vector<int>pi(N,-1);
    vector<vector<dis_pi>>dp(N,vector<dis_pi>(N));//dp[node][s].first = shortest distance for s steps from source to node
                                //dp[node][s].second = shortest path for s steps from source to node
    
    if(metric == "TIME")
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                dp[i][j].first = (double)INFINITY;
            }
        }
        dp[origin_idx][1].first = 0;
        for(int i=0;i<N;i++)
        {
            if(place[i].is_open())
            {
                dp[i][1].first = graph[origin_idx][i];
                dp[i][1].second.push_back(origin_idx);
            }
            
        }
    }
    else
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                dp[i][j].first = 0;
            }
        }
        for(int i=0;i<N;i++)
        {
            if(place[i].is_open())
            {
                dp[i][1].first = graph[origin_idx][i];
                dp[i][1].second.push_back(origin_idx);
            }

        }
        dp[origin_idx][1].first = 1;
    }
    if(metric == "TIME")
    {
        for(int cur_step = 2;cur_step < limit;cur_step++)
        {
            for(int i=0;i<N;i++)
            {
                if(i==origin_idx || !place[i].is_open())continue;
                double min = dp[i][cur_step-1].first;
                int tmp_idx = -1;
                for(int j=0;j<N;j++)
                {
                    if(!place[j].is_open())continue;
                    if(j!=i &&  min >= dp[j][cur_step-1].first+graph[j][i])
                    {
                        if(min == dp[j][cur_step-1].first+graph[j][i])
                        {
                            if(place[j].get_ps()>place[dp[i][cur_step-1].second.back()].get_ps())
                            {
                                min = dp[i][cur_step].first = dp[j][cur_step-1].first+graph[j][i];
                                tmp_idx = j;
                            }
                            else if(place[j].get_id() < place[dp[i][cur_step-1].second.back()].get_id())
                            {
                                min = dp[i][cur_step].first = dp[j][cur_step-1].first+graph[j][i];
                                tmp_idx = j;
                            }
                        }
                        else if(min > dp[j][cur_step-1].first+graph[j][i] )
                        {
                            min = dp[i][cur_step].first = dp[j][cur_step-1].first+graph[j][i];
                            tmp_idx = j;
                        }
                        
                    }
                    
                }
                if(tmp_idx!=-1) //found better path
                {
                    dp[i][cur_step].second = dp[tmp_idx][cur_step-1].second;
                    dp[i][cur_step].second.push_back(tmp_idx);
                    
                }
                else //did not find better path
                {
                    dp[i][cur_step].first = dp[i][cur_step-1].first;
                    dp[i][cur_step].second = dp[i][cur_step-1].second;
                }
                /*
                for(int i=0;i<N;i++)
                {
                    for(int j=0;j<N;j++)
                    {
                        cout<<"dis: "<<dp[i][j].first<<" ";
                    }
                    cout<<endl;
                }
                cout<<"-------------------------"<<endl;
                */
            }
        }
    }
    else
    {
        for(int cur_step = 2;cur_step < limit;cur_step++)
        {
            for(int i=0;i<N;i++)
            {
                if(i==origin_idx||!place[i].is_open())continue;
                double max = dp[i][cur_step-1].first;
                int tmp_idx = -1;
                for(int j=0;j<N;j++)
                {
                    if(!place[j].is_open())continue;
                    if(j!=i && max <=  dp[j][cur_step-1].first*graph[j][i])
                    {
                        if(max == dp[j][cur_step-1].first*graph[j][i])
                        {
                            if(place[j].get_ps()>place[dp[i][cur_step-1].second.back()].get_ps())
                            {
                                max = dp[i][cur_step].first = dp[j][cur_step-1].first*graph[j][i];
                                tmp_idx = j;
                            }
                            else if(place[j].get_id() < place[dp[i][cur_step-1].second.back()].get_id())
                            {
                                max = dp[i][cur_step].first = dp[j][cur_step-1].first*graph[j][i];
                                tmp_idx = j;
                            }
                        }
                        else if(max < dp[j][cur_step-1].first*graph[j][i])
                        {
                            max = dp[i][cur_step].first = dp[j][cur_step-1].first*graph[j][i];
                            tmp_idx = j;
                        }
                        
                    }
                    
                }
                if(tmp_idx!=-1)
                {
                    dp[i][cur_step].second = dp[tmp_idx][cur_step-1].second;
                    dp[i][cur_step].second.push_back(tmp_idx);
                }
                else
                {
                    dp[i][cur_step].first = dp[i][cur_step-1].first;
                    dp[i][cur_step].second = dp[i][cur_step-1].second;
                }
                /*
                for(int i=0;i<N;i++)
                {
                    for(int j=0;j<N;j++)
                    {
                        cout<<"dis: "<<dp[i][j].first<<" ";
                    }
                    cout<<endl;
                }
                cout<<"-------------------------"<<endl;
                */
            }
        }
    }
    

    //cout<<dp[des][limit-1].second.size()<<endl;
    out_put_path_limit(dp[des][limit-1].second,origin_idx,des,type,metric);
}
int main()
{
    int N;
    cin>>N;
    vector<vector<double>>time_graph(N);
    vector<vector<double>>flow_graph(N);
    for(int i=0;i<N;i++)
    {
        int id,ps;
        string name;
        cin>>id>>name>>ps;
        node tmp = node(id,name,ps);
        place[id] = node(id,name,ps);
        check_info[name] = node(id,name,ps);
    }   
    //cout<<"here"<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            double tmp;
            cin>>tmp;
            time_graph[i].push_back(tmp);
        }
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            double tmp;
            cin>>tmp;
            flow_graph[i].push_back(tmp);
        }
    }
    int origin_idx;
    while(1)
    {
        string command;
        cin>>command;
        if(command == "SET_ORIGIN")
        {
            string origin_name;
            cin>>origin_name;
            int idx = check_info[origin_name].get_id();
            if(place[idx].is_open())
            {
                origin_idx = idx;
                cout<<origin_name<<" is the new origin"<<endl;
            }
            else
            {
                cout<<"Fail to reset the origin"<<endl;
            }
        }
        else if(command == "MARK_STATE")
        {
            string open_or_close,name;
            cin>>open_or_close;
            vector<string>tmp;
            while(cin.peek()!='\n')
            {
                string name;
                cin>>name;
                tmp.push_back(name);
            }
            for(auto name:tmp)
            {
                int idx = check_info[name].get_id();
                if(open_or_close == "OPEN")
                {
                    if(place[idx].is_open())
                    {
                        cout<<"Fail to open "<<name<<endl;
                    }  
                    place[idx].set_open();
                }
                else if(open_or_close == "CLOSE")
                {
                    if(idx == origin_idx)
                    {
                        cout<<"Fail to close "<<name<<endl;
                        continue;
                    }
                    else if(!place[idx].is_open())
                    {
                        cout<<"Fail to close "<<name<<endl;
                    }
                    place[idx].set_close();
                }
            }
            
        }
        else if(command == "OPTIMAL_PATH")
        {
            string destination,type;
            cin>>destination>>type;
            //cout<<"processing optimal path from "<<place[origin_idx].get_name()<<" to "<<destination<<"...."<<endl;
            if(!check_info[destination].is_open())
            {
                cout<<"No such optimal path to "<<destination<<endl;
            }
            else if(type == "TIME")
            {
                Dijk(time_graph,origin_idx,N,check_info[destination].get_id(),"TIME",N,"Optimal");
            }
            else if(type == "FLOW")
            {
                Dijk(flow_graph,origin_idx,N,check_info[destination].get_id(),"FLOW",N,"Optimal");
            }
        }
        else if(command == "LIMITED_PATH")
        {
            string destination,type;
            int steps;
            cin>>destination>>type>>steps;
            if(steps >= N)
            {
                steps = N;
            }
            if(!check_info[destination].is_open() || steps <= 0)
            {
                cout<<"No such limited path to "<<destination<<endl;
            }
            
            else if(type == "TIME")
            {
                Dijk_limit(time_graph,origin_idx,N,check_info[destination].get_id(),"TIME",(steps),"Limited");
            }
            else if(type == "FLOW")
            {
                Dijk_limit(flow_graph,origin_idx,N,check_info[destination].get_id(),"FLOW",(steps),"Limited");
            }
        }
        else if(command == "END_OF_INSTRUCTION")
        {
            cout<<"Stop receiving instructions"<<endl;
            break;
        }
    }
    return 0;
}