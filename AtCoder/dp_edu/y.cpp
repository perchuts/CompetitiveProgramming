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

void solve(){
    int n, m, k; cin >> n >> m >> k;
    int N = 2*(n+m);
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
        if (a < b) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    vector<ii> cells(k);
    for (auto& [x, y] : cells) cin >> x >> y;
    // dp[i] = numeros de caminhos de (1, 1) ate cells[i] com i sendo a primeira celula que o caminho atinge
    // resposta = C(N+M, N) - sum(dp[i] * caminhos de cell[i] ate (N, M))
    // entao o problema se reduz a calcular dp[i]
    vector<int> dp(n);
    sort(all(cells));
    int ans = C(n+m-2, n-1);
    for (int i = 0; i < k; ++i) {
        auto [x, y] = cells[i];
        dp[i] = C(x+y-2, x-1);
        for (int j = 0; j < i; ++j) {
            auto [x2, y2] = cells[j];
            if (x2 <= x and y2 <= y) {
                dp[i] = (dp[i] - dp[j] * C(x-x2+y-y2, x-x2)) % mod;
                dp[i] = (dp[i] + mod) % mod;
            }
        }
        int ways = dp[i] * C(n-x+m-y, n-x) % mod;
        ans = (ans + mod - ways) % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
