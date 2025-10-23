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
    vector sets(21, vector(21, vector<int>()));
    vector classes(21, vector(21, vector<vector<int>>()));
    vector<int> pc(1<<20), vis(1<<20);
    for (int i = 0; i < (1 << 20); ++i) pc[i] = __builtin_popcount(i);
    auto shift = [] (int i, int j) {
        if (2 * j < (1 << i)) return 2 * j;
        return 2 * j + 1 - (1 << i);
    };
    for (int i = 1; i <= 20; ++i) {
        for (int j = 0; j < (1 << i); ++j) {
            sets[i][pc[j]].pb(j);
            if (vis[j] == false) {
                vector<int> sexo;
                int cur = j;
                while (!vis[cur]) {
                    sexo.pb(cur);
                    vis[cur] = 1;
                    cur = shift(i, cur);
                };
                classes[i][pc[j]].pb(sexo);
            }
        }
        for (int j = 0; j < (1 << i); ++j) vis[j] = 0;
    }
    int t; cin >> t;
    // ideia: faz classes, (e o w)
    vector ord(21, vector(21, vector<int>()));
    while (t--) {
        // dp[qtd_bits][num_bichos][quem_sobra]
        // dp[n][2^n][2^n]
        int n, k, m; cin >> n >> k >> m;
        vector<int> tot(n);
        vector<int> ans;
        if (ord[n][k].empty()) {
            auto& v = ord[n][k];
            int N = sz(classes[n][k]);
            v.resize(N);
            iota(all(v), 0);
            sort(all(v), [&] (int x, int y) {
                return sz(classes[n][k][x]) < sz(classes[n][k][y]);
            });
        }
        int id = 0;
        for (auto z : ord[n][k]) {
            auto v = classes[n][k][z];
            for (auto x : v) {
                for (int j = 0; j < n; ++j) {
                    int val = (x>>j&1);
                    tot[j] += val;
                }
                ans.pb(x);
            }
            m -= sz(v);
            id++;
        }
        if (m) {
            //
        }
        cout << (*max_element(all(tot))) << endl;
        for (auto x : ans) {
            for (int j = 0; j < n; ++j) cout << (x>>j&1);
            cout << endl;
        }
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
