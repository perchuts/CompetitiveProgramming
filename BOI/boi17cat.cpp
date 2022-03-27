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

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<int>g[maxn];
vector<ii>order;
int lift[maxn][20], sub[maxn], lvl[maxn], par[maxn], best[maxn];
bool vis[maxn];

void getOrder(int u,int p,int lvl){
    order.pb({lvl,u});
    for(auto v:g[u]){
        if(v!=p)getOrder(v,u,lvl+1);
    }
}

int dfs(int u,int p,int lvl){
    if(lvl!=-1)lift[u][lvl] = lift[p][lvl]+1;
    sub[u] = 1;
    for(auto v:g[u]){
        if(v==p||vis[v])continue;
        sub[u] += dfs(v,u,lvl);
    }
    return sub[u];
}

int find_centroid(int u,int p,int n){
    for(auto v:g[u]){
        if(!vis[v]&&sub[v]>n/2&&v!=p)return find_centroid(v,u,n);
    }
    return u;
}

void build(int u=1,int p=-1){
    int centroid = find_centroid(u,p,dfs(u,u,p==-1?p:lvl[p]));
    vis[centroid] = 1, par[centroid] = p;
    if(p!=-1)lvl[centroid] = lvl[p]+1;
    for(auto v:g[centroid]){
        if(!vis[v])build(v,centroid);
    }
}   

int lca(int u,int v){
    if(lvl[u]<lvl[v])swap(u,v);
    while(lvl[u]!=lvl[v])u=par[u];
    while(u!=v)u=par[u],v=par[v];
    return u;
}

int dist(int u,int v){
    int level = lvl[lca(u,v)];
    return lift[u][level] + lift[v][level];
}

void update(int u){
    int source = u;
    while(u!=-1){
        if(best[u]==0||dist(source,u)<dist(best[u],u))best[u] = source;
        u = par[u];
    }
}

int query(int u){
    int source = u, answer = inf;
    while(u!=-1){
        if(best[u]!=0)ckmin(answer,dist(source,best[u]));
        u = par[u];
    }
    return answer;
}

int main(){_
    int n,d;cin>>n>>d;
    for(int i=2;i<=n;++i){
        int x;cin>>x;++x;
        g[x].pb(i);
        g[i].pb(x);
    }
    getOrder(1,1,0);
    sort(all(order));reverse(all(order));//order of node insertion
    build();
    int ans = 0;
    for(int i=0;i<n;++i){
        int cur = order[i].second;  
        if(query(cur)>=d){
            update(cur), ++ans;
            // cout<<cur<<" ";
        }
    }
    cout<<ans<<endl;
}