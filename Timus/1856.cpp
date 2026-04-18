#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

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

bool brute(int n, vector<int> p, vector<int> q) {
    vector<vector<int>> adj(1<<n);
    vector<int> deg(1<<n);
    vector<bool> win(1<<n), lose(1<<n);
    for (int i = 1; i < (1<<n); ++i) {
        int pm = 0, qm = 0;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) pm |= (1 << p[j]), qm |= (1 << q[j]);
        }
        adj[pm].pb(i), deg[i]++;
        if (pm != qm) adj[qm].pb(i), deg[i]++;
		if (i == pm or i == qm) lose[i] = 1;
    }
    queue<int> qq;
    for (int i = 0; i < n; ++i) qq.push(1<<i), win[i] = 1;
    vector<int> vence(1<<n);
    while (!qq.empty()) {
        int u = qq.front(); qq.pop();
        for (auto v : adj[u]) {
            vence[v]++;
            if (vence[v] == deg[v]) {
                for (auto w : adj[v]) if (!win[w] and !lose[w]) {
                    win[w] = 1;
                    qq.push(w);
                }
            }
        }
    }
	for (int i = 0; i < (1<<n); ++i) {
		cout << bitset<4>(i) << " " << win[i] << endl;
	}
    return win.back()^1;
}

bool vis[1000000];
vector<int> adj[1000000];
int deg[1000000];

bool solve(int n, vector<int> p, vector<int> q) {
    auto get = [&] (int i, int j) { 
        if (i > j) swap(i, j);
        return 1000*i+j;
    };
    queue<int> qq;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int eu = get(i, j);
            int a = get(p[i], p[j]), b = get(q[i], q[j]);
            adj[a].pb(eu), deg[eu]++;
            if (a != b) adj[b].pb(eu), deg[eu]++;
            if (i == j) qq.push(eu), vis[eu] = 1;
        }
    }
    int cnt = 0;
    while (!qq.empty()) {
        int u = qq.front(); qq.pop();
        cnt++;
        for (auto v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                for (auto w : adj[v]) {
                    if (!vis[w]) vis[w] = 1, qq.push(w);
                }
            }
        }
    }
    return (cnt < n*(n+1)/2);
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> p(n), q(n);
    for (int i = 0; i < n; ++i) cin >> p[i] >> q[i], --p[i], --q[i];
    cout << (solve(n, p, q) ? "Peace" : "War") << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 5);
        vector<int> p(n), q(n); 
        for (int i = 0; i < n; ++i) p[i] = rnd(0, n-1), q[i] = rnd(0, n-1);
        bool my = solve(n, p, q);
        bool ans = brute(n, p, q);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (int i = 0; i < n; ++i) cout << p[i]+1 << " " << q[i]+1 << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
