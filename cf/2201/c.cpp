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
const int mod = (119<<23)+1;
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
    string s; cin >> s;
    vector<int> pot(n+1, 1), invp(n+1, 1);
    int inv2 = (mod+1)/2;
    for (int i = 1; i <= n; ++i) pot[i] = 2 * pot[i-1] % mod, invp[i] = inv2 * invp[i-1] % mod;
    // inicialmente, nossa subsequencia pode ter apenas elementos de uma cor
    // partindo da premissa que s eh uma RBS, essa conta ta certa
    int ans = pot[n/2+1]-2;
    vector<int> start(n+1), abre(n+1), fecha(n+1), trs(n+1), ps(n+1);
    vector<int> vals = {1}, rev_v(n+1);
    for (int i = 1; i < n; ++i) {
        if (s[i] == '(') vals.pb(vals.back()+1);
        else vals.pb(vals.back()-1);
    }
    rev_v[n] = 1;
    for (int i = n-1; i >= 1; --i) rev_v[i] = rev_v[i+1] + (s[i-1] == ')' ? 1 : -1);
    int lst_0 = 0, acum = 0;
    for (int i = 1; i <= n; ++i) {
        abre[i] = abre[i-1];
        fecha[i] = fecha[i-1];
        ps[i] = ps[i-1];
        if (s[i-1] == '(') {
            abre[i]++;
            start[i] = pot[fecha[i]];
            trs[i] = acum;
            ps[i] = (ps[i] + (trs[i] + start[i]) * invp[abre[i]]) % mod;
        } else {
            int dp = pot[abre[i]] * (mod+ps[i] - ps[lst_0]) % mod;
            if (rev_v[i] == 1) dp = 0;
            start[i] = pot[abre[i]];
            fecha[i]++;
            // vou ser o ultimo?
            ans = (ans + dp * pot[n/2-fecha[i]]) % mod;
            acum = (2 * acum + dp) % mod;
        }
        if (vals[i-1] == 1) lst_0 = i;
    }
    vector<vector<int>> dp(n+1, vector<int>(3));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i-1];
        if (s[i-1] == '(') {
            dp[i][0] = (2 * dp[i][0]) % mod;
            dp[i][2] = (2 * dp[i][2] + dp[i][1]) % mod;
        } else {
            dp[i][1] = (2 * dp[i][1] + dp[i][0] + dp[i][2]) % mod;
        }
    }
    ans = (ans + dp[n][2]) % mod;
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
