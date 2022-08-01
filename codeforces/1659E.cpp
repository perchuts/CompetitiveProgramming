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
struct DSU{
    int par[maxn], lvl[maxn];
    bool ok[maxn];
    DSU(){for(int i=1;i<maxn;++i)par[i]=i;}
    int findp(int u){return par[u] = (par[u]==u?u:findp(par[u]));}
    void merge(int u,int v){
        u = findp(u), v = findp(v);
        if(u==v)return;
        if(lvl[u]<lvl[v])swap(u,v);
        par[v] = u;
        if(lvl[u]==lvl[v])++lvl[u];
        ok[u]|=ok[v];
    }
    void nice(int u){ok[findp(u)]=1;}
}dsu[30];
 
 
int main(){_
    int n,m;cin>>n>>m;
    for(int i=1;i<=m;++i){
        int u,v,w;cin>>u>>v>>w;
        for(int k=0;k<30;++k)if((w>>k)&1)dsu[k].merge(u,v);
        if(!(w&1))for(int k=1;k<30;++k)dsu[k].nice(u), dsu[k].nice(v);
    }
    int q;cin>>q;
    while(q--){
        int u, v;cin>>u>>v;
        int ans = 2;
        for(int k=0;k<30;++k){
            if(dsu[k].findp(u)==dsu[k].findp(v))ans = 0;
        }
        if(ans==2){
            for(int k=1;k<30;++k)if(dsu[k].ok[dsu[k].findp(u)])ans = 1;
        }
        cout<<ans<<endl;
    }
}