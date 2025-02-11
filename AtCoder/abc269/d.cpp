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
    map<ii, int> exist;
    vector<ii> sexo(n);
    for (auto& [x, y] : sexo) {
        cin >> x >> y;
        exist[{x, y}] = 1;
    }
    map<ii, int> vis;
    int ans = 0;
    auto dfs = [&] (auto&& self, ii par) -> void {
        vis[par] = 1;
        vector<ii> z = {{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};
        auto [xx, yy] = par;
        for (auto [x, y] : z) {
            int x2 = xx + x, y2 = yy + y;
            if (exist[{x2, y2}] == true and !vis[{x2, y2}]) self(self, {x2, y2});
        }
    };
    for (auto a : sexo) {
        if (!vis[a]) ans++, dfs(dfs, a);    
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
