#include<bits/stdc++.h>
using namespace std;
const int maxSize = 1e5+1;
bool visited[maxSize];
#define ll long long
 
const ll INF = 1e18;
const ll NINF = -INF;
int main()
{
    int n,m,q;
    cin>>n>>m;
    vector<tuple<int,int,int>>v;
    int f,s,c,i;
    for(i=1;i<=m;i++)
    {
        cin>>f>>s>>c;
        v.push_back({f,s,-c});
    }
    ll distance[n+1];
    for(i=2;i<=n;i++)
    {
        distance[i] = INF;
    }
    distance[1]=0;
    for(i=1;i<=n-1;i++)
    {
        for(auto it:v)
        {
            int a,b,w;
            tie(a,b,w) = it;
            if(distance[a] == INF) continue;
            if(distance[b]>distance[a]+w)
            {
                distance[b] = distance[a]+w;
            }
            if(distance[b]<NINF)
            {
                distance[b] = NINF;
            }
        }
    }
    for(i=1;i<=n-1;i++)
    {
        for(auto it:v)
        {
            int a,b,w;
            tie(a,b,w) = it;
            if(distance[a] == INF) continue;
            // this means still a node is unvisited but may contain negative cycle connecting to the end point
            // which should not be considered while considering the answer from first node
            if(distance[a] == NINF)
            {
                distance[b] = NINF;
                continue;
            }  
            if(distance[b]>distance[a]+w)
            {
                distance[b] = NINF;
                continue;
            }

        }
    }
    if(distance[n] == NINF)
    {
        cout<<-1<<endl;
        return 0;
    }
    cout<<-distance[n];

    
}