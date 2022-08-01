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
const int maxn = 3003;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<int>g[maxn];

struct Tab{
    int w;ll delta;
    Tab(int w,ll delta): w(w), delta(delta){}
    Tab(): w(-1), delta(0){}
    bool operator <(const Tab& x) const{
        return w<x.w||w==x.w&&delta<x.delta;
    }
    Tab operator+(const Tab& x) const{
        return Tab(w+x.w,delta+x.delta);
    }
    Tab operator-() const{
        return Tab(w+(delta>0),0);
    }
};

vector<vector<Tab>>dp;

vector<Tab> merge(vector<Tab>a, vector<Tab>b){
    vector<Tab> res(sz(a)+sz(b));
    for(int i=0;i<sz(a);++i){
        for(int j=0;j<sz(b);++j){
            res[i+j] = max(res[i+j], a[i] + b[j]);
            res[i+j+1] = max(res[i+j+1], a[i] + -b[j]);
        }
    }
    return res;
}

void dfs(int u,int p){
    for(auto v:g[u]){
        if(v==p)continue;
        dfs(v,u);
        dp[u] = merge(dp[u],dp[v]);
    }
}

void solve(){
    int n, m;cin>>n>>m;

    dp = vector<vector<Tab>>(n+1, vector<Tab>(1, Tab(0,0)));//no inicio, n venco ngm

    for(int i=1;i<=n;++i){
        ll x;cin>>x;
        dp[i][0].delta -= x;
    }

    for(int i=1;i<=n;++i){
        ll x;cin>>x;
        dp[i][0].delta += x;
    }

    for(int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        g[u].pb(v), g[v].pb(u);
    }

    dfs(1,1);

    for(int i=1;i<=n;++i)g[i].clear();

    cout << (-dp[1][m-1]).w << endl;

}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}