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
    int n; cin >> n;
    vector<int> p(n), q(n), prod(n);
    for (int i = 0; i < n; ++i) cin >> p[i] >> q[i];
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    auto inv = [&] (int b, int e = mod-2) {
         int ans = 1;
         while (e) {
            if (e&1) ans = ans * b % mod;
            b = b * b % mod, e /= 2;
         }
         return ans;
    };
    for (int i = 0; i < n; ++i) p[i] = p[i] * inv(q[i]) % mod;
    for (int i = 0; i < n; ++i) {
        prod[i] = (1-p[i]+mod)%mod;
        for (int j : g[i]) prod[i] = prod[i] * p[j] % mod;
    }
    int ans = 0;
    auto adj = [&] (auto&& self, int u, int par) -> void {
        if (u != par) {
            int val = prod[u] * prod[par] % mod;
            val = val * inv(p[u]) % mod * inv(p[par]) % mod;
            ans = (ans + val) % mod;
        }
        for (auto v : g[u]) {
            if (v != par) self(self, v, u);
        }
    };
    adj(adj, 0, 0);
    for (int i = 0; i < n; ++i) {
        int cur = 0;
        for (auto v : g[i]) {
            int my = prod[v] * inv(p[i]) % mod;
            ans = (ans + my * cur % mod * (1+mod-p[i]) % mod) % mod;
            cur = (cur + my) % mod;
        }
        cur = 0;
    }
    vector<int> prod2(n);
    int tot = 0;
    for (int i = 0; i < n; ++i) {
        for (auto v : g[i]) {
            int cur = prod[i] * inv(p[v]) % mod * (1+mod-p[v]) % mod;
            prod2[i] = (prod2[i] + cur) % mod;
        }
        tot = (tot + prod2[i]) % mod;
    }
    for (int i = 0; i < n; ++i) {
        int temp = (tot + mod - prod2[i]) % mod;
        for (auto v : g[i]) if (v > i) temp = (temp - prod2[v] + mod) % mod; 
        ans = (ans + prod2[i] * temp) % mod;
        tot = (tot - prod2[i] + mod) % mod;
    }
    for (int i = 0; i < n; ++i) {
        int cur = 0;
        for (auto v : g[i]) {
            ans = (ans - prod2[v] * cur) % mod;
            ans = (ans + mod) % mod;
            cur = (cur + prod2[v]) % mod;
        }
        cur = 0;
        int cur2 = 0, rem = 0;
        for (auto v : g[i]) {
            int my = (prod2[v] - prod[v] * inv(p[i]) % mod * (1-p[i]) % mod) % mod;
            my = (my + mod) % mod;
            ans = (ans + cur * my % mod * inv(p[i])) % mod;
            cur = (cur + my) % mod;
        }
    }
    ans = (ans + mod) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
