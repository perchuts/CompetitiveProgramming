#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

map<ii, int> grid;

int cnt_queries = 0;

int get(int x, int y) {
    if (grid.count({x, y})) return grid[{x, y}];
    cnt_queries++;
#ifdef gato
    grid[{x, y}] = rnd(0, 1);
#else
    cout << "? " << x << " " << y << endl;
    char c; cin >> c;
    grid[{x, y}] = (c == 'B');
#endif
    return grid[{x, y}];
}

vector<ii> solve(int n) {
    grid.clear();
    // good cells!
    map<ii, int> cover, foi;
    vector<int> adj = {-1, 0, 1};
    vector<set<ii>> q(4);
    vector<int> cnt(2);
    vector<vector<ii>> bichos(2);
    auto add = [&] (int x, int y) {
        int cor = get(x, y);
        cnt[cor]++;
        bichos[cor].pb({x, y});
        for (int i = 1; i < 4; ++i) {
            if ((i & cover[{x, y}]) == i) q[i].erase({x, y});
            else assert(q[i].find({x, y}) == end(q[i]));
        }
        foi[{x, y}] = 1;
        for (auto i : adj) {
            for (auto j : adj) {
                int x2 = x + i, y2 = y + j;
                if (foi[{x2, y2}]) continue;
                cover[{x2, y2}] |= (1 << cor);
                q[cover[{x2, y2}]].insert({x2, y2});
            }
        }
        return cor;
    };
    int p0 = add(0, 0);
    for (int i = 1; i < n; ++i) {
        int x = add(i, 0);
        if (x != p0) break;
    }
    while (true) {
        while (max(cnt[0], cnt[1]) < n and !q[3].empty()) {
            auto [x, y] = *begin(q[3]);
            add(x, y);
        }
        if (max(cnt[0], cnt[1]) == n) break;
        int target;
        if (cnt[0] < cnt[1]) {
            bichos[0].clear();
            q[1].clear();
            cnt[0] = 0;
            target = 0;
        } else {
            bichos[1].clear();
            q[2].clear();
            cnt[1] = 0;
            target = 1;
        }
        while (true) {
			assert(!q[2-target].empty());
            auto [x, y] = *begin(q[2-target]);
            if (add(x, y) == target) break;
        }
    }
    if (cnt[0] == n) return bichos[0];
    return bichos[1];
}

int32_t main() {_
#ifndef gato
    string z = "WB";
    int t, n; cin >> t >> n;
    for (int i = 0; i < t; ++i) {
        auto ans = solve(n);
        cout << "! " << z[get(ans[0].first, ans[0].second)] << " ";
        for (auto [x, y] : ans) cout << x << " " << y << " ";
        cout << endl;
    }
#else
    int n = 300;
    for (int i = 0; ; ++i) {
        int cur = cnt_queries;
        grid.clear();
        auto ans = solve(n);
        map<ii, int> foi;
        if (sz(ans) != n) {
            cout << "Wrong answer on test " << i << ": " << " wrong size" << endl;
            exit(0);
        }
        bool ok = 1;
        for (auto [x, y] : ans) {
            assert(grid.count({x, y}));
            if (foi[{x, y}] == 1) {
                cout << "Wrong answer on test " << i << ": " << " repeated position" << endl;
                exit(0);
            }
            foi[{x, y}] = 1;
            ok &= (get(x, y) == get(ans[0].first, ans[0].second));
        }
        if (ok == 0) {
            cout << "Wrong answer on test " << i << ": " << " invalid component" << endl;
            exit(0);
        }
        cout << "Accepted on test " << i << ": used " << cnt_queries - cur << " queries" << endl;
    }
    cout << "used " << cnt_queries << " queries" << endl;
#endif
}
