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
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y <= x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x <= y) ? (x=y,1):0; }
 
 
ll v[8005], pref[8005],dp[8005][2];
ll calc(ll i,ll j){
    if(i>j)return 1e18;
    return (pref[j] - pref[i-1])*(j-i+1ll);
}
 
void compute(int g,int l,int r,int dx,int dy){
    if(l>r)return;
    int md = (l+r)/2,dmd=dx;
    dp[md][g&1]=1e18;
    for(int i=dx;i<=min(dy,md-1);++i)if(ckmin(dp[md][g&1],dp[i][!(g&1)]+calc(i+1,md)))dmd=i;
    compute(g,l,md-1,dx,dmd);
    compute(g,md+1,r,dmd,dy);
}
 
ll solve(ll n, ll g, vector<ll>v){
 
    for(int i=1;i<=n;++i)pref[i] = pref[i-1]+v[i];
    for(int i=0;i<=n;++i)dp[i][0] = dp[i][1] = 1e18;
 
    dp[0][1] = dp[0][0] = 0;
 
    for(int i=1;i<=g;++i)compute(i,1,n,0,n-1);
    
    return dp[n][g&1];
}
 
int main(){_
    ll n,g;cin>>n>>g;vector<ll>v(n+1);
    for(int i=1;i<=n;++i)cin>>v[i];
    cout<<solve(n,g,v)<<endl;
}