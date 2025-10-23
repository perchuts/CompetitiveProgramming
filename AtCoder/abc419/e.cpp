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
    int n, m, l; cin >> n >> m >> l;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<vector<int>> sexo(l, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = a[i]; j < m; ++j) sexo[i%l][j] += j - a[i];
        for (int j = 0; j < a[i]; ++j) sexo[i%l][j] += m - a[i] + j;
    }
    vector<int> dp(m, 1e18);
    dp[0] = 0;
    for (int i = 0; i < l; ++i) {
        vector<int> ndp(m, 1e18);
        for (int j = 0; j < m; ++j) {
            for (int w = 0; w < m; ++w) {
                int nv = j + w;
                if (nv >= m) nv -= m;
                ckmin(ndp[nv], dp[j] + sexo[i][w]);
            }
        }
        swap(dp, ndp);
    }
    cout << dp[0] << endl;
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
