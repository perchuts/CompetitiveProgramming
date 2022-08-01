#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;
 
const int inf = 2e9+1;
const ll mod = 1e9+7;
const int maxn = 6e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
ll factorial[maxn];
 
long long inv(long long a, long long b){
 return 1<a ? b - inv(b%a,a)*b/a : 1;
}
 
long long binomial_coefficient(int n, int k) {
    return (((factorial[n] * inv(factorial[k],mod))%mod) * inv(factorial[n-k],mod)) % mod;
}
 
int32_t main(){_
    int n;cin>>n;
    vector<int>v(n+1);
    for(auto& x:v)cin>>x;
    factorial[0] = 1;
    for (ll i = 1; i < maxn; i++) {
        factorial[i] = (factorial[i - 1] * i) % mod;
    }
    ll ans = 0;
    for(int i=0;i<=n;++i){
        if(v[i]==0)break;
        ans = (ans+binomial_coefficient(v[i]+i,i+1))%mod;
    }
    cout<<ans<<endl;
}