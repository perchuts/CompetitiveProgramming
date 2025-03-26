#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
void query(int i, int j) {
    cout << i+1 << ' ' << j+1 << endl;
}
void solve(){
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; 
        --u, --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    vector<int> cor(n, -1);
    int tot = -1;
    vector<int> cur;
    auto dfs = [&] (auto&& self, int u) -> void {
        cur.pb(u);
        for (auto v : g[u]) {
            if (cor[v] != -1) continue;
            cor[v] = 1 ^ cor[u];
            self(self, v);
        }
    };
    int c00 = 0, c01 = 0, c11 = 0;
    for (int i = 0; i < n; ++i) {
        if (cor[i] == -1) {
            cur.clear();
            int c1 = 0, c2 = 0;
            cor[i] = 0;
            dfs(dfs, i);
            for (auto x : cur) {
                if (cor[x]) c2++;
                else c1++;
            }
            tot += c1*c2;
            c1 %= 2, c2 %= 2;
            if (c1 != c2) c01++;
            else if (c1 == 0) c00++;
            else c11++;
            tot++;
        }
    }
    tot -= m;
    // 00, 01: par
    // 00, 11: impar
    // 01, 11: par
    // 00, 00: par
    // 01, 01: escolha
    // 11, 11: par
    // 2 problemas independentes: parear 01 com 01, parear 11 com 00
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
