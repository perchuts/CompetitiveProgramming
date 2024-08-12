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
const int maxn = 5010;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int v[maxn], dp[maxn], qnt[maxn], pode[maxn];
 
void solve(){
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>v[i], qnt[i] = 0;
 
    int tmp = 0;pode[n+1] = 1;
 
    for(int i=n;i>=1;--i){
        ++qnt[v[i]], ckmax(tmp,qnt[v[i]]);
        pode[i] = tmp<=(n-i+1)/2&&((n-i)&1);
    }
 
    int ans = 0;
 
    for(int i=1;i<=n;++i){
 
        int big = 0;
 
        dp[i] = 0;
 
        for(int j=1;j<=n;++j)qnt[j] = 0;
 
        for(int j=i-1;j>=1;--j){    
            if(big<=(i-j-1)/2&&v[i]==v[j]&&((i-j)&1)){
                ckmax(dp[i],dp[j]!=0?dp[j]+1:0);
            }
            ++qnt[v[j]];
            ckmax(big,qnt[v[j]]);
        }
 
        if(big<=(i-1)/2&&(i&1))ckmax(dp[i],1);
 
        if(pode[i+1])ckmax(ans,dp[i]);
    }
 
    cout<<ans<<endl;
}
 
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}