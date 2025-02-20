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
    int n, k; cin >> n >> k;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
    vector<ii> pts;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) pts.pb({x[i], y[j]});
    int ans = 9e18;
    for (int i = 0; i < sz(pts); ++i) for (int j = i+1; j < sz(pts); ++j) {
        auto [x1, y1] = pts[i];
        auto [x2, y2] = pts[j];
        if (x1 == x2 or y1 == y2) continue;
        int cur = 0;
        for (int w = 0; w < n; ++w) {
            if (min(x1, x2) <= x[w] and x[w] <= max(x1, x2) and min(y1, y2) <= y[w] and y[w] <= max(y1, y2)) cur++;
        }
        if (cur >= k) {
            ckmin(ans, (max(x1, x2) - min(x1, x2)) * (max(y1, y2) - min(y1, y2)));

        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
