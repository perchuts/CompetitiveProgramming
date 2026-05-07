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
    vector<array<int, 2>> v(3);
    vector<vector<int>> mark(n, vector<int>(m));
    for (int i = 0; i < 3; ++i) cin >> v[i][0] >> v[i][1], --v[i][0], --v[i][1], mark[v[i][0]][v[i][1]] = 1;
    vector<int> a = {1, -1, 0, 0, 0, 0, 1, -1};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int score = 0;
            for (int k = 0; k < 4; ++k) {
                int i2 = i + a[k], j2 = j + a[k+4];
                if (min(i2, j2) >= 0 and i2 != n and j2 != m and mark[i2][j2]) score++;
            }
            if (score == 3) {
                cout << "NO" << endl;
                return;
            }
        }
    }
    cout << "YES" << endl;
    vector<vector<int>> par(2);
    for (int i = 0; i < 3; ++i) par[(v[i][0]+v[i][1]) % 2].pb(i);
    vector<vector<char>> ans(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i+j)%2) ans[i][j] = 'R';
            else ans[i][j] = 'B';
        }
    }
    if (!par[0].empty() and !par[1].empty()) {
        if (sz(par[0]) == 2) {
            int i = par[0][0];
            ans[v[i][0]][v[i][1]] = 'G';
        } else {
            int i = par[1][0];
            ans[v[i][0]][v[i][1]] = 'G';
        }
    } else {
        int p1 = -1, p2 = -1;
        for (int i = 0; i < 3; ++i) {
            for (int j = i+1; j < 3; ++j) {
                if (abs(v[i][0]-v[j][0])+abs(v[i][1]-v[j][1]) != 2) p1 = i, p2 = j;
            }
        }
        assert(p1 != -1);
        char choice;
        if ((v[0][0]+v[0][1]) % 2) {
            choice = 'B';
        } else {
            choice = 'R';
        }
        ans[v[p1][0]][v[p1][1]] = choice;
        ans[v[p2][0]][v[p2][1]] = 'G';
        for (int i = 0; i < 4; ++i) {
            int x = v[p1][0] + a[i], y = v[p1][1] + a[i+4];
            if (min(x, y) >= 0 and x != n and y != m) ans[x][y] = 'G';
        }
    }
    for (auto x : ans) {
        for (auto y : x) cout << y;
        cout << endl;
    }
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
