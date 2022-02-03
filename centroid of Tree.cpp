#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+100;
vector<int>tree[N];
int dp[N];
int n;
void dfs(int node,int par)
{
    dp[node]=1;
    for(auto nde:tree[node])
    {
        if(nde == par)
            continue;
        dfs(nde,node);
        dp[node]+=dp[nde];
    }
    // number  of node from all branch from node is less than n/2 than go
}
void solve(int node,int par,int parAns)
{
    int maxNode=-1,maxSize=-1;
    for(auto nde:tree[node])
    {
        if(nde == par)
        {
            continue;
        }
        if(dp[nde]>maxSize)
        {
            maxSize = dp[nde];
            maxNode = nde;
        }
    }
    if(maxSize>n/2)
    {
        solve(maxNode,node,dp[node]-dp[maxNode]+1);
    }
    else
    {
        cout<<node;
        return;
    }
    

}
int main()
{
    // int n;
    cin>>n;
    int i;
    for(i=0;i<n-1;i++)
    {
        int first,second;
        cin>>first>>second;
        tree[first].push_back(second);
        tree[second].push_back(first);
    }
    dfs(1,0);
    solve(1,0,0);
    // no of child node in subtree

}