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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n, m, q; cin >> n >> m >> q;
    int inv2 = (mod+1)/2;
    auto query = [&] (int i, int j, int x, int y) {
        if ((i + j) % 2) j++;
        if (i > x or j > y) return 0LL;
        int termos = (y-j)/2+1;
        int primeiro = (i-1)*m + j;
        int ultimo = ((i+y) % 2 ? (i-1)*m+(y-1) : (i-1)*m+y);
        int sum = (primeiro+ultimo) % mod * termos % mod * inv2 % mod;
        sum %= mod;
        int termos2 = (x-i)/2+1;
        int ans = sum * termos2 % mod; 
        ans = (ans + termos * 2*m % mod * (((termos2-1) * termos2 / 2)%mod)) % mod;
        return ans;
    };
    while (q--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        int ans = (query(a, c, b, d) + query(a+1, c, b, d)) % mod;
        cout << ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
