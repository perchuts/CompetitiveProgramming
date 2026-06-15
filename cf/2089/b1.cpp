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
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    set<ii> alive;
    for (int i = 0; i < n; ++i) {
        int z = min(a[i], b[i]);
        a[i] -= z, b[i] -= z;
        if (a[i] != 0) alive.insert({i, 1});
        if (b[i] != 0) alive.insert({i, 0});
    }
    set<iii> dds;
    auto it = begin(alive);
    while (it != end(alive)) {
        it = next(it);
        if (it == end(alive)) break;
        if ((prev(it)->second) == 1 and (it->second == 0)) {
            dds.insert({-prev(it)->first+(it->first), prev(it)->first, prev(it)->second});
        }
    }
    if (sz(alive) >= 2) { 
        auto [i, t1] = *begin(alive);
        auto [j, t2] = *prev(end(alive));
        if (t2 == 1 and t1 == 0) {
            dds.insert({n-(j-i), j, t2});
        }
    }
    auto get_prox = [&] (int i) {
        auto z = alive.lower_bound({i+1, -1});
        if (z == end(alive)) return *begin(alive);
        return *z;
    };
    auto get_prev = [&] (int i) {
        auto z = alive.lower_bound({i, -1});
        if (z == begin(alive)) return *prev(end(alive));
        return *prev(z);
    };
    auto dist = [&] (int i, int j) {
        if (i < j) return j - i;
        return n - (i - j);
    };
    int ans = 0;
    while (!dds.empty()) {
        auto [dx, i, t] = *dds.begin();
        auto [j, t2] = get_prox(i);
        assert(t == 1 and t2 == 0);
        dds.erase(begin(dds));
        alive.erase({i, t});
        alive.erase({j, t2});
        int z = min(a[i], b[j]);
        a[i] -= z, b[j] -= z;
        if (a[i] != 0) {
            alive.insert({i, t});
            if (sz(alive) > 1) {
                auto [jj, tt2] = get_prox(i);
                if (tt2 == 0) dds.insert({dist(i, jj), i, t});
            }
        } else if (b[j] != 0) {
            alive.insert({j, t2});
            if (sz(alive) > 1) {
                auto [i2, tt] = get_prev(i);
                if (tt == 1) dds.insert({dist(i2, j), i2, tt});
            }
        } else {
            if (sz(alive) > 1) {
                auto [jj, tt2] = get_prox(i);
                auto [i2, tt] = get_prev(i);
                if (tt == 1 and tt2 == 0) dds.insert({dist(i2, jj), i2, tt});
            }
        }
        ckmax(ans, dx);
    }
    cout << ans+1 << endl;
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
