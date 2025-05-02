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
    set<ii> caras; multiset<int> dists;
    for (int i = 1; i <= m; ++i) caras.insert({i, 0}), dists.insert(0);
    for (int i = 1; i <= n; ++i) {
        int l, r; cin >> l >> r;
        int ncost = inf;
        while (true) {
            auto it = caras.lower_bound({l, 0});
            if (it == end(caras)) break;
            auto [pos, cost] = *it;
            if (r+1 < pos) break;
            caras.erase({pos, cost});
            dists.erase(dists.find(cost));
            ckmin(ncost, cost + (r+1-pos));
        }

        if (ncost < inf and r != m) dists.insert(ncost), caras.insert({r+1, ncost});
        if (caras.empty()) cout << -1 << endl;
        else cout << (*begin(dists)) + i << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
