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

int solve(int n, vector<int> a) {
    vector<array<int, 2>> cx(n+1);
    cx[0][0] = 1;
    stack<ii> st; st.push({0, 0});
    int ans = 0;
    vector<array<int, 2>> ayuda(n+1);
    for (int i = 1; i <= n; ++i) {

        while (st.top().first >= a[i-1]) st.pop();
        int ptr = st.top().second, eu = i & 1;
        cx[i] = cx[i-1];

        int ways = -a[i-1] * (cx[i-1][eu] - (ptr?cx[ptr-1][eu]:0)) % mod + a[i-1] * (cx[i-1][eu^1] - (ptr?cx[ptr-1][eu^1]:0)) % mod;
        ways %= mod;
        ways = (ways + mod) % mod;

        // qual vai ser o coeficiente se alguem dessa paridade aparecer pra me resgatar
        ayuda[i][eu] = (ways + ayuda[ptr][eu]) % mod;
        ayuda[i][eu^1]   = (mod - ayuda[i][eu]) % mod;
       
        ans = ayuda[i][eu];

        cx[i][eu] = (cx[i][eu] + ayuda[i][eu]) % mod;

        st.push({a[i-1], i});
    }
    return ans;
}

int brute(int n, vector<int> a) {
    vector<int> dp(n+1);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int mn = a[i-1], c = 1;
        for (int j = i-1; ~j; --j, c *= -1) {
            dp[i] = (dp[i] + c * dp[j] * mn) % mod;
            dp[i] = (dp[i] + mod) % mod;
            if (j) ckmin(mn, a[j-1]);
        }
    }
    return dp[n];
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << solve(n, a) << endl;
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
