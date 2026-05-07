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
    int n; cin >> n;
    vector<vector<int>> grid(n, vector<int>(n)), mn(n, vector<int>(n, inf)), mx(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c; cin >> c;
            grid[i][j] = (c == '@');
        }
    }
    mn[0][0] = mx[0][0] = 0;
    vector<int> ans(2*n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i) ckmin(mn[i][j], mn[i-1][j] + grid[i][j]), ckmax(mx[i][j], mx[i-1][j] + grid[i][j]);
            if (j) ckmin(mn[i][j], mn[i][j-1] + grid[i][j]), ckmax(mx[i][j], mx[i][j-1] + grid[i][j]);
            ans[mn[i][j]]++;
            ans[mx[i][j]+1]--;
        }
    }
    cout << ans[0] << endl;
    for (int i = 1; i < 2*n-1; ++i) {
        ans[i] += ans[i-1];
        cout << ans[i] << endl;
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
