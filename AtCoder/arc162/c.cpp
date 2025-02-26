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
    vector<vector<int>> g(n);
    vector<int> par(n);
    for (int i = 1; i < n; ++i) {
        cin >> par[i];
        --par[i];
        g[par[i]].pb(i);
    }
    vector<int> a(n), dead(n), falta(n+1);
    vector<vector<int>> freq(n, vector<int>(n+1));
    for (auto& x : a) cin >> x;
    bool can = 0;
    auto process = [&] (auto&& self, int u) -> void {
        if (a[u] == -1) dead[u] = 1;
        else freq[u][a[u]] = 1;
        for (auto v : g[u]) {
            self(self, v);
            for (int i = 0; i <= n; ++i) freq[u][i] += freq[v][i];
            dead[u] += dead[v];
        }
        for (int i = 0; i < k; ++i) falta[u] += (freq[u][i] == 0);
        if (max(falta[u], dead[u]) <= 1 and freq[u][k] == 0 and falta[u] <= dead[u]) can = 1;
    };
    process(process, 0);
    cout << (can ? "Alice" : "Bob") << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
