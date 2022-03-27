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

vector<int>g[1001];
int dp[1001],lvl[1001];
bool isbridge[1001];
int additional = 0;
int dfs(int u){
    int ans = 0;
    for(auto v:g[u]){
        if(!lvl[v]){
            lvl[v] = lvl[u] + 1;
            ans+=dfs(v);
            dp[u]+=dp[v];
        }else if(lvl[v]<lvl[u]){
            dp[u]++;
        }else dp[u]--;
    }
    dp[u]--;
    if(ans==0&&lvl[u]>1&&dp[u]==0){
        return 1;
    }
    return ans;
}


int main(){_
    int n,m;cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b;cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }   
    lvl[1] = 1;
    cout<<(dfs(1)+1)/2<<endl; 
}