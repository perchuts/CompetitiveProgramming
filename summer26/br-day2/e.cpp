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
    vector<vector<int>> bichos(m), bichos2(n);
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        bichos2[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> bichos2[i][j];
            --bichos2[i][j];
            bichos[bichos2[i][j]].pb(i);
        }
    }
    vector<int> hsh(n), val(m);
    map<ii, int> tem;
    for (int i = 0; i < m; ++i) val[i] = rnd(0, 1e18);
    for (int i = 0; i < n; ++i) {
        for (auto x : bichos2[i]) {
            hsh[i] ^= val[x], tem[{i, x}] = 1;
        }
    }
    vector<int> par(n);
    for (int i = 0; i < n; ++i) par[i] = i;
    auto findp = [&] (auto&& self, int u) -> int {
        return par[u] = (par[u] == u ? u : self(self, par[u]));
    };
    auto unite = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (v == u) return false;
        par[u] = v;
        return true;
    };
    vector<int> need(n, -1);
    for (int i = 0; i < m; ++i) {
        sort(all(bichos[i]), [&] (int x, int y) { return sz(bichos2[x]) < sz(bichos2[y]); });
        for (int j = 1; j < sz(bichos[i]); ++j) {
            int a = bichos[i][j-1], b = bichos[i][j];
            if (sz(bichos2[a]) == sz(bichos2[b]) and hsh[a] != hsh[b]) {
                cout << "YES" << endl;
                cout << a + 1 << " " << b+1 << endl;
                exit(0);
            }
            if (sz(bichos2[a]) != sz(bichos2[b]) and (need[a] == -1 or sz(bichos2[b]) < sz(bichos2[need[a]]))) need[a] = b;
        }
    }
    vector<vector<int>> sexo(n);
    for (int i = 0; i < n; ++i) {
        int j = need[i];
        if (j == -1) continue;
        for (auto k : bichos2[i]) {
            if (!tem[{j, k}]) {
                cout << "YES" << endl;
                cout << i +1 << " " << j+1 << endl;
                exit(0);
            }
        }
    }
    cout << "NO" << endl;
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
