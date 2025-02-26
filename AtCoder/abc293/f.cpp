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

int limit[64];

void solve(){
    int ans = 0;
    int n; cin >> n;
    for (int i = 2; i <= 1000; ++i) {
        int cur = n;
        bool ok = 1;
        while (cur) {
            ok &= (cur % i <= 1);
            cur /= i;
        }
        ans += ok;
    }
    auto eval = [&] (int m, int b) {
        int pot = 1, tot = m&1;
        for (int i = 1; (1 << i) <= m; ++i) {
            pot *= b;
            if (m >> i & 1) tot += pot;
        }
        return tot;
    };
    for (int i = 1; i < (1 << 6) and limit[i] > 1000; ++i) {
        int l = 1001, r = limit[i], choice = r;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (eval(i, md) <= n) choice = md, l = md+1;
            else r = md-1;
        }
        if (eval(i, choice) == n) ans++;
    }
    cout << ans << endl;
}

int32_t main(){_
    int lg = 0;
    for (int i = 1; i < 64; ++i) {
        if (__builtin_popcount(i) > 1) limit[i] = limit[i-1];
        else {
            int l = 1, r = 1e18;
            while (l <= r) {
                int md = l + (r-l+1)/2, pot = 1;
                for (int k = 0; k < lg; ++k) {
                    if (pot > (1e18/md)) { pot = 2e18 + 69; break; }
                    pot *= md;
                }
                if (pot <= 1e18) limit[i] = md, l = md+1;
                else r = md-1;
            }
            lg++;
        }
    }
    int t = 1; cin >> t;
    while(t--) solve();
}
