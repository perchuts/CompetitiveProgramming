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
    int n, m, k; cin >> n >> m >> k;
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<set<int>> row(n), col(m);
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) row[i].insert(j), col[j].insert(i); 
    vector<vector<int>> dist(n, vector<int>(m, inf));
    --x1, --y1, --x2, --y2;
    dist[x1][y1] = 0;
    queue<ii> q; q.push({x1, y1});
    row[x1].erase(y1), col[y1].erase(x1);
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        {
            auto it = row[x].lower_bound(y);
            while (true) {
                if (it == end(row[x])) break;
                int w = *it;
                if (grid[x][w] == '@' or w > y + k) break;
                q.push({x, w}), dist[x][w] = 1 + dist[x][y], it = next(it), row[x].erase(w), col[w].erase(x);
            }
        }
        {
            auto it = row[x].lower_bound(y);
            if (it != begin(row[x])) {
                it = prev(it);
                while (true) {
                    int w = *it;
                    if (grid[x][w] == '@' or w < y - k) break;
                    q.push({x, w}), dist[x][w] = 1 + dist[x][y];
                    if (it == begin(row[x])) { row[x].erase(w), col[w].erase(x); break; }
                    else { it = prev(it); row[x].erase(w), col[w].erase(x); }
                }
            }
        }
        {
            auto it = col[y].lower_bound(x);
            while (true) {
                if (it == end(col[y])) break;
                int w = *it;
                if (grid[w][y] == '@' or w > x + k) break;
                q.push({w, y}), dist[w][y] = 1 + dist[x][y], it = next(it), col[y].erase(w), row[w].erase(y);
            }
        }
        {
            auto it = col[y].lower_bound(x);
            if (it != begin(col[y])) {
                it = prev(it);
                while (true) {
                    int w = *it;
                    if (grid[w][y] == '@' or w < x - k) break;
                    q.push({w, y}), dist[w][y] = 1 + dist[x][y];
                    if (it == begin(col[y])) { col[y].erase(w), row[w].erase(y); break; }
                    else { it = prev(it); col[y].erase(w), row[w].erase(y); }
                }
            }
        }
    }
    cout << (dist[x2][y2] < inf ? dist[x2][y2] : -1) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
