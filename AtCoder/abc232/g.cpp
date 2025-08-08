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

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    vector<vector<ii>> g(2*n);
    vector<int> ord_out(n); iota(all(ord_out), 0);
    sort(all(ord_out), [&] (int i, int j) { return b[i] < b[j]; });
    for (int j = 0; j < n-1; ++j) g[n+ord_out[j]].pb({n+ord_out[j+1], b[ord_out[j+1]] - b[ord_out[j]]});
    for (int j = 0; j < n; ++j) {
        g[n+j].pb({j, 0});
        g[j].pb({n+ord_out[0], a[j]+b[ord_out[0]]});
        int l = 0, r = n-1, opt = -1;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (a[j] + b[ord_out[md]] >= m) opt = md, r = md-1;
            else l = md+1;
        }
        if (opt != -1) g[j].pb({n+ord_out[opt], a[j] + b[ord_out[opt]] - m});
    }
    vector<int> dist(2*n, inf);
    dist[0] = 0;
    priority_queue<ii, vector<ii>, greater<>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        for (auto [v, w] : g[u]) {
            if (ckmin(dist[v], d + w)) pq.push({dist[v], v});
        }
    }
    cout << dist[n-1] << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
