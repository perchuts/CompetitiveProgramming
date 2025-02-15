#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;
 
const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 2e5+100;
const int logn = 20;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int par[maxn][logn], lvl[maxn], cnt[maxn];
 
vector<int>g[maxn];
 
void dfs(int u,int p){
    par[u][0] = p, lvl[u] = lvl[p]+1;
    for(int i=1;i<logn;++i){
        if(par[u][i-1])par[u][i] = par[par[u][i-1]][i-1];
    }
    for(auto v:g[u]){
        if(v!=p)dfs(v,u);
    }
}
 
int lca(int u,int v){
    if(lvl[u]<lvl[v])swap(u,v);
    for(int i=logn-1;~i;--i){
        if(lvl[par[u][i]]>=lvl[v])u = par[u][i];
    }
    if(u==v)return u;
    for(int i=logn-1;~i;--i){
        if(par[u][i]!=par[v][i])u = par[u][i], v = par[v][i];
    }
    return par[v][0];
}
 
int dfs2(int u,int p){
    for(auto v:g[u]){
        if(v==p)continue;
        cnt[u] += dfs2(v,u);
    }
    return cnt[u];
}
 
int main(){_
    int n,m;cin>>n>>m;
    for(int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        g[u].pb(v), g[v].pb(u);
    }    
    dfs(1,0);
    while(m--){
        int u,v;cin>>u>>v;
        int _lca = lca(u,v);
        cnt[u]++, cnt[v]++, cnt[_lca]--, cnt[par[_lca][0]]--;
    }
    dfs2(1,1);
    for(int i=1;i<=n;++i)cout<<cnt[i]<<" \n"[i==n];
}


