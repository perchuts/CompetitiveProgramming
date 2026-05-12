#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

void solve1() {
    int n, s; cin >> n >> s;
    auto cor = [&] (int k) { return (s >> k & 1); };
    --s;
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        if (u < v) swap(u, v);
        if (u == n-1) {
            if (cor(v) == 1) cout << n << " " << v+1 << endl;
            else cout << v+1 << " " << n << endl;
            continue;
        }
        if (cor(u) == cor(v)) cout << u+1 << " " << v+1 << endl;
        else cout << v+1 << " " << u+1 << endl;
    }
}

void solve2() {
    int n; cin >> n;
    vector<ii> edg(n-1);
    vector<int> par(2*n); iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        par[v] = u;
    };
    for (auto& [u, v] : edg) {
        cin >> u >> v, --u, --v;
        if (u == n-1) {
            unite(v, 2*n-1);
            unite(v+n-1, 2*n-2);
        } else if (v == n-1) {
            unite(u, 2*n-2);
            unite(u+n-1, 2*n-1);
        } else {
            if (u > v) {
                unite(u, v);
                unite(u+n-1, v+n-1);
            } else {
                unite(u, v+n-1);
                unite(u+n-1, v);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n-1; ++i) {
        if (findp(findp, i) == findp(findp, 2*n-1)) ans += (1 << i);
    }
    cout << ans+1 << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1, q; cin >> t >> q;
    while(t--) {
        if (q == 1) solve1();
        else solve2();
    }
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
