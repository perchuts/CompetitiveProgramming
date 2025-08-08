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
    int n, m; cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (auto& x : grid) for (auto& y : x) cin >> y, --y;
    vector<int> pot(11, 1);
    for (int i = 1; i <= 10; ++i) pot[i] = 4 * pot[i-1];
    vector<int> rep(1<<20, 15);
    for (int i = 0; i < (1<<20); ++i) {
        int lst = -1;
        for (int j = 0; j < 10; ++j) {
            int cur = (i/pot[j])%4;
            if (lst == cur) { rep[i] = j; break; }
            lst = cur;
        }
    }
    auto rotate = [&] (vector<vector<int>>& x, int k) {
        int a = k & 1, b = (k & 2) / 2;
        for (int i = 0; i < n-1; ++i) {
            for (int j = 0; j < (m-1)/2; ++j) {
                swap(x[i+a][j+b], x[n-2-i+a][m-2-j+b]);
            }
        }
        if ((m&1) == 0) {
            int j = (m-1)/2;
            for (int i = 0; i < (n-1)/2; ++i) swap(x[i+a][j+b], x[n-2-i+a][m-2-j+b]);
        }
    };
    map<vector<vector<int>>, int> sexo;
    vector<vector<int>> model(n, vector<int>(m));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) model[i][j] = m * i + j;
    vector<vector<vector<int>>> tgrid(1);
    for (int steps = 0; steps <= 10; ++steps) {
        vector<vector<vector<int>>> ntgrid(pot[steps]);
        for (int mask = 0; mask < pot[steps]; ++mask) {
            if (rep[mask]+1 <= steps) continue;
            ntgrid[mask] = (steps == 0 ? model : tgrid[mask % pot[steps-1]]);
            if (steps) rotate(ntgrid[mask], (mask / pot[steps-1]) & 3);
            if (!sexo.count(ntgrid[mask])) sexo[ntgrid[mask]] = steps;
        }
        swap(tgrid, ntgrid);
    }
    int ans = 21;
    for (auto [eu, k] : sexo) {
        vector<vector<int>> need(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int i2 = eu[i][j] / m, j2 = eu[i][j] % m;
                need[i][j] = grid[i2][j2];
            }
        }
        vector<vector<int>> need2(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int i2 = need[i][j] / m, j2 = need[i][j] % m;
                need2[i2][j2] = m * i + j;
            }
        }
        if (sexo.count(need)) ckmin(ans, sexo[need] + k);
    }
    cout << (ans == 21 ? -1 : ans) << endl;
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
