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
const int maxn = 1e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<tuple<int,int,int>>planos;

vector<int>seg[8*maxn];

int vis[8*maxn],where[2*maxn], n, m;

void build(int i,int l,int r){
    if(l==r){
        where[l] = i;
        return;
    }
    int md = (l+r)/2;
    seg[i].pb(2*i);seg[i].pb(2*i+1);
    build(2*i,l,md);build(2*i+1,md+1,r);
}

void update(int i,int l,int r,int x,int y,int u){
    if(l>y||r<x)return;
    if(x<=l&&r<=y){
        seg[u].pb(i);
        return;
    }
    int md = (l+r)/2;
    update(2*i,l,md,x,y,u);update(2*i+1,md+1,r,x,y,u);
}

bool dfs(int u){
    vis[u] = 1;
    for(auto v:seg[u]){
        if(vis[v]==1)return 1;
        if(vis[v]==0&&dfs(v))return 1;
    }
    vis[u] = 2;
    return 0;
}

bool hasCycle(int x){
    for(int i=1;i<=n;++i)seg[where[i]].clear();
    for(int i=1;i<=4*n;++i)vis[i] = 0;
    for(int i=0;i<=x;++i){
        auto [u,l,r] = planos[i];
        u = where[u];
        update(1,1,n,l,r,u);
    }
    for(int i=1;i<=n;++i){
        if(!vis[i]&&dfs(i))return 1;
    }
    return 0;
}

int main(){_
    cin>>n>>m;
    planos.resize(m);
    for(auto& [a,b,c]:planos)cin>>a>>b>>c;    
    build(1,1,n);
    int l = 1, r = m, ans = -1;
    while(l<=r){
        int md = l + (r-l+1)/2;
        if(hasCycle(md-1))ans = md, r = md - 1;
        else l = md + 1;
    }
    cout<<ans<<endl;
}