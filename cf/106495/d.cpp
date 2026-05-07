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
    int n, k, s, h; cin >> n >> k >> s >> h;
    using ld = long double;
    vector<ld> b(n+1), c(n+1), v(n+1), q(n+1);
    // b = achar bateria
    // c = achar comida
    // v = morrer por causa da comida
    // q = bicho fraco
    for (int i = 1; i <= n; ++i) cin >> b[i] >> c[i] >> v[i] >> q[i];
    vector dp(n+1, vector(n+1, vector(k+1, vector<ld>(h+1))));
    for (int m = 0; m <= n; ++m) {
        for (int e = 0; e <= k; ++e) {
            for (int f = 1; f <= h; ++f) {
                dp[n][m][e][f] = 1;
            }
        }
    }
    for (int d = n-1; ~d; --d) {
        for (int m = 0; m <= d; ++m) {
            for (int e = 0; e <= k; ++e) {
                for (int f = 1; f <= h; ++f) {
                    ld& eu = dp[d][m][e][f];
                    ld B = b[d+1], C = c[d+1], V = v[d+1], Q = q[d+1];
                    ld p = (ld)(m+1)/(d+2), np = 1-p;

                    // hide
                    ckmax(eu, dp[d+1][m+1][e][f-1]*p + dp[d+1][m][e][f-1]*np);

                    // get battery
                    // (got battery, no monster) + (got battery, monster) + (didnt get battery, no monster) + (didnt get battery, monster)
                    ckmax(eu, (e < k ? dp[d+1][m][e+1][f-1]*np*B*(1-Q) : 0) + (e > 1 ? dp[d+1][m][e-1][f-1]*np*B*Q + dp[d+1][m][e-2][f-1]*np*(1-B)*Q : 0) + dp[d+1][m][e][f-1]*np*(1-B)*(1-Q));

                    // get food
                    // (got food, no monster) + (got food, monster) + (didnt get food, no monster) + (didnt get food, monster)
                    ckmax(eu, dp[d+1][m][e][h]*np*C*(1-V)*(1-Q) + Q*np*(e > 1 ? dp[d+1][m][e-2][h]*C*(1-V)+dp[d+1][m][e-2][f-1]*(1-C) : 0) + dp[d+1][m][e][f-1]*np*(1-C)*(1-Q));
                }
            }
        }
    }
    cout << fixed << setprecision(20);
    cout << dp[0][0][s][h] << endl;
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
