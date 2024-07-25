#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define pb push_back
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf 2000000001
#define mod 1000000007 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
vector<int>g[maxn];
int ways[maxn];
bool vis[maxn];
 
int dfs(int x){
    if(vis[x])return ways[x];
	vis[x] = 1;
    for(auto v:g[x]){
        ways[x]=(ways[x]+dfs(v))%mod;
    }
    return ways[x];
}
 
 
int main(){_
    int n,m;cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b;cin>>a>>b;
        g[b].pb(a);
    }  
	ways[1] = vis[1] = 1;
    cout<<dfs(n)<<endl;
}
