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
    int n, m; cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (auto& x : grid) for (auto& y : x) cin >> y;
    int q; cin >> q;
    vector<array<int, 7>> qu(q);
    vector<vector<vector<int>>> queries(n, vector<vector<int>>(m));
    vector<int> ans(q);
    for (int i = 0; i < q; ++i) {
        cin >> qu[i][0] >> qu[i][1] >> qu[i][2] >> qu[i][3] >> qu[i][4] >> qu[i][5], qu[i][6] = i;
        qu[i][0]--, qu[i][1]--;
        qu[i][3]--, qu[i][4]--;
        queries[qu[i][0]][qu[i][1]].pb(i);
        queries[qu[i][3]][qu[i][4]].pb(i);
        if (qu[i][0] == qu[i][3] and qu[i][1] == qu[i][4]) ans[i] = abs(qu[i][2] - qu[i][5]);
    }
    vector<vector<set<ii>>> comp(n, vector<set<ii>>(m));
    vector<vector<ii>> par(n, vector<ii>(m));
    vector<vector<int>> lvl(n, vector<int>(m));
    vector<vector<ii>> heights(4*maxn);
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        heights[grid[i][j]].pb({i, j});
        par[i][j] = {i, j};
        comp[i][j].insert({i, j});
    }
    auto findp = [&] (auto&& self, int i, int j) -> pair<int, int> {
        return par[i][j] = (par[i][j] == make_pair(i, j) ? par[i][j] : self(self, par[i][j].first, par[i][j].second));
    };
    auto unite = [&] (int x1, int y1, int x2, int y2, int H) {
        auto p1 = findp(findp, x1, y1);
        auto p2 = findp(findp, x2, y2);
        if (p1 == p2) return;
        if (lvl[p1.first][p1.second] < lvl[p2.first][p2.second]) swap(p1, p2);
        x1 = p1.first, y1 = p1.second;
        x2 = p2.first, y2 = p2.second;
        par[x2][y2] = {x1, y1};
        for (auto [x, y] : comp[x2][y2]) {
            for (auto id : queries[x][y]) {
                int x2 = qu[id][0], y2 = qu[id][1];
                if (x2 == x and y2 == y) x2 = qu[id][3], y2 = qu[id][4];
                if (comp[x1][y1].find(pair(x2, y2)) != end(comp[x1][y1]) and ans[id] == 0) {
                    if (H >= min(qu[id][2], qu[id][5])) ans[id] = abs(qu[id][2] - qu[id][5]);
                    else ans[id] = abs(qu[id][2]-H) + abs(qu[id][5]-H);
                }
                comp[x1][y1].insert(pair(x, y));
            }
        }
        if (lvl[x1][y1] == lvl[x2][y2]) lvl[x1][y1]++;
    };
    int a[] = {1, -1, 0, 0, 0, 0, 1, -1};
    for (int h = 4*maxn-1; h; --h) {
        for (auto [x, y] : heights[h]) {
            for (int i = 0; i < 4; ++i) {
                int x2 = x + a[i], y2 = y + a[i+4];
                if (min(x2, y2) < 0 or x2 >= n or y2 >= m or grid[x2][y2] < h) continue;
                unite(x, y, x2, y2, h);
            }
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
