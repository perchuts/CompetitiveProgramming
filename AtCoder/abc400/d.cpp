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
    int n, m, x1, y1, x2, y2; cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    priority_queue<iii, vector<iii>, greater<>> pq;
    vector<vector<int>> dist(n, vector<int>(m, inf));
    cin >> x1 >> y1 >> x2 >> y2;
    --x1, --x2, --y1, --y2;
    dist[x1][y1] = 0;
    pq.push({0, x1, y1});
    int a[] = {0, 0, -1, 1, 1, -1, 0, 0};
    while (!pq.empty()) {
        auto [d, x, y] = pq.top(); pq.pop();
        if (d != dist[x][y]) continue;
        for (int i = 0; i < 4; ++i) {
            int cost = 0;
            for (int go = 1; go < 3; ++go) {
                int xx = x + go*a[i], yy = y + go*a[i+4];
                if (min(xx, yy) < 0 or xx >= n or yy >= m) continue;
                cost |= (grid[xx][yy] == '#');
                if (ckmin(dist[xx][yy], d + cost)) pq.push({d+cost, xx, yy});
            }
        }
    }
    cout << dist[x2][y2] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
