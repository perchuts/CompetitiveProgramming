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
 
int deg[maxn], dist[maxn];
vector<int>g[maxn];
int main(){_    
    int n,m;cin>>n>>m;
    for(int i=1;i<=m;++i){
        int u,v;cin>>u>>v;
        g[v].pb(u);
        ++deg[u];
    }    
    for(int i=1;i<n;++i)dist[i] = inf;
    priority_queue<ii,vector<ii>,greater<ii>>pq;
    pq.push({0,n});
    while(!pq.empty()){
        auto [d,u] = pq.top();pq.pop();
        if(d>dist[u])continue;
        for(auto v:g[u]){
            if(ckmin(dist[v],d+deg[v])){
                pq.push({dist[v],v});
            }
            --deg[v];
        }
    }
    cout<<dist[1]<<endl;
}