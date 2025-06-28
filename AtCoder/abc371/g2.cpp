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
    vector<int> p(n), a(n);
    for (auto& x : p) cin >> x, --x;
    for (auto& x : a) cin >> x, --x;
    // o problema eh basicamente sobre TCR
    vector<int> vis(n, -1);
    vector<vector<int>> cyc;
    for (int i = 0; i < n; ++i) {
        if (vis[i] != -1) continue;
        cyc.pb({});
        int cur = i;
        while (vis[cur] == -1) vis[cur] = sz(cyc)-1, cyc.back().pb(cur), cur = p[cur];
    }
    vector<int> repr(n+1, inf);
    for (int i = 0; i < sz(cyc); ++i) {
        int mn = *min_element(all(cyc[i]));
        assert(mn == cyc[i][0]);
        ckmin(repr[sz(cyc[i])], mn);
    }
    vector<int> sol_mod(n+1), vp(n+1);
    for (int tam = 2; tam <= n; ++tam) {
        if (repr[tam] == inf) continue;
        int j = vis[repr[tam]], cur = tam, g = 1;
        for (int k = 2; k * k <= tam; ++k) {
            int cnt = 0;
            while (cur % k == 0) cnt++, cur /= k;
            ckmin(cnt, vp[k]);
            while (cnt) g *= k, cnt--;
        }
        if (cur and vp[cur]) g *= cur;
        int best = -1, val = inf;
        for (int w = sol_mod[g]; w < tam; w += g) {
            if (ckmin(val, a[cyc[j][w]])) best = w;
        }
        assert(best != -1);
        
    }
    for (auto x : a) cout << x + 1 << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
