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
    int n, m; cin >> n >> m;
    vector<ii> segs(m);
    vector<int> xo(n+2);
    vector<int> val(m);
    for (auto& x : val) x = rnd(0, 1e18);
    for (auto& [l, r] : segs) cin >> l >> r;
    for (int i = 0; i < m; ++i) {
        auto [l, r] = segs[i];
        xo[l] ^= val[i], xo[r+1] ^= val[i];
    }
    map<int, vector<int>> caras;
    for (int i = 1; i <= n; ++i) {
        xo[i] ^= xo[i-1];
        caras[xo[i]].pb(i);
    }
    vector<iii> ranges;
    vector<iii> sts(n+1);
    vector<ii> elim(n+1);
    for (auto [fds, v] : caras) {
        int t = sz(v)/2;
        if (sz(v) == 1) continue;
        elim[v[0]] = {v[1], v[sz(v)-t]};
        for (int r = t-1; r < sz(v); ++r) {
            int z = (r == sz(v)-1 ? n+1 : v[r+1]);
            sts[v[r-t+1]] = {z, v[r], (r == t-1)};
        }
    }
    vector<ii> ans;
    vector<iii> alive;
    for (int i = 1; i <= n; ++i) {
        auto [lim, rx, is_beg] = sts[i];
        if (lim) {
            if (!alive.empty()) {
                auto [l, r, lim2] = alive.back();
                if (rx < lim2 and lim < lim2) {
                    alive.pop_back();
                    alive.pb({l, rx, lim});
                    sts[elim[i].first] = {0, 0, 0};
                } else if (!is_beg) {
                    alive.pb({i, rx, lim});
                }
            } else if (!is_beg) {
                alive.pb({i, rx, lim});
            }
        }
        while (!alive.empty()) {
            auto [x, y, z] = alive.back();
            if (i < z-1) break;
            ans.pb({x, y});
            alive.pop_back();
        }
    }

    cout << sz(ans) << endl;
    for (auto [l, r] : ans) cout << l << " " << r << endl;
    cout << endl;

}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
