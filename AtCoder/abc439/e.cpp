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

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n), cara;
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i], cara.pb(a[i]);
    sort(all(cara)), cara.erase(unique(all(cara)), end(cara));
    vector<ii> ord;
    for (int i = 0; i < n; ++i) ord.pb({lower_bound(all(cara), a[i]) - begin(cara), i});
    sort(all(ord), [&] (ii x, ii y) { return b[x.second] < b[y.second]; });
    vector<int> bit(n+1);
    auto add = [&] (int x, int y) {
        while (x <= n) ckmax(bit[x], y), x += x & (-x);
    };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) {
            ckmax(ans, bit[x]);
            x -= x & (-x);
        }
        return ans;
    };
    int ans = 0;
    for (int l = 0, r = 0; l != n; l = r) {
        vector<ii> bicho;
        while (r < n and b[ord[r].second] == b[ord[l].second]) bicho.pb(ord[r++]);
        vector<ii> adc;
        for (auto [pos, fodase] : bicho) {
            int val = query(pos) + 1;
            adc.pb({pos+1, val});
            ckmax(ans, val);
        }
        for (auto [x, y] : adc) add(x, y);
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
