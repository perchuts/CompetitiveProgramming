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

const int _log = 20;
vector<int>g[maxn];
int lvl[maxn], par[maxn][_log];

void dfs(int u,int p){
    par[u][0] = p, lvl[u] = lvl[p]+1;
    for(int i=1;i<_log;++i){
        if(par[u][i-1]!=-1)par[u][i] = par[par[u][i-1]][i-1];
    }
    for(auto v:g[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}

int lca(int u,int v){
    if(lvl[u]<lvl[v])swap(u,v);
    for(int i=_log-1;~i;--i){
        if(par[u][i]!=-1&&lvl[par[u][i]]>=lvl[v])
            u = par[u][i];
    }
    if(u==v)return u;
    for(int i=_log-1;~i;--i){
        if(par[u][i]!=par[v][i])
            u = par[u][i], v = par[v][i];
    }
    return par[u][0];
}

int dp[maxn];
int ans;

int dfs2(int u,int p){
    int resp = dp[u];
    for(auto v:g[u]){
        if(v==p)continue;
        int sub = dfs2(v,u);
        resp+=sub;
    }
    ckmax(ans,resp);
    return resp;
}

int main(){_
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);    
    int n,k;cin>>n>>k;
    for(int i=1;i<n;i++){
        int a,b;cin>>a>>b;
        g[a].pb(b);g[b].pb(a);
    }
    dfs(1,1);
    for(int i=1;i<=k;i++){
        int a,b;cin>>a>>b;
        int _lca = lca(a,b);
        dp[a]++,dp[b]++,dp[par[_lca][0]]--,dp[_lca]--;
    }
    dfs2(1,1);
    cout<<ans<<endl;
}