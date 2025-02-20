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
    vector<vector<int>> dist(n, vector<int>(n));
    for (auto& x : dist) for (auto& y : x) cin >> y;
    vector<iii> caras;
    for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) caras.pb({dist[i][j], i, j});
    sort(all(caras));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) {
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
            cout << -1 << endl;
            exit(0);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
        bool ok = 1;
        for (int k = 0; k < n; ++k) {
            if (k == i or k == j) continue;
            ok &= (dist[i][k] + dist[k][j] > dist[i][j]);
        }
        if (ok) ans += dist[i][j];
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
