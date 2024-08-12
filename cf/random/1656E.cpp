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

bool color[maxn];
vector<int>g[maxn];

void dfs(int u,int p){
    color[u] = color[p]^1;
    for(auto v:g[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}

void solve(){
    int n;cin>>n;
    for(int i=1;i<n;++i){
        int a,b;cin>>a>>b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(1,1);
    for(int i=1;i<=n;++i){
        cout<<(color[i]?sz(g[i]):-sz(g[i]))<<" ";
        g[i].clear();
    }
    cout<<endl;

}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}