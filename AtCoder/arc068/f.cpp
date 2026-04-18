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

int brute(int n, int k) {
    vector<int> p(n); iota(all(p), 1);
    int ans = 0;
    do {
        int c1 = n+1, c2 = n+2;
        if (p[k-1] != 1) continue;
        bool ok = 1;
        for (int i = 0; i < k; ++i) {
            if (p[i] > c2) { ok = 0; break; }
            if (p[i] < c1) c1 = p[i];
            else c2 = p[i];
        }
        for (int i = k; i < n; ++i) ok &= (c2 > p[i]), c2 = p[i];
        ans += ok;
        //if (ok) {
        //    for (auto x : p) cout << x << " ";
        //    cout << endl;
        //}
    } while (next_permutation(all(p)));
    for (int i = 0; i < n-k-1; ++i) ans = (ans + ans) % mod;
    return ans;
}

void solve() {
    int n, k; cin >> n >> k;
    // {7, 6, 3, 2}
    // {5, 4}
    // you give me a sequence.
    // 1 has to be in position k.
    // the LIS of the sequence must be two (or one, but this implies n --- 1), k = n.
    // 1 2 3 4 5 6 7 8 9 10
    // x   x y x   x x x  x
    // lets say that i have two sequences. how many of then can generate what i want?
    //
    // c1, c2
    // i see something. if this something is smaller than c1, c2, make c1 := y.
    // else, if y > c1, c2, you simply died.
    // then c1 < y < c2. make c2 := y.
    // this deterministically maps every valid sequence to a pair of decreasing sequences.
    // keep c1, c2, largest number not taken.
    // it must hold that if y > c1, y = largest number not taken!!
    // x x + k . . . . . . . 1 x + k + z
    //
    // [last number from c1][how many numbers i have left on the right]
    // from this we can recover how many numbers we wrote:
    // [i][j]
    // n - i + 1 - j
    // n + 1 - (i + j)
    // increasing order of i + j.
    // [i][j] -> [i][j-1]
    // [i][j] -> [i-k][j+k-1]
    // diagonal transition
    //if (n <= 8) cout << brute(n, k) << endl;
    vector<vector<int>> diag(2*n+1, vector<int>(n+1));
    vector<vector<int>> dp(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; ++i) diag[0][i] = 1;
    for (int w = 1; w <= k; ++w) {
        // n + 1 - (i + j) = w
        // n + 1 - i - w = j
        // 
        for (int i = 1, j = n - w; i <= n+1-w; ++i, --j) {
            dp[i][j] = diag[w-1][i];
            //cout << "i = " << i << " j = " << j << ": " << dp[i][j] << endl;
        }
        //cout << endl;
        diag[w][n+1-w] = dp[n+1-w][0];
        for (int i = n-w; i >= 1; --i) diag[w][i] = (dp[i][n+1-i-w] + diag[w][i+1]) % mod;
    }
    int ans = (dp[1][n-k] - dp[1][n-k+1] + mod) % mod;
    for (int i = 0; i < n-k-1; ++i) ans = 2 * ans % mod;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
