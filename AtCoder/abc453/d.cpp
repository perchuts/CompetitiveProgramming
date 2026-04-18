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
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector dist(n, vector<vector<int>>(m, vector<int>(4, inf)));
    vector par(n, vector<vector<iii>>(m, vector<iii>(4)));
    int is, js, ig, jg;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'S') is = i, js = j;
            if (grid[i][j] == 'G') ig = i, jg = j;
        }
    }
    queue<iii> q;
    for (int i = 0; i < 4; ++i) q.push({is, js, i}), dist[is][js][i] = 0;
    vector<int> a = {1, -1, 0, 0, 0, 0, 1, -1};
    // down, up, right, left
    while (!q.empty()) {
        auto [i, j, dir] = q.front(); q.pop();
        for (int k = 0; k < 4; ++k) {
            int i2 = i + a[k], j2 = j + a[k+4];
            if (min(i2, j2) < 0) continue;
            if (i2 == n or j2 == m) continue;
            if (grid[i2][j2] == '#') continue;
            if (grid[i][j] == 'o' and k != dir) continue;
            if (grid[i][j] == 'x' and k == dir) continue;
            if (ckmin(dist[i2][j2][k], dist[i][j][dir]+1)) {
                q.push({i2, j2, k}), par[i2][j2][k] = {i, j, dir};
            }
        }
    }

    string ans;
    int ci = -1, cj = -1, dir = -1;
    for (int i = 0; i < 4; ++i) if (dist[ig][jg][i] < inf) ci = ig, cj = jg, dir = i;
    if (dir == -1) {
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
    string rec = "DURL";
    while (ci != is or cj != js) {
        ans += rec[dir];
        auto [ni, nj, nd] = par[ci][cj][dir];
        ci = ni, cj = nj, dir = nd;
    }
    reverse(all(ans));
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
