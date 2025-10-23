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


int32_t main() {_
#ifndef gato
    int n, m; 
    while (true) {
        cin >> n >> m;
        if (n == 0) break;
        vector<set<int>> g(n);
        vector<int> tipo(n);
        vector<ii> edg(m);
        for (auto& [u, v] : edg) {
            cin >> u >> v;
            --u, --v;
            g[u].insert(v), g[v].insert(u);
        }
        vector<int> ord(n); iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return sz(g[x]) > sz(g[y]); });
        for (auto i : ord) {
            bool ok = true;
            for (auto j : ord) {
                if (j == i) break;
                if (g[j].find(i) == g[j].end()) { ok = false; break; }
            }
            if (!ok) break;
            tipo[i] = 1;
        }
        bool ok = 1;
        for (auto [u, v] : edg) {
            ok &= ((tipo[u] + tipo[v]) > 0);
        }
        cout << (ok ? "Y" : "N") << endl;
    }
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
