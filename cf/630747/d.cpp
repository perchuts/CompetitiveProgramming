#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

// Claro, aqui vai a solução para o problema!! 
int solve(int n, int w, int k, vector<int> x, vector<int> y) {
    vector<vector<int>> sexo(31);
    for (int i = 0; i < n; ++i) sexo[x[i]].push_back(y[i]);
    for (int i = 0; i <= 30; ++i) {
        sort(all(sexo[i]));
        reverse(all(sexo[i]));
        for (int j = 1; j < sz(sexo[i]); ++j) sexo[i][j] += sexo[i][j-1];
        if (sz(sexo[i]) > k+1) sexo[i].resize(k+1);
    }
    const int MAXW = 1005;
    vector<vector<int>> dp(MAXW, vector<int>(k+1, -1e18));
    vector<int> pot(32, 1);
    for (int i = 1; i <= 31; ++i) pot[i] = pot[i-1] + pot[i-1];
    dp[min(MAXW-1, w / pot[31])][0] = 0;
    for (int bit = 30; ~bit; --bit) {
        int eu = (w >> bit & 1);
        for (int i = MAXW-1; ~i; --i) {
            for (int j = 0; j <= k; ++j) {
                ckmax(dp[min(MAXW-1, 2 * i + eu)][j], dp[i][j]);
            }
        }
        for (int i = MAXW-2; ~i; --i) {
            for (int j = 0; j <= k; ++j) {
                ckmax(dp[i][j], dp[i+1][j]);
            }
        }
        auto ndp = dp;

        for (int S = 0; S < MAXW + k; ++S) {
            if (sexo[bit].empty()) continue;
            auto go = [&] (auto&& self, int lx, int rx, int lopt, int ropt) -> void {
                if (lx > rx) return;
                int i = (lx + rx)/2, j = S - i, opt = i;
                for (int ep = max(lopt, i+1); ep <= ropt; ++ep) {
                    int use = ep - i;
                    if (j - use >= 0 and use <= sz(sexo[bit]) and ckmax(ndp[i][j], dp[i+use][j-use] + sexo[bit][use-1])) opt = ep;
                }
                self(self, lx, i-1, lopt, opt);
                self(self, i+1, rx, opt, ropt);
            };
            go(go, max(0LL, S - k), min(MAXW-1, S), max(0LL, S - k), min(MAXW-1, S));
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i < MAXW; ++i) {
        ckmax(ans, dp[i][k]);
    }
    return ans;
}

int32_t main() {_
    int t = 1; //cin >> t;
    while(t--) {
        int n, w, k; cin >> n >> w >> k;
        vector<int> x(n), y(n);
        vector<vector<int>> sexo(31);
        for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
        cout << solve(n, w, k, x, y) << endl;
    }
}
