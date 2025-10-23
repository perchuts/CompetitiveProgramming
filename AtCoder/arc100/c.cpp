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
    vector<int> a(1<<n);
    for (auto& x : a) cin >> x;
    // maior cara que segue i ate o bit turn
    // want to compute maximum of a[i] + a[j] where i | j = k
    vector<vector<int>> dp(n+1, vector<int>(1<<n, -inf));
    dp[n] = a;
    for (int turn = n-1; ~turn; --turn) {
        for (int i = 0; i < (1 << n); ++i) {
            if (i >> turn & 1) dp[turn][i] = max(dp[turn+1][i], dp[turn+1][i-(1<<turn)]);
            else dp[turn][i] = dp[turn+1][i];
        }
    }
    vector<int> opt(1<<n);
    for (int i = 1; i < (1<<n); ++i) {
        opt[i] = opt[i-1];
        for (int j = 0; j < n; ++j) {
            // ateh onde ambos vao seguir o i. um deles vai quebrar aqui
            if (i >> j & 1) {
                // aqui eles podem se diferenciar.
                ckmax(opt[i], dp[j+1][i] + dp[j+1][i-(1<<j)]);
            }
        }
        cout << opt[i] << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
