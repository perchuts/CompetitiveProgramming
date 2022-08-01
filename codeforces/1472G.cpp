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
 
int d[maxn], answer[maxn];
 
void solve(){
    int n,m;cin>>n>>m;
    for(int i=1;i<=m;++i){
        int u,v;cin>>u>>v;
        g[u].pb(v);
    }
 
    queue<int>q;
 
    q.push(1);
 
    while(!q.empty()){
        int u = q.front();q.pop();
        for(auto v:g[u]){
            if(v!=1&&d[v]==0){
                d[v] =d[u]+1;
                q.push(v);
            }
        }
    }
 
    vector<int>sorted(n);
 
    iota(all(sorted),1);
 
    sort(all(sorted),[&](int a,int b){
        return d[a]>d[b];
    });
 
    for(auto u:sorted){
        int best = d[u];
        for(auto v:g[u]){
            if(d[v]>d[u])ckmin(best,answer[v]);
            else ckmin(best,d[v]);
        }
        answer[u] = best;
    }
 
    for(int i=1;i<=n;++i){
        g[i].clear();
        cout<<answer[i]<<" \n"[i==n];
        answer[i] = d[i] = 0;
    }
}
 
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}