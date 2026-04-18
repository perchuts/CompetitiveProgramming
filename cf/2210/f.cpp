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
const int maxn = 1e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int z[maxn][22], zid[maxn], jump[maxn][22];

void solve() {
    int n, q; cin >> n >> q;
    for (int i = 0; i <= n; ++i) zid[i] = 0;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
    vector<int> dir(n+1);
    vector<ii> penis = {{-1, n}};
    dir[n] = n;
    for (int i = n-1; ~i; --i) {
        while (penis.back().first > p[i]) penis.pop_back();
        dir[i] = penis.back().second;
        penis.pb({p[i], i});
    }
    vector<int> acum(n+1);
    for (int i = n-1; ~i; --i) acum[i] = (dir[i] - i) * (dir[i] - i - 1) / 2 + acum[dir[i]];
    vector<vector<int>> t(n+1);
    int help = 0;
    vector<int> stk(n+10);
    auto dfs = [&] (auto&& self, int u) -> void {
        stk[help++] = u;
        int cur = help-1;
        int tot = dir[u] - u;
        while (cur > 1) {
            int want = u + 2 * tot + 1;
            int l = 0, r = cur-1, opt = -1;
            while (l <= r) { 
                int md = l + (r-l+1)/2;
                if (stk[md] >= want) l = md+1, opt = md;
                else r = md-1;
            }
            cur = opt+1;
            if (opt == -1) break;
            if (stk[cur-1] - stk[cur] <= tot) break;
            z[u][zid[u]++] = stk[cur];
            tot = stk[cur-1] - u;
        }
        for (auto v : t[u]) self(self, v);
        help--;
    };
    for (int i = 0; i < n; ++i) t[dir[i]].pb(i);
    dfs(dfs, n);
    for (int j = 0; j < 20; ++j) jump[n][j] = n;

    for (int i = n-1; ~i; --i) {
        jump[i][0] = dir[i];
        for (int j = 1; j < 20; ++j) {
            jump[i][j] = jump[jump[i][j-1]][j-1];
        }
    }
    while (q--) {
        int l, r; cin >> l >> r; --l, --r;
        int tam = r-l+1;
        if (dir[l] > r) {
            cout << (tam/2)*((tam+1)/2)-(tam/2) << endl;
            continue;
        }
        int cur = l;
        for (int i = 19; ~i; --i) {
            if (dir[jump[cur][i]] <= r+1) cur = jump[cur][i];
        }
        int sobra = r+1-dir[cur];
        int ans = tam*(tam-1)/2 - acum[l] + acum[dir[cur]] - sobra*(sobra-1)/2;
        cout << ans << " ";
        for (int i = 0; i < zid[l]; ++i) {
            int pos = z[l][i];
            int j = (l+dir[pos])/2;
            assert(pos <= j and j < dir[pos]);
            int score = (j-l)*(r+1-j) - acum[dir[pos]] + acum[dir[cur]] - sobra*(sobra-1)/2 - (dir[pos]-j)*(dir[pos]-j-1)/2;
            //
            ckmax(ans, score);
        }
        cout << ans << endl;
    }
    // [l, r], decided to pick k mins
    // k*n - k*(k+1)/2
    // k*(n-(k+1)/2) - how many pairs amongst last k of mins are equal!
    // k*(n-k) + (k*(k-1)/2) - chooses of mins
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
