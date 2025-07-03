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
    int n, a; cin >> n >> a;
    vector<int> w(n), x(n), v(n);
    for (int i = 0; i < n; ++i) cin >> w[i] >> x[i] >> v[i];
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        vector<iii> times;
        int tot = 0;
        for (int j = 0; j < n; ++j) {
            int d1 = v[j] - v[i];
            if (x[i] <= x[j] and x[j] <= x[i]+a) times.pb({0, 1, w[j]});
            if (d1 > 0) {
                if (x[j] < x[i]) times.pb({x[i]-x[j], d1, w[j]});
                if (x[j] <= x[i] + a) times.pb({x[i]+a-x[j], d1, -w[j]});
            } else if (d1 < 0) {
                if (x[i] + a < x[j]) times.pb({x[j]-x[i]-a, -d1, w[j]});
                if (x[i] <= x[j]) times.pb({x[j]-x[i], -d1, -w[j]});
            }
        }
        sort(all(times), [&] (iii a, iii b) {
            auto [x1, y1, z1] = a;
            auto [x2, y2, z2] = b;
            if (x1*y2 == x2*y1) return z1 > z2;
            return x1*y2 < x2*y1;
        });
        for (auto [a, b, c] : times) {
            tot += c;
            ckmax(ans, tot);
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
