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

const int inf = 1e9+1;
const int mod = 1e9+7;
const int maxn = 1e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<int>g[maxn], g2[maxn];
int subt[maxn], lvl[maxn], root, lvl2[maxn], lvl3[maxn], lift[maxn][20];
ii best[maxn];//stores closest red node in i's subtree and its distance to i
bool vis[maxn];

int dfs(int u,int p){
    subt[u] = 1, lvl[u] = lvl[p]+1;
    for(auto v:g[u]){
        if(v==p||vis[v])continue;
        subt[u] += dfs(v,u);
    }
    return subt[u];
}

int find_centroid(int u,int p,int n){
    for(auto v:g[u]){
        if(v==p||vis[v]||subt[v]<=n/2)continue;
        return find_centroid(v,u,n);
    }
    return u;
}

void build(int x = 1,int p = -1){
    lvl[x] = 0;
    int centroid = find_centroid(x,x,dfs(x,x));
    vis[centroid] = 1;
    if(p!=-1){
        g2[p].pb(centroid);g2[centroid].pb(p);
    }else root = centroid;
    for(auto v:g[centroid]){
        if(!vis[v])build(v,centroid);
    }
}

void dfs2(int u,int p){
    lvl2[u] = lvl2[p]+1;
    for(auto v:g2[u]){
        if(v==p)continue;
        dfs2(v,u);
    }
}
int calcdist(int u,int v){
    if(lvl3[u]<lvl3[v])swap(u,v);
    int ans = 0;
    for(int i=19;~i;--i)if(lvl3[lift[u][i]]>=lvl3[v])u=lift[u][i], ans += (1<<i);
    if(u==v)return ans;
    for(int i=19;~i;--i)if(lift[u][i]!=lift[v][i])u=lift[u][i],v=lift[v][i],ans+=(1<<(i+1));
    return ans+2;
}

void update(int u){
    best[u] = {0,u};
    int dist=0,source = u;
    while(u!=root){
        u=g2[u][0], dist=calcdist(source,u);
        if(ckmin(best[u].first,dist))best[u].second = source;
    }
}

int lca(int u,int v){
    if(lvl2[u]<lvl2[v])swap(u,v);
    while(lvl2[u]!=lvl2[v])u = g2[u][0];
    while(u!=v)u = g2[u][0], v = g2[v][0];
    return u;
}


int query(int u){
    int resp = best[u].first, dist = 0, source = u;
    while(u!=root){
        u = g2[u][0];
        int closest = best[u].second, dist2 = best[u].first;
        if(best[u].first==inf)continue;
        ckmin(resp,calcdist(closest,source));
    }
    return resp;
}

void processa(int u=1,int p=0){
    lvl3[u] = lvl3[p]+1, lift[u][0]=p;
    for(int i=1;i<20;++i)if(lift[u][i-1])lift[u][i]=lift[lift[u][i-1]][i-1];
    for(auto v:g[u])if(v!=p)processa(v,u);
}

int main(){_
    int n,m;cin>>n>>m;
    
    for(int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        g[u].pb(v);
        
        g[v].pb(u);
    }    
    processa();
    for(int i=1;i<=n;++i)best[i].first = inf;

    build();
    dfs2(root,root);
    update(1);
    for(int i=1;i<=m;++i){
        int t,v;cin>>t>>v;
        if(t==1){
            update(v);
        }else{
            cout<<query(v)<<endl;
        }
    }
}