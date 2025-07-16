#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

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

int score(int& n, vector<vector<int>>& grid) {
    int tot = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-1; ++j) {
            tot += (grid[i][j]-grid[i][j+1]) * (grid[i][j]-grid[i][j+1]);
            tot += (grid[j][i]-grid[j+1][i]) * (grid[j][i]-grid[j+1][i]);
        }
    }
    return tot;
}

vector<vector<int>> brute(int n, vector<vector<int>> grid) {
    int ans = inf;
    vector<vector<int>> resp;
    auto go = [&] (auto&& self, int k, int cur) -> void {
        if (cur >= ans) return;
        if (k == n * n) { 
            ans = cur, resp = grid;
            return;
        }
        int i = k / n, j = k % n, ncur = cur;
        if (i != 0) ncur += (grid[i][j]-grid[i-1][j]) * (grid[i][j]-grid[i-1][j]);
        if (j != 0) ncur += (grid[i][j]-grid[i][j-1]) * (grid[i][j]-grid[i][j-1]);
        self(self, k+1, ncur);
        if (grid[i][j] == 0) {
            for (int p = 1; p <= 5; ++p) {
                grid[i][j] = p, ncur = cur;
                if (i != 0) ncur += (grid[i][j]-grid[i-1][j]) * (grid[i][j]-grid[i-1][j]);
                if (j != 0) ncur += (grid[i][j]-grid[i][j-1]) * (grid[i][j]-grid[i][j-1]);
                self(self, k+1, ncur);
            }
            grid[i][j] = 0;
        }
    };
    go(go, 0, 0);
    return resp;
}

vector<vector<int>> solve(int n, vector<vector<int>> grid) {
    vector<vector<int>> pode(n, vector<int>(n));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) pode[i][j] = (grid[i][j] == 0);
    int a[] = {1, -1, 0, 0, 0, 0, 1, -1};
    while (true) {
        bool ok = false;
        iii pos;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!pode[i][j]) continue;
                auto calc = [&] (int x) {
                    int tot = 0;
                    for (int k = 0; k < 4; ++k) {
                        int x2 = i + a[k], y2 = j + a[k+4];
                        if (min(x2, y2) < 0 or max(x2, y2) == n) continue;
                        tot += (x-grid[x2][y2])*(x-grid[x2][y2]);
                    }
                    return tot;
                };
                int best = calc(grid[i][j]), val = grid[i][j];
                for (int k = 0; k <= 5; ++k) {
                    if (ckmin(best, calc(k))) val = k;
                }
                if (val != grid[i][j]) {
                    ok = true;
                    pos = {i, j, val};
                }
            }
        }
        if (!ok) break;
        auto [i, j, val] = pos;
        grid[i][j] = val;
    }
    return grid;
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (auto& x : grid) for (auto& y : x) cin >> y;
    auto ans = solve(n, grid);
    cout << score(n, ans) << endl;
    for (auto x : ans) {
        for (auto y : x) cout << y << ' ';
        cout << endl;
    }

#else
    int t = 1;
    while (true) {
        int n = rnd(1, 2);
        int lim = 8;
        vector<vector<int>> grid(n, vector<int>(n));
        for (auto& x : grid) {
            for (auto& y : x) {
                y = rnd((lim == 0), 5);
                if (y == 0) --lim;
            }
        }
        auto my = solve(n, grid);
        auto ans = brute(n, grid);

        if (score(n, my) != score(n, ans)) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << score(n, my) << endl;
            for (auto x : my) {
                for (auto y : x) cout << y << ' ';
                cout << endl;
            }
            cout << "Answer: " << score(n, ans) << endl;
            for (auto x : ans) {
                for (auto y : x) cout << y << ' ';
                cout << endl;
            }
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
