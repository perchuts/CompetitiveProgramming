#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

void solve() {
//    state = seed
//
//for i=2 to N:
//  if i <= M:
//    p[i] = q[i]
//  else:
//    p[i] = (state mod (i-1)) + 1
//    state = (state * 1103515245 + 12345) mod 2^31
//
//for i=1 to N:
//  if i <= M:
//    c[i] = d[i]
//  else:
//    c[i] = (state mod F) + 1
//    state = (state * 1103515245 + 12345) mod 2^31
    int n, seed, m, f;
    cin >> n >> seed >> m >> f;
    vector<int> q(m+1), d(m+1);
    for (int i = 2; i <= m; ++i) cin >> q[i];
    for (int i = 1; i <= m; ++i) cin >> d[i];
    int state = seed;
    vector<int> p(n+1), c(n+1);
    p[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (i <= m) p[i] = q[i];
        else p[i] = (state % (i-1)) + 1, state = (state * 1103515245 + 12345) % (1LL << 31);
    }
    for (int i = 1; i <= n; ++i) {
        if (i <= m) c[i] = d[i];
        else c[i] = (state % f) + 1, state = (state * 1103515245 + 12345) % (1LL << 31);
    }
    //for (int i = 1; i <= n; ++i) cout << p[i] << " \n"[i==n];
    //for (int i = 1; i <= n; ++i) cout << c[i] << " \n"[i==n];
    vector<int> M(n+1), K(n+1);
    vector<int> lx(n+1), rx(n+1), subt(n+1, 1), quem(2*n);
    int T = 0;
    vector<vector<int>> g(n+1);
    for (int i = 2; i <= n; ++i) g[p[i]].pb(i);
    auto dfs = [&] (auto&& self, int u) -> void {
        lx[u] = ++T;
        quem[lx[u]] = u;
        for (auto v : g[u]) self(self, v), subt[u] += subt[v];
        rx[u] = T;
    };
    dfs(dfs, 1);
    vector<int> cnt_color(n+1), cnt_freq(n+1);
    int cur_ans = 0;
    auto rem = [&] (int u) {
        //cout << "rem " << u << endl;
        cnt_freq[cnt_color[c[u]]]--;
        if (cur_ans == cnt_color[c[u]] and cnt_freq[cur_ans] == 0) cur_ans--;
        cnt_color[c[u]]--;
        cnt_freq[cnt_color[c[u]]]++;
    };
    auto add = [&] (int u) {
        //cout << "add " << u << endl;
        cnt_freq[cnt_color[c[u]]]--;
        if (cur_ans == cnt_color[c[u]]) cur_ans++;
        cnt_color[c[u]]++;
        cnt_freq[cnt_color[c[u]]]++;
    };
    auto solve = [&] (auto&& self, int u) -> void {
        //cout << "na subt: " << u << endl;
        M[u] = cur_ans, K[u] = cnt_freq[cur_ans];
        if (g[u].empty()) {
            rem(u);
            return;
        }
        sort(all(g[u]), [&] (int x, int y) { return subt[x] > subt[y]; });
        int big = g[u][0];
        int L = lx[big], R = rx[big];
        for (int i = lx[u]; i < L; ++i) rem(quem[i]);
        for (int i = R+1; i <= rx[u]; ++i) rem(quem[i]);
        self(self, big);
        for (int i = 1; i < sz(g[u]); ++i) {
            for (int j = lx[g[u][i]]; j <= rx[g[u][i]]; ++j) add(quem[j]);
            self(self, g[u][i]);
        }
    };
    for (int i = 1; i <= n; ++i) add(i);
    solve(solve, 1);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = (ans + (M[i]^i) * (K[i]^i)) % mod;
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
