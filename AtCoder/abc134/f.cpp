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
    int n, k; cin >> n >> k;
    vector dp(n+1, vector(n*n+1, 0LL));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        vector ndp(n+1, vector(n*n+1, 0LL));
        for (int comps = 0; comps <= i; ++comps) {
                for (int score = 0; score <= n*n; ++score) {
                    int nc, ns;
                    // vou usar mais pra frente - ambos
                    nc = comps-1, ns = score-2*nc;
                    if (min(nc, ns) >= 0) ndp[comps][score] = (ndp[comps][score] + dp[nc][ns]) % mod;
                    // vou me colocar em uma ponta de alguma fileira
                    nc = comps, ns = score-2*nc;
                    if (ns >= 0) ndp[comps][score] = (ndp[comps][score] + dp[nc][ns] * 2 * nc) % mod;
                    // vou fechar alguma fileira
                    nc = comps+1, ns = score-2*nc;
                    if (ns >= 0 and nc <= n) ndp[comps][score] = (ndp[comps][score] + dp[nc][ns] * nc) % mod;
                    // vou me colocar aqui
                    nc = comps, ns = score-2*nc;
                    if (ns >= 0) ndp[comps][score] = (ndp[comps][score] + dp[nc][ns]) % mod;
                    // vou juntar duas fileiras
                    nc = comps+1, ns = score-2*nc;
                    if (nc <= n and ns >= 0) ndp[comps][score] = (ndp[comps][score] + dp[nc][ns] * nc * (nc-1)) % mod;
                }
            }
        swap(dp, ndp);
    }
    cout << dp[0][k] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
