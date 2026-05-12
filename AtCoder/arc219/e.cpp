#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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
    n *= 2, m *= 2;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<string> ans(n, string(m, 'A'));
    int qt = 0;
    for (int i = n/2; i < n; ++i) for (auto& x : ans[i]) x = 'B';
    for (int i = 0; i < n/2; ++i) {
        for (auto x : grid[i]) qt += (x == 'o');
    }
    for (int col = 0; qt != (n/2)*(m/2); ++col) {
        for (int i = 0; i < n/2 and qt != (n/2)*(m/2); ++i) {
            if (col != m-1) {
                if (grid[n/2-1-i][col] == 'o') qt--;
                ans[n/2-1-i][col] = 'B';
                if (grid[n/2+i][m-1-col] == 'o') qt++;
                ans[n/2+i][m-1-col] = 'A';
            } else {
                if (grid[i][col] == 'o') qt--;
                ans[i][col] = 'B';
                if (grid[n-1-i][m-1-col] == 'o') qt++;
                ans[n-1-i][m-1-col] = 'A';
            }
        }
    }
    for (auto x : ans) cout << x << endl;
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
