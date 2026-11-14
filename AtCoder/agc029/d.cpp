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
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> blocked(m), vis(m), reach(m);
    vector<vector<ii>> regions(m);
    for (int i = 0; i < k; ++i) {
        int x, y; cin >> x >> y; --x, --y;
        blocked[y].pb(x);
    }
    for (int i = 0; i < m; ++i) {
        sort(all(blocked[i]));
        int last = -1;
        blocked[i].pb(n);
        for (auto val : blocked[i]) {
            if (last != val-1) regions[i].pb({val-1, last+1});
            last = val;
        }
    }
    for (int i = 0; i < m; ++i) vis[i].resize(sz(regions[i])), reach[i] = vector<int>(sz(regions[i]), inf);
    priority_queue<iii, vector<iii>, greater<>> pq;
    pq.push({0, 0, 0});
    while (!pq.empty()) {
        auto [height, col, idx] = pq.top(); pq.pop();
        if (vis[col][idx]) continue;
        vis[col][idx] = 1;
        if (col == m-1) continue;
        auto [r, l] = regions[col][idx];
        int i = lower_bound(all(regions[col+1]), pair<int, int>(height+1, -1)) - begin(regions[col+1]);
        while (i != sz(regions[col+1]) and regions[col+1][i].second <= r) {
            if (ckmin(reach[col+1][i], max(height+1, regions[col+1][i].second))) pq.push({reach[col+1][i], col+1, i});
            ++i;
        }
    }
    int ans = n;
    for (int i = 0; i < m; ++i) {
        //cout << "column " << i << endl;
        //for (auto [r, l] : regions[i]) cout << l << " " << r << endl;
        for (int j = 0; j < sz(reach[i]); ++j) {
            if (vis[i][j]) ckmin(ans, regions[i][j].first);
        }
    }
    //cout << endl;
    //for (int i = 0; i < m; ++i) {
    //    for (auto x : vis[i]) cout << x << " ";
    //    cout << endl;
    //}
    //cout << endl;
    //for (int i = 0; i < m; ++i) {
    //    for (auto x : reach[i]) cout << x << " ";
    //    cout << endl;
    //}
    cout << ans+1 << endl;
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
