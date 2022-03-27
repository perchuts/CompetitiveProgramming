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

int lvl[maxn], par[maxn], lvl2[maxn], par2[maxn], in[maxn], low[maxn];
bool vis[maxn];

int findp(int x){
    if(par[x]==x)return x;
    else return par[x] = findp(par[x]);
}

void merge(int x,int y){
    int a = x, b = y;
    x = findp(x), y = findp(y);
    if(lvl[x]<lvl[y])swap(x,y);
    par[y] = x;
    lvl[x] += lvl[y];
}

int findp2(int x){
    if(par2[x]==x)return x;
    else return par2[x] = findp2(par2[x]);
}
void merge2(int x,int y){
    int a = x, b = y;
    x = findp2(x), y = findp2(y);
    if(lvl2[x]<lvl2[y]){
        swap(x,y);
    }
    par2[y] = x;
    lvl2[x] += lvl2[y];
}
vector<int>g[maxn];
int cur;
void dfs(int u,int p){
    vis[u] = 1, low[u] = in[u] = ++cur;
    bool flag = 1;
    for(auto v:g[u]){
        if(v==p&&flag){
            flag = 0;continue;
        }else if(vis[v]){
            ckmin(low[u],in[v]);
        }else{
            dfs(v,u);
            ckmin(low[u],low[v]);
            if(low[v]>in[u])cout<<v<<" "<<u<<endl;
        }
    }
}

int main(){_
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i)lvl[i] = lvl2[i] = 0, par[i] = par2[i] = i;
    for(int i=0;i<m;++i){
        int a,b;cin>>a>>b;
        if(findp(a)!=findp(b)){
            g[a].pb(b);g[b].pb(a);           
        }else if(findp2(a)!=findp2(b)){
            g[a].pb(b);g[b].pb(a);           
        }
        }
    for(int i=1;i<=n;++i)
        if(!vis[i])dfs(i,i);
}