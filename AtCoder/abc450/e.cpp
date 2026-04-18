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
    string s0, s1; cin >> s0 >> s1;
    vector<int> tam = {sz(s0), sz(s1)};
    vector<vector<int>> freq(2, vector<int>(26));
    vector ps_base(2, vector(26, vector<int>()));
    for (auto x : s0) freq[0][x-'a']++;
    for (auto x : s1) freq[1][x-'a']++;
    for (int w = 0; w < 2; ++w) {
        for (int c = 0; c < 26; ++c) {
            int tot = 0;
            ps_base[w][c].pb(0);
            for (int i = 0; i < sz(s0); ++i) {
                tot += s0[i] == char('a'+c);
                ps_base[w][c].pb(tot);
            }
        }
        swap(s0, s1);
    }
    int t = 2;
    while (true) {
        int prox = tam[t-1] + tam[t-2];
        tam.pb(prox);
        freq.pb(vector<int>(26));
        for (int i = 0; i < 26; ++i) freq[t][i] = freq[t-1][i] + freq[t-2][i];
        t++;
        if (prox >= 1e18 and t % 2 == 1) break;
    }
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        char c; cin >> c;
        int C = c - 'a', ans = 0;
        auto solve = [&] (auto&& self, int lx, int rx, int cur) -> void {
            if (cur <= 1) {
                ans += ps_base[cur][C][rx] - ps_base[cur][C][lx-1];
                return;
            }
            if (lx == 1 and rx == tam[cur]) {
                ans += freq[cur][C];
                return;
            }
            if (rx <= tam[cur-1]) self(self, lx, rx, cur-1);
            else if (tam[cur-1] < lx) self(self, lx-tam[cur-1], rx-tam[cur-1], cur-2);
            else self(self, lx, tam[cur-1], cur-1), self(self, 1, rx-tam[cur-1], cur-2);
        };
        solve(solve, l, r, t-1);
        cout << ans << endl;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}

