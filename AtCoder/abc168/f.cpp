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

bool pode[5000][5000][4];

void solve(){
    int n, m; cin >> n >> m;
    vector<int> vr = {0, inf, -inf}, vc = {0, inf, -inf};
    vector<iii> a, b;
    for (int i = 0; i < n; ++i) {
        int x, y, z; cin >> x >> y >> z;
        x *= -1, y *= -1;
        vr.pb(x), vr.pb(y);
        vc.pb(z), vc.pb(z-1);
        a.pb({y, x, z});
    }
    for (int i = 0; i < m; ++i) {
        int x, y, z; cin >> x >> y >> z;
        x *= -1;
        vc.pb(y), vc.pb(z);
        vr.pb(x), vr.pb(x-1);
        b.pb({x, y, z});
    }
    sort(all(vc)), sort(all(vr)); vc.erase(unique(all(vc)), end(vc)), vr.erase(unique(all(vr)), end(vr));
    auto get_coord = [&] (int x, int y) { return pair{lower_bound(all(vr), x) - begin(vr), lower_bound(all(vc), y) - begin(vc)}; };
    int N = sz(vr), M = sz(vc);
    vector<vector<bool>> vis(N, vector<bool>(M));
    vector adj = {1, -1, 0, 0, 0, 0, 1, -1};
    for (auto [x, y, z] : a) {
        auto [lx, c] = get_coord(x, z);
        auto [rx, cc] = get_coord(y, z);
        for (int i = lx; i < rx; ++i) {
            pode[i][c][3] = pode[i][c-1][2] = true;
        }
    }
    for (auto [x, y, z] : b) {
        auto [cc, lx] = get_coord(x, y);
        auto [c, rx] = get_coord(x, z);
        for (int i = lx; i < rx; ++i) {
            pode[c][i][1] = pode[c-1][i][0] = true;
        }
    }
    auto [inx, iny] = get_coord(0, 0);
    queue<ii> q; q.push({inx, iny}), vis[inx][iny] = true;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (min(x, y) == 0 or x == N-1 or y == M-1) {
             cout << "INF" << endl;
             exit(0);
        }
        for (int i = 0; i < 4; ++i) {
            if (pode[x][y][i]) continue;
            int x2 = x + adj[i], y2 = y + adj[i+4];
            if (!vis[x2][y2]) vis[x2][y2] = true, q.push({x2, y2});
        }
    }
    ll ans = 0;
    for (int i = 1; i < N-1; ++i) for (int j = 1; j < M-1; ++j) {
        if (vis[i][j]) {
            int dx = vr[i+1] - vr[i], dy = vc[j+1] - vc[j];
            ans += ll(dx) * ll(dy);
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
