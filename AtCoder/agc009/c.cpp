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
    vector<int> z(n);
    int a, b; cin >> a >> b;
    if (a > b) swap(a, b);
    for (auto& x : z) cin >> x;
    auto solve = [&] (vector<int> v) {
        int m = sz(v);
        vector<int> seta(m+1), dp(m+1), sdp(m+1);
        for (int i = 2; i <= m; ++i) {
            if (v[i-1] - v[i-2] >= a) seta[i] = seta[i-1];
            else seta[i] = i-1;
        }
        int ptr = 0;
        for (int i = 1; i <= m; ++i) {
            while (v[i-1] - v[ptr] >= b) ptr++;
            // posso transicionar de ptr pra tras
            // mas apenas de seta[i-1] pra frente (com ressalva em seta[i-1])!
            // entao de seta[i-1]+1 ate ptr eu posso transicionar sem restricoes
            if (seta[i-1] < ptr) {
                dp[i] = (dp[i] + sdp[ptr] - sdp[seta[i-1]] + mod) % mod;
            }
            // agora vamos tentar transicionar pra seta[i-1]. preciso que seta[i-1]+1 enxergue o cara de tras
            if (seta[i-1] <= ptr) {
                // lembrar q seta eh 1 indexado, shiftei eles em 1 dentro do v
                if (seta[i-1] == 0) dp[i] = (dp[i] + 1) % mod;
                else if (seta[i-1] == 1 or v[seta[i-1]] - v[seta[i-1]-2] >= a) dp[i] = (dp[i] + dp[seta[i-1]]) % mod;
            }
            sdp[i] = (sdp[i-1] + dp[i]) % mod;
        }
        int tot = (seta[m] == 0);
        int lst = 3e18;
        for (int i = m; i; --i) {
            if (i == m or i == 1 or v[i] - v[i-2] >= a) tot = (tot + dp[i]) % mod;
            if (lst - v[i-1] < a) break;
            lst = v[i-1];
        }
        return tot;
    };
    vector<int> cur = {z[0]};
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        if (z[i] - z[i-1] >= b) ans = ans * solve(cur) % mod, cur = {z[i]};
        else cur.pb(z[i]);
    }
    ans = ans * solve(cur) % mod;
    cout << ans << endl;
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
