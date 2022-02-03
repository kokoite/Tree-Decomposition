#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+100;
pair<ll,ll>tree[4*N];
ll n;
ll a[N];

void build(int k,int x,int y)
{
    if(x>y)
    {
        return;
    }
    if(x == y)
    {
        tree[k].first = a[x];
        return;
    }
    int left = 2*k;
    int right = left+1;
    int d = (x+y)>>1;
    build(left,x,d);
    build(right,d+1,y);
    tree[k].first = tree[left].first + tree[right].first;
    return;
}
void rangeUpdate(int a,int b,int k,int x,int y,ll value)
{
    if(tree[k].second !=0)
    {
        ll numOfElement = y-x+1;
        tree[k].first += (numOfElement)*tree[k].second;
        if(x!=y)
        {
            tree[2*k].second +=tree[k].second;
            tree[2*k +1].second+=tree[k].second;
        }
        tree[k].second =0;
    }
    if(b<x || a>y || x>y)
    {
        return;
    }
    if(a<=x && b>=y)
    {
        ll numOfElement = y-x+1;
        tree[k].first += value*(numOfElement);
        if(x!=y)
        {
            tree[2*k].second+=value;
            tree[2*k +1].second+=value;
        }
        return;
        // tree[]
    }
    int d = (x+y)/2;
    rangeUpdate(a,b,2*k,x,d,value);
    rangeUpdate(a,b,2*k +1,d+1,y,value);
    tree[k].first = tree[2*k].first + tree[2*k +1].first;
    return;
}

ll getRangeSum(int a,int b,int k,int x,int y)
{
    if(tree[k].second !=0)
    {
        ll numOfElement = y-x+1;
        tree[k].first +=(numOfElement)*(tree[k].second);
        if(x!=y)
        {
            tree[2*k].second += tree[k].second;
            tree[2*k +1].second += tree[k].second;
        }
        tree[k].second =0;
    }
    if(b<x || a>y || x>y)
    {
        return 0;
    }
    if(a<=x && b>=y)
    {
        
        return tree[k].first;
    }
    int d = (x+y)/2;

    return getRangeSum(a,b,2*k,x,d) + getRangeSum(a,b,2*k +1,d+1,y);
}

int main()
{
    int q;
    cin>>n>>q;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }

    build(1,0,n-1);
    while(q--)
    {
        int type;
        cin>>type;
        if(type == 1)
        {
            ll a,b,val;
            cin>>a>>b>>val;
            --a,b--;
            rangeUpdate(a,b,1,0,n-1,val);
        }
        else
        {
            int first;
            cin>>first;
            --first;
            cout<<getRangeSum(first,first,1,0,n-1)<<endl;
        }
    }
    // cout<<"gppd"<<endl;


}