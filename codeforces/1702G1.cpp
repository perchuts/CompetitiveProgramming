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
const int maxn = 3e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
vector<int>g[maxn];
 
int t, lvl[maxn], par[maxn][20];
 
pair<int,int>tempo[maxn];
 
int dfs(int u,int p){
    tempo[u].first = ++t, par[u][0] = p, lvl[u] = lvl[p]+1;
    for(int i=1;i<20;++i){
        if(par[u][i-1])par[u][i] = par[par[u][i-1]][i-1];
    }
    int mx = t;
    for(auto v:g[u]){
        if(v==p)continue;
        mx = dfs(v,u);
    }
    tempo[u].second = mx;
    return mx;
}
 
int lca(int u,int v){
    if(lvl[u]<lvl[v])swap(u,v);
    for(int i=19;~i;--i)if(lvl[par[u][i]]>=lvl[v])u = par[u][i];
    if(u==v)return u;
    for(int i=19;~i;--i)if(par[u][i]!=par[v][i])u = par[u][i], v = par[v][i];
    return par[u][0];
}
 
int main(){_
    int n;cin>>n;
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        g[u].pb(v), g[v].pb(u);
    }    
    dfs(1,0);
    vector<ii>exl;
    for(int i=1;i<=n;++i)exl.pb(tempo[i]);
    sort(all(exl));
    // for(int i=1;i<=n;++i)cout<<tempo[i].first<<" "<<tempo[i].second<<endl;
    int q;cin>>q;
    while(q--){
        int k;cin>>k;
        vector<pair<ii,int>>v(k);
        for(auto& [p,x]:v){
            cin>>x;p = tempo[x];
        }
        sort(all(v));
        bool flag = 0, ok = 1;
        for(int i=1;i<k;++i){
            if(v[i].first.first>v[i-1].first.second){
               if(flag==1){
                    ok = 0;break;
               } 
               flag = 1;        
                if(lvl[lca(v[i].second,v[i-1].second)]>lvl[v[0].second]){
                    ok = 0;break;
                }
            }
        }        
        cout<<(ok?"YES":"NO")<<endl;
    }
}