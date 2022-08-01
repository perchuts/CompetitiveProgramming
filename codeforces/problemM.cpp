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
using li = pair<ll,int>;
const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
vector<li>g[maxn];
li dp[maxn][2];
void compute(int u,int p,ll lambda){
    li best(0,0), sum(0,0);
    for(auto [w,v]:g[u]){
        if(v==p)continue;
        compute(v,u,lambda);
        sum.first += dp[v][0].first, sum.second += dp[v][0].second;
        best = max(best,{dp[v][1].first-dp[v][0].first+w-lambda,dp[v][1].second-dp[v][0].second+1});
    }
    dp[u][1] = sum, dp[u][0].first = sum.first + best.first, dp[u][0].second = sum.second + best.second;
}
 
int main(){_
    ll n, k;cin>>n>>k;
    for(int i=1;i<n;++i){
        int u,v;ll c;cin>>u>>v>>c;
        g[u].pb({c,v}), g[v].pb({c,u});
    }
    ll l = -1e12, r = 1e12;
    compute(1,0,l);
    if(dp[1][0].second<k){
        cout<<"Impossible"<<endl;
        return 0;
    }
    while(l!=r){
        ll md = l + (r-l+1)/2;
        compute(1,0,md);
        if(dp[1][0].second>=k)l = md;
        else r=md-1; 
    }   
    compute(1,0,l);
    cout<<dp[1][0].first+k*l<<endl;
}