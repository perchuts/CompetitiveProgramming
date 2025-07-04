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
    int n; cin >> n;
    auto fexp = [&] (int b, int e) { 
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            b = b * b % mod;
            e /= 2;
        }
        return ans;
    };
    vector<ii> ev;
    int ans = 0, prv = 0, prb = 1, foi = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            int x; cin >> x;
            ev.pb({x, i});
        }
    }
    vector<int> inv(7);
    for (int i = 1; i <= 6; ++i) inv[i] = fexp(i, mod-2);
    vector<int> freq(n, 0);
    sort(all(ev));
    for (int l = 0, r = 0; l != sz(ev); l = r) {
        ans = (ans + (ev[l].first - prv) * (1 - (foi == n ? prb : 0) + mod)) % mod;
        while (r != sz(ev) and ev[r].first == ev[l].first) {
            auto [v, i] = ev[r];
            if (freq[i] == 0) {
                foi++;
            } else {
                prb = prb * inv[freq[i]] % mod * 6 % mod;
            }
            freq[i]++;
            prb = prb * freq[i] % mod * inv[6] % mod;
            r++;
        }
        prv = ev[l].first;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
