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
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> h(n+1), qt(n+5), par(n+5), usando(n+1), morreu(n+1), falta(n+1);
    vector<set<ii>> bichos(n+5);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        h[u] = h[p] + 1;
        falta[u] = sz(g[u])-1;
        bichos[h[u]].insert({-falta[u], u});
        qt[h[u]]++;
        for (auto v : g[u]) {
            if (v == p) continue;
            par[v] = u;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, n);
    int mxh = *max_element(all(h)), mxq = *max_element(all(qt));
    int ok = 1;
    for (int i = 0; i < n; ++i) {
        if (qt[h[i]+1] == mxq) {
            ok &= (sz(g[i])-(i!=0) != qt[h[i]+1]);
        }
    }
    morreu[par[0]] = 1;
    int ans = mxq + 1 - ok;
    cout << ans << endl;
    int tot = 0;
    set<int> alts;
    for (int i = 1; i <= mxh; ++i) alts.insert(-i);
    for (int j = 0; j < ans; ++j) {
        vector<int> rem, cur;
        for (auto z : alts) {
            z *= -1;
            auto poe = [&] (int a) {
                usando[par[a]] = 1;
                if (!morreu[par[a]]) {
                    bichos[z-1].erase({-falta[par[a]], par[a]});
                    falta[par[a]]--;
                    bichos[z-1].insert({-falta[par[a]], par[a]});
                }
                cur.pb(a);
            };
            if (sz(bichos[z]) == 1) {
                auto [qt, a] = *begin(bichos[z]);
                if (usando[a]) continue;
                bichos[z].erase({qt, a});
                poe(a);
                rem.pb(z);
            } else {
                auto [qt1, a] = *begin(bichos[z]); bichos[z].erase(begin(bichos[z]));
                auto [qt2, b] = *begin(bichos[z]); bichos[z].erase(begin(bichos[z]));
                if (!usando[a]) {
                    poe(a);
                    bichos[z].insert({qt2, b});
                } else {
                    poe(b);
                    bichos[z].insert({qt1, a});
                }
            }
        }
        for (auto x : rem) alts.erase(-x);
        tot += sz(cur);
        cout << sz(cur) << " ";
        assert(!cur.empty());
        for (auto x : cur) {
            usando[par[x]] = 0;
            morreu[x] = true;
            cout << x + 1 << " ";
        }
        cout << endl;
    }
    assert(tot == n);
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
