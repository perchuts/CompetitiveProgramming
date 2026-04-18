#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

const int MAX = 3e6 + 10;
// Kosaraju
//
// O(n + m)

int N;
vector<int> g[MAX];
vector<int> gi[MAX]; // grafo invertido
int vis[MAX];
stack<int> S;
int comp[MAX]; // componente conexo de cada vertice

void dfs(int k) {
    vis[k] = 1;
    for (int i = 0; i < (int) g[k].size(); i++)
        if (!vis[g[k][i]]) dfs(g[k][i]);

    S.push(k);
}

void scc(int k, int c) {
    vis[k] = 1;
    comp[k] = c;
    for (int i = 0; i < (int) gi[k].size(); i++)
        if (!vis[gi[k][i]]) scc(gi[k][i], c);
}

void kosaraju() {
    for (int i = 0; i < N; i++) vis[i] = 0;
    for (int i = 0; i < N; i++) if (!vis[i]) dfs(i);

    for (int i = 0; i < N; i++) vis[i] = 0;
    while (S.size()) {
        int u = S.top();
        S.pop();
        if (!vis[u]) scc(u, u);
    }
}
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (auto& x : a) for (auto& y : x) cin >> y;
    vector<ii> ranges;
    vector<vector<ii>> vals(n*m+1);
    for (int i = 0; i < n; ++i) {
        int mn = n*m+1, mx = 0;
        for (int j = 0; j < m; ++j) {
            if (a[i][j]) ckmin(mn, a[i][j]), ckmax(mx, a[i][j]), vals[a[i][j]].pb({i, j});
        }
        if (mx) ranges.pb({mx, mn});
    }
    sort(all(ranges));
    for (int i = 1; i < sz(ranges); ++i) {
        if (ranges[i-1].first > ranges[i].second) {
            cout << "No" << endl;
            exit(0);
        }
    }
    vector<int> ord(m); iota(all(ord), 0);
    N = m;
    for (int i = 0; i < n; ++i) {
        sort(all(ord), [&] (int x, int y) {
            return a[i][x] < a[i][y];
        });
        int prv = -1;
        for (int l = 0, r = 0; r != m; l = r) {
            while (r != m and a[i][ord[l]] == a[i][ord[r]]) r++;
            if (a[i][ord[l]]) {
                for (int k = l; k < r; ++k) {
                    g[N].pb(ord[k]), gi[ord[k]].pb(N);
                }
                if (prv != -1) {
                    for (int k = prv; k < l; ++k) {
                        g[ord[k]].pb(N), gi[N].pb(ord[k]);
                    }
                }
                N++, prv = l;
            }
        }
    }
    kosaraju();
    for (int i = 0; i < m; ++i) if (comp[i] != i) {
        cout << "No" << endl;
        exit(0);
    }
    cout << "Yes" << endl;
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
