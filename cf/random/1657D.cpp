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

ll dp[10*maxn], cost[10*maxn];
bool mark[10*maxn];
int main(){_
    int n,c;cin>>n>>c;

    for(int i=1;i<=n;++i){
        ll x,y,z;cin>>x>>y>>z;
        cost[i] = x;
        ckmax(dp[cost[i]],y*z);
    }    
    
    for(int i=1;i<=n;++i){
        if(mark[cost[i]])continue;
        mark[cost[i]] = 1;
        for(ll j=2;j*cost[i]<=c;++j)ckmax(dp[cost[i]*j],dp[cost[i]]*j);
    }
    
    for(int i=1;i<=c;++i)ckmax(dp[i],dp[i-1]);

    int m;cin>>m;

    auto possible = [&](int x,ll target){
        return dp[x]>target;
    };

    for(int i=1;i<=m;++i){
        ll a,b;cin>>a>>b;
        ll target = a*b;
        int l = 1, r = c, ans = -1;
        while(l<=r){
            int md = l + (r-l+1)/2;
            if(possible(md,target))ans = md, r = md-1;
            else l = md + 1;
        }
        cout<<ans<<" ";
    }
    cout<<endl;
}