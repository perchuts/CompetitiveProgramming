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

void solve(){
    int n, d; cin >> n >> d;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    vector dp(d+1, vector(d+1, vector(n+1, 0LL)));
    dp[0][0][0] = 1;
    int tot_d = 0, extra = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) {
            extra++;
            for (int le = 0; le <= tot_d; ++le) {
                for (int j = i+1; j; --j) dp[le][tot_d-le][j] = dp[le][tot_d-le][j-1];
                dp[le][tot_d-le][0] = 0;
            }
            continue;
        }
        for (int poe = min(a[i], b[i]); poe <= max(a[i], b[i]); ++poe) {
            for (int le = 0; le <= tot_d; ++le) {
                int nle = le + abs(poe - a[i]), nre = tot_d - le + abs(poe - b[i]), add = (poe == a[i] or poe == b[i]);
                if (max(nle, nre) > d) continue;
                for (int j = 0; j <= i; ++j) {
                    dp[nle][nre][j+add] += dp[le][tot_d-le][j];
                    if (dp[nle][nre][j+add] >= mod) dp[nle][nre][j+add] -= mod;
                }
            }
        }
        tot_d += abs(a[i] - b[i]);
        if (tot_d > 2 * d) {
            cout << 0 << endl;
            exit(0);
        }
    }
    int ans = 0, N = d + n + 1;
    vector<int> fat(N, 1), ifat(N);
    for (int i = 1; i < N; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto C = [&] (int a, int b) {
        assert(a >= b);
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    for (int le = 0; le <= tot_d; ++le) {
        for (int i = extra; i <= n; ++i) {
            int lado = 1;
            for (int j = 0; j <= extra; ++j) {
                // posso andar pra casa do caralho o quanto eu quiser!
                int ri = tot_d - le, sobra = d - max(ri, le);
                if (sobra < j) break;
                int ways = dp[le][ri][i] * C((sobra-j)+(i-extra+j), sobra-j) % mod * lado % mod * C(extra, j) % mod;
                ans = (ans + ways) % mod;
                lado = 2 * lado % mod;
            }
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
