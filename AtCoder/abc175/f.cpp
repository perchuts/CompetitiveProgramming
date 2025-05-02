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
    vector<string> v(n);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) cin >> v[i] >> c[i];
    for (int i = 0; i < n; ++i) {
        string ss = v[i]; reverse(all(ss));
        v.pb(ss); c.pb(c[i]);
    }
    n *= 2;
    vector<vector<vector<iii>>> g(n);
    vector<vector<int>> win(n);
    for (int i = 0; i < n; ++i) {
        int m = sz(v[i]);
        g[i].resize(m+1), win[i].resize(m+1);
        for (int j = 0; j <= m; ++j) {
            win[i][j] = true;
            for (int k = j; k < m; ++k) win[i][j] &= (v[i][k] == v[i][m-1-(k-j)]);
            int ini = (i < n/2 ? n/2 : 0);
            for (int k = ini; k < ini+n/2; ++k) {
                int pt1 = j, pt2 = 0, ok = true;
                while (pt1 < m and pt2 < sz(v[k])) ok &= (v[i][pt1++] == v[k][pt2++]);
                if (ok) {
                    if (pt1 == m) g[i][j].pb({k, pt2, c[k]});
                    else g[i][j].pb({i, pt1, c[k]});
                }
            }
        }
    }
    vector<vector<int>> dist(n);
    priority_queue<iii, vector<iii>, greater<>> pq;
    for (int i = 0; i < n; ++i) {
        int m = sz(v[i]);
        dist[i].resize(m+1);
        for (int j = 0; j <= m; ++j) dist[i][j] = 1e18;
        if (i < n/2) pq.push({c[i], i, 0}), dist[i][0] = c[i];
    }
    while (!pq.empty()) {
        auto [d, i, j] = pq.top(); pq.pop();
        if (dist[i][j] != d) continue;
        for (auto [i2, j2, w] : g[i][j]) {
            if (ckmin(dist[i2][j2], d+w)) pq.push({d+w, i2, j2});
        }
    }
    int ans = 1e18;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= sz(v[i]); ++j) if (win[i][j]) ckmin(ans, dist[i][j]);
    }
    cout << (ans == 1e18 ? -1 : ans) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
