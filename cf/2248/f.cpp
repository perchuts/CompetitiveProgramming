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
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m));
    for (auto& x : a) for (auto& y : x) cin >> y;
    if (n > m) {
        vector<vector<int>> b(m, vector<int>(n));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) b[j][i] = a[i][j];
        swap(b, a);
        swap(n, m);
    }
    if (n+m == 2) {
        cout << (a[0][0] >= 0 ? 0 : -1) << endl;
        return;
    }
    vector<int> sr(n), sc(m);
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) sr[i] += a[i][j], sc[j] += a[i][j];
    int ans = 1e12;
    {
        int l = 0, r = 1e12;
        auto possible = [&] (int x) {
            int z = 0;
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
                if (a[i][j] - x >= sr[i] + sc[j] - 2 * a[i][j] - x * (n + m - 2)) z++;
            }
            return (z >= k);
        };
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (possible(md)) ans = md, r = md-1;
            else l = md+1;
        }
    }
    if (n > 1) {
        cout << ans << endl;
        return;
    }
    n = m;
    int S = sr[0];
    auto A = a[0];
    for (int w = 0; w < 2; ++w) {
        int l = 0, r = 1e12;
        auto possible = [&] (int x) {
            int z = 1;
            // A[0] - a >= S - A[0] - (n-1)x
            int need = 2*A[0] + (n-1)*x - S;
            ckmin(need, x);
            if (need < 0) return false;
            for (int i = 1; i < n; ++i) {
                if (A[i] - x >= S - (n-2) * x - need - A[i]) z++;
            }
            return (z >= k);
        };
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (possible(md)) ckmin(ans, md), r = md-1;
            else l = md+1;
        }
        reverse(all(A));
    }
    cout << ans << endl;


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
