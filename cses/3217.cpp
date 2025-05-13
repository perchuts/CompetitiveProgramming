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
    vector<int> mv1 = {1, -1}, mv2 = {2, -2};
    vector<vector<int>> dist(n, vector<int>(n, inf));
    queue<ii> q; q.push({0, 0}); dist[0][0] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int __ = 0; __ < 2; ++__) {
            for (auto dx : mv1) {
                for (auto dy : mv2) {
                    int x2 = x + dx, y2 = y + dy;
                    if (min(x2, y2) < 0 or max(x2, y2) >= n or dist[x2][y2] != inf) continue;
                    dist[x2][y2] = dist[x][y] + 1;
                    q.push({x2, y2});
                }
            }
            swap(mv1, mv2);
        }
    }
    for (auto x : dist) {
        for (auto y : x) cout << y << ' ';
        cout << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
