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
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v);
    }
    vector<int> vis(n), color(n), freq(3);
    auto explore = [&] (auto&& self, int u) -> bool {
        vis[u] = 1;
        freq[color[u]]++;
        bool ok = true;
        for (auto v : g[u]) {
            if (vis[v]) {
                ok &= (color[v] == (1 + color[u]) % 3);
            } else { 
                color[v] = (1 + color[u]) % 3;
                ok &= self(self, v);
            }
        }
        return ok;
    };

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            freq[0] = freq[1] = freq[2] = 0;
            if (explore(explore, i)) ans += freq[0] * freq[1] + freq[1] * freq[2] + freq[2] * freq[0];
            else ans += (freq[0]+freq[1]+freq[2])*(freq[0]+freq[1]+freq[2]);
        }
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
