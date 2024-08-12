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
 
ll m,n,k;
bool possible(ll x){
    ll less = 0;
    for(ll i=1;i<=n;++i){
        // i*j = x => j = x/i
        less += min(m,x/i);
    }
    return less>=k;
}
 
int main(){_
    cin>>n>>m>>k;
    ll l = 1ll, r = 1e12, ans;
    while(l<=r){
        ll md = l + (r-l+1ll)/2;
        if(possible(md))r = md-1ll, ans = md;
        else l = md+1ll;
    }
    cout<<ans<<endl;
}