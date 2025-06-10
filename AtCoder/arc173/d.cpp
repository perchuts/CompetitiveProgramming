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
    vector<iii> edg(m);
    for (auto& [x, y, z] : edg) {
        char c; cin >> x >> y >> c;
        z = (c == ')' ? -1 : 1);
        --x, --y;
    }
    vector<int> cyc(2);
    for (int j = 0; j < 2; ++j) {
        vector<int> dist(n, inf);
        dist[0] = 0;
        for (int t = 0; t < n; ++t) {
            bool ok = 0;
            for (auto [u, v, w] : edg) ok |= ckmin(dist[v], dist[u] + w);
            cyc[j] = (t == n-1 and ok);
        }
        for (auto& [u, v, w] : edg) w *= -1;
    }
    cout << (cyc[0] ^ cyc[1] ? "No" : "Yes") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

