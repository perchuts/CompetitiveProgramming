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
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n, mod; cin >> n >> mod;
    int N = 5*n + 50;
    vector<int> fat(N, 1), ifat(N);
    vector<vector<int>> dp2(n+1, vector<int>(n+1)), dp = dp2;
    dp2[0][0] = 1;
    for (int a = 1; a <= n; ++a) {
        dp2[a][0] = 1;
        for (int b = 1; a+b <= n and a >= b; ++b) {
            dp2[a][b] = (dp2[a-1][b] + dp2[a][b-1]) % mod;
        }
    }
    // score[a][b] = a abres, b fechas, soma de todos os scores possiveis
    // score[a][b] = score[a-1][b] + score[a][b-1] + (quantos sequencias com a abres e b-1 fechas tem um abre sobrando)
    // a >= b
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % mod;
            e /= 2;
            b = b * b % mod;
        }
        return ans;
    };
    for (int i = 1; i < N; ++i) fat[i] = i * fat[i-1] % mod;
    ifat[N-1] = fexp(fat[N-1], mod-2);
    for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto ncr = [&] (int a, int b) {
        if (a < b or b < 0) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    vector<int> ans(n+1);
    for (int a = 0; a <= n; ++a) {
        for (int b = 0; a+b <= n; ++b) {
            if (a + b == 0) continue;
            if (a) dp[a][b] = (dp[a][b] + dp[a-1][b]) % mod;
            if (b) {
                dp[a][b] = (dp[a][b] + dp[a][b-1]) % mod;
                dp[a][b] = (dp[a][b] + ncr(a+b-1, a) - dp2[b-1][a] + mod) % mod;
            }
            ans[a+b] = (ans[a+b] + fat[a] * fat[b] % mod * dp[a][b]) % mod;
        }
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
    //
    // 0 0
    // 1 0
    //
    // 00 0
    // 01 1 1
    // 10 0
    // 11 0
    //      1
    //
    // 000 0
    // 001 1 2
    // 010 1 2
    // 011 1 2
    // 100 0
    // 101 1 2
    // 110 0
    // 111 0
    //       8
    //
    //
    // 0000 0
    // 0001 1 6
    // 0010 1 6
    // 0011 2 8
    // 0100 1 6
    // 0101 2 8
    // 0110 1 4
    // 0111 1 6
    // 1000 0 
    // 1001 1 4
    // 1010 1 4
    // 1011 1 6
    // 1100 0
    // 1101 1 6
    // 1110 0
    // 1111 0
    //       64
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
