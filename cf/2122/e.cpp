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
    int n, k; cin >> n >> k;
    int up, down;
    vector<int> a(n), b(n);
    cin >> up;
    for (int i = 0; i < n-1; ++i) cin >> a[i];
    for (int i = 0; i < n-1; ++i) cin >> b[i];
    cin >> down;
    int sexo = k, shift = sexo-1;
    vector<int> dp(k+1);
    dp[sexo] = 1;
    for (int i = 0; i < n-1; ++i) {
        vector<int> ndp(k+1), ways(2*shift+1);
        for (int x1 = 1; x1 <= k; ++x1) {
            if (a[i] != -1 and x1 != a[i]) continue;
            for (int x2 = 1; x2 <= k; ++x2) {
                if (b[i] != -1 and x2 != b[i]) continue;
                ways[shift+x2-x1]++;
            }
        }
        for (int score = -k+1; score <= 0; ++score) ndp[sexo] = (ndp[sexo] + ways[shift+score]*dp[sexo]) % mod;
        for (int j = 0; j < k; ++j) {
            for (int score = -k+1; score <= k-1; ++score) {
                    int c = ways[shift+score];
                    if (score+j < 0) continue;
                    int tr;
                    if (score > 0) {
                        if (j == score) ndp[j] = (ndp[j] + c*dp[sexo]) % mod;
                        tr = score;
                    } else tr = score+j;
                    if (tr < 0) continue;
                    ndp[tr] = (ndp[tr] + c*dp[j]) % mod;
                }
            }
        swap(dp, ndp);
    }
    int ans = 0;
    for (auto x : dp) ans = (ans + x) % mod;
    if (up == -1) ans = ans * k % mod;
    if (down == -1) ans = ans * k % mod;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
