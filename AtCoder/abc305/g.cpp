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
    int n, m; cin >> n >> m;
    map<string, int> forb;
    for (int i = 0; i < m; ++i) { string x; cin >> x, forb[x] = true; }
    map<string, int> mp;
    queue<string> qq;
    qq.push("");
    while (!qq.empty()) {
        auto sx = qq.front(); qq.pop();
        for (int i = 0; i < sz(sx); ++i) {
            string tx = sx.substr(i, sz(sx) - i);
            forb[sx] |= forb[tx];
        }
        int eu = forb[sx];
        mp[sx] = sz(mp);
        if (sz(sx) == 6) continue;
        sx += 'a';
        forb[sx] |= eu;
        qq.push(sx);
        sx.pop_back();
        sx += 'b';
        forb[sx] |= eu;
        qq.push(sx);
    }
    int N = 127;
    vector<vector<int>> adj(N, vector<int>(N));
    auto go = [] (string s, char c) {
        s += c;
        if (sz(s) == 7) {
            reverse(all(s)); s.pop_back(); reverse(all(s));
        }
        return s;
    };
    for (auto [x, y] : mp) {
        if (forb[x]) continue;
        for (auto c : {'a', 'b'}) {
            auto z = go(x, c);
            if (!forb[z]) adj[y][mp[z]] = 1;
        }
    }
    vector<vector<int>> ans(N, vector<int>(N));
    for (int i = 0; i < N; ++i) ans[i][i] = 1;
    auto mult = [&] (vector<vector<int>> a, vector<vector<int>> b) { 
        vector<vector<int>> c(N, vector<int>(N));
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
        }
        return c;
    };
    while (n) {
        if (n&1) ans = mult(ans, adj);
        adj = mult(adj, adj), n /= 2;
    }
    int tot = 0;
    for (int i = 0; i < N; ++i) tot = (tot + ans[0][i]) % mod;
    cout << tot << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
