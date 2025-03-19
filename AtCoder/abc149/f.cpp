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
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    vector<int> subt(n, 1);
    auto pre = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
            subt[u] += subt[v];
        }
    };
    pre(pre, 0, 0);
    vector<int> pot(n+1, 1);
    for (int i = 1; i <= n; ++i) pot[i] = 2 * pot[i-1] % mod;
    int ans = n * (pot[n-1]-1+mod) % mod;
    for (int i = 0; i < n; ++i) {
        for (auto j : g[i]) {
            if (subt[i] > subt[j]) ans = (ans - pot[subt[j]] + 1) % mod;
            else ans = (ans - pot[n-subt[i]] + 1) % mod;
            ans = (ans + mod) % mod;
        }
    }
    cout << (ans * fexp(pot[n], mod-2)) % mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
