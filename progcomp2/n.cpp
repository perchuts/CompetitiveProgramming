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
    if (n == 2) {
        cout << 0 << endl;
        exit(0);
    }
    vector<ii> edg(n-1);
    for (auto& [u, v] : edg) cin >> u >> v, --u, --v;
    vector<int> par(n), lvl(n);
    iota(all(par), 0);
    auto findp = [&] (auto& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return false;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) lvl[u]++;
        return true;
    };
    vector<ii> lixo;
    for (auto [u, v] : edg) {
        if (!merge(u, v)) lixo.pb({u, v});
    }
    vector<int> rr;
    for (int i = 0; i < n; ++i) if (findp(findp, i) == i) rr.pb(i);
    cout << sz(lixo) << endl;
    for (int i = 0; i < sz(lixo); ++i) {
        cout << 1+lixo[i].first << ' ' << 1+lixo[i].second << ' ' << 1+rr[i] << ' ' << 1+rr[i+1] << endl;
    }
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
