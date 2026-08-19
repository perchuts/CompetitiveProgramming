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
    int n, m, q; cin >> n >> m >> q;
    vector<string> s(n);
    for (auto& x : s) cin >> x;
    vector<int> appear(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) appear[j] |= (1 << (s[i][j] - '0'));
    }
    vector<ii> clauses;
    for (int i = 0; i < m; ++i) {
        if (appear[i] == 1) {
            clauses.pb({i+m, i+m});
        }
        if (appear[i] == 2) {
            clauses.pb({i, i});
        }
    }
    vector<vector<int>> mark(2, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        for (int j = i+1; j < m; ++j) {
            if (min(appear[i], appear[j]) != 3) continue;
            // e se o bit i for zero?
            mark[0][0] = mark[0][1] = mark[1][0] = mark[1][1] = 0;
            for (int k = 0; k < n; ++k) {
                mark[s[k][i]-'0'][s[k][j]-'0'] = 1;
            }
            if (!mark[0][0]) clauses.pb({i, j});
            if (!mark[0][1]) clauses.pb({i, j+m});
            if (!mark[1][0]) clauses.pb({i+m, j});
            if (!mark[1][1]) clauses.pb({i+m, j+m});
        }
    }
    while (q--) {
        string t; cin >> t;
        auto check = [&] (int x) {
            if (x >= m) return (t[x-m] == '0');
            return t[x] == '1';
        };
        bool ok = 1;
        for (auto [x, y] : clauses) {
            ok &= (check(x) or check(y));
        }
        cout << (ok ? "Yes" : "No") << endl;
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
