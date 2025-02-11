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
    vector<string> v(n);
    for (auto& x : v) cin >> x;
    vector<int> mark(2*maxn), hi(2*maxn), id(n);
    vector<vector<int>> ptr(2*maxn, vector<int>(26));
    int h = 0;
    for (int i = 0; i < n; ++i) {
        int cur = 0;
        for (auto c : v[i]) {
            if (ptr[cur][c-'a'] == 0) ptr[cur][c-'a'] = ++h; 
            cur = ptr[cur][c-'a'];
        }
        mark[cur] = 1, id[i] = cur;
    };
    auto dfs1 = [&] (auto&& self, int u) -> void {
        for (int i = 0; i < 26; ++i) if (ptr[u][i]) hi[ptr[u][i]] = mark[u] + hi[u], self(self, ptr[u][i]);
    };
    auto dfs2 = [&] (auto&& self, int u) -> void {
        for (int i = 0; i < 26; ++i) if (ptr[u][i]) self(self, ptr[u][i]), mark[u] += mark[ptr[u][i]];
    };
    dfs1(dfs1, 0), dfs2(dfs2, 0);
    int sexo = (mod+1)/2;
    for (auto i : id) {
        int ans = hi[i] + 1;
        int resto = n - hi[i] - mark[i];
        cout << (ans + resto * sexo) % mod << endl; 
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
