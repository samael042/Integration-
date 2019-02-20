#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 1000000000 
 
ll dis[100005];
vector <pair<ll,pair<ll,ll>>>adj[100005]; //vector storing next vertex,time,cost
bool vis[100005];
ll parent[100005];
ll tame[100005];
ll K;
 
void dijkstra(ll source,ll destination)
{
    multiset <pair<ll,ll>>q;  //declaring queue of distance and vertex
    q.insert(make_pair(0,source));
    dis[source] = 0;
    parent[source] = source;
    
    while(!q.empty())
    {
        ll ver = (*q.begin()).second;
        
        q.erase(q.begin());
        
        if(vis[ver])
            continue;
        vis[ver] = true;
        
        for(ll i=0;i<adj[ver].size();++i)
        {
            ll e = adj[ver][i].first;
            ll wei = adj[ver][i].second.second;
            ll t = adj[ver][i].second.first;
            
            if(e == destination)
            {
                if((dis[ver] + wei + K*t) < dis[e])
                {
                    dis[e] = dis[ver] + wei + K*t;
                    tame[e] = tame[ver] + t;
                    q.insert(make_pair(dis[e],e));
                    parent[e] = ver;
                }
            }
            else
            {
                if((dis[ver] + wei + K*(t + 1)) < dis[e])
                {
                    dis[e] = dis[ver] + wei + K*(t + 1);
                    tame[e] = tame[ver] + t + 1;
                    q.insert(make_pair(dis[e],e));
                    parent[e] = ver;
                }
            }
        }
    }
}
 
int main()
{
    ll N,X; cin>>K>>N>>X;
    
    for(ll i=0;i<100005;++i)
    {
        dis[i] = MAX;
    }
    
    for(ll i=0;i<X;++i)
    {
        ll u,v,t,c; cin>>u>>v>>t>>c;
        adj[u].push_back(make_pair(v,make_pair(t,c)));
        adj[v].push_back(make_pair(u,make_pair(t,c)));
    }
    
    ll source,destination; cin>>source>>destination;
    
    dijkstra(source,destination);
    
    if((dis[destination] == MAX) || (X < 1) || (X > ((N*N - N)/2)) || (K < 1) || (K > 1000) || (source < 1) || (destination < 1) || (source > N) || (destination > N))
    {
        cout<<"Error"<<endl;
    }
    else
    {
        stack <ll>s;
        ll i = destination;
        while(parent[i] != i) //finding path
        {
            s.push(i);
            i = parent[i];
        }
        s.push(source);
        
        while(!s.empty()) //printing path
        {
            if(s.size() == 1)
            {
                cout<<(s.top())<<" ";
            }
            else
            {
                cout<<(s.top())<<"->";
            }
            s.pop();    
        }
        cout<<tame[destination]<<" "<<dis[destination]<<endl;
    }
}
