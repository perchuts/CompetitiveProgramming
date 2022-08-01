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
const int maxn = 4e5;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
vector<ll>b;
ll times[2*maxn];
int main(){_
    ll n, k;cin>>n>>k;
    b.resize(n+1);
    for(int i=1;i<=n;++i)cin>>b[i];
 
    ll resp = 0, cur = 0, qnt = 0;
 
    for(ll i=n;i>=k+1;--i){
        cur -= qnt, qnt -= times[i+k];
        if(b[i]>0)times[i] = max(0ll, (b[i] - cur + k - 1ll)/k);
        resp += times[i], cur += k*times[i], qnt += times[i];
    }
 
    ll additional = 0;
 
    for(ll i=k;i>=1;--i){
        cur -= qnt, qnt -= times[i+k];
        ckmax(additional, (b[i] - cur + i - 1ll)/i);
    }
 
    cout<<resp+additional<<endl;
}