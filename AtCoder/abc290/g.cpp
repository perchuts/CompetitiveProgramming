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
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int d, k, x; cin >> d >> k >> x;
    auto fexp = [&] (__int128_t b, int e) {
        __int128_t ans = 1;
        while (e) {
            if (e&1) ans = ans * b;
            b = b * b, e /= 2;
        }
        return ans;
    };
    int ans = 1e18;
    for (int st = d; ~st; --st) {
        __int128_t sexo = (fexp(__int128_t(k), st+1)-1) / __int128_t(k-1);
        if (sexo < x) break;
        __int128_t T = sexo - __int128_t(x);
        int cur = (st != d);
        for (int i = st-1; ~i; --i) {
            sexo = sexo * __int128_t(k-1);
            sexo = (sexo+1)/__int128_t(k);
            sexo = (sexo-1) / __int128_t(k-1);
            __int128_t times = T / sexo;
            cur += int(times);
            T %= sexo;
        }
        ckmin(ans, cur);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
