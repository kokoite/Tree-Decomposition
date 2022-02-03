#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const ll NINF = -INF;
const int mod = 1e9+7;
#define pb push_back
#define rep(i,a,b) for(i=a;i<b;i++)
#define vi vector<int>
#define f first
#define s second
#define all(a) a.begin(),a.end()
#define sortv(v)   sort(all(v))   
#define revv(v) reverse(all(v))   
#define nline cout<<"\n"

const int N = 2e5+100;

// if i ever forger this will help me to recall 

vector<int>tree[N];
int dp[N];
// dp array is for filling the  level table on which level node are
int jump[N][40];

// this will fill up the jump table indicating if jump[i][j] 
// denoting the jump from node i of length 2 power j

void dfs(int node,int par)
{
    for(auto nde:tree[node])
    {
        if(nde == par)
            continue;
        dp[nde]=dp[node]+1;
        dfs(nde,node);
    }
}

// o(n) time

// o log(n) time
int makeJump(int node,int n)
{

    // n is distance from node
    int i;
    int digit = log2(n)+1;

            for(i=0;i<digit;i++)
            {
                if(n & (1<<i))
                {
                    node = jump[node][i];
                }
                if(node == -1)
                {
                    break;
                }
            }
            return node;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    cin>>n>>q;
    int i;
    int parent[N];
    for(i=2;i<=n;i++)
    {
        int first;
        cin>>first;
        parent[i] = first;
        tree[first].push_back(i);
        tree[i].push_back(first);
    }
    for(i=0;i<=n;i++)
    {
        jump[1][i]=-1;

    }
    for(i=2;i<=n;i++)
    {
        jump[i][0] = parent[i];
    }

    // filling the jump table
    int j;
    for(i=1;i<25;i++)
    {
        for(j=2;j<=n;j++)
        {
            if(jump[j][i-1]<=1)
            {
                jump[j][i]=-1;
            }
            else
            {
                jump[j][i] = jump[jump[j][i-1]][i-1];
            }
        }
    }

    dfs(1,0);
    // dp[i] denote the level


    while(q--)
    {
        int first,second;
        cin>>first>>second;
        int lv1 = dp[first];
        int lv2 = dp[second];
        if(lv2 == 0 || lv1 == 0)
        {
            // cout<<"good"<<endl;
            cout<<1<<endl;
        }
        else if(first == second)
        {
            // cout<<"good"<<endl;
            cout<<first<<endl;
        }
        else
        {
            int reqJump = abs(lv1-lv2);
            int node = -1;
            int prev;
            if(lv1>lv2)
            {
                node = first;
                prev = second;
            }
            else
            {
                prev = first;
                node = second;
            }
            // cout<<node<<endl;
            node = makeJump(node,reqJump);
            if(node == prev)
            {
                cout<<node<<endl;

            }
            else
            {
                // minimum jump can be of length one
                // maximum will be of length of root node
                // doing binary search
                // predicate function
                // like FFFFFT
                // finding the first T value
                int hi = dp[node];
                int lo = 1;
                while(hi-lo>1)
                {
                    int mid = (hi + lo)/2;
                    if(makeJump(node,mid) == makeJump(prev,mid))
                    {
                        hi = mid;
                    }
                    else{
                        lo = mid+1;
                    }
                }
                if(makeJump(node,lo) == makeJump(prev,lo))
                {
                    cout<<makeJump(node,lo)<<endl;
                }
                else
                {
                    cout<<makeJump(node,hi)<<endl;
                }

            }


        }
    }
    // overall time complexity o(n) + o(q*(logn)*(log(n)))
    
}