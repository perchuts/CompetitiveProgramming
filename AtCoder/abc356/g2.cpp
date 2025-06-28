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
    vector<int> a(n), b(n);
    using ld = double;
    int id = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        if (a[i] * b[id] < a[id] * b[i]) id = i;
    }
    vector<int> ord(n); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) {
        return b[x] * a[y] < b[y] * a[x];
    });
    vector<int> hull;
    for (int l = 0, r = 0; l != n; l = r) {
        int choice = l;
        while (r != n and b[ord[l]] * a[ord[r]] == b[ord[r]] * a[ord[l]]) {
            if (a[ord[r]] > a[ord[choice]]) choice = r;
            r++;
        }
        auto compare = [&] (int i, int j, int k) {
            __int128_t x = (a[j] - a[i]);
            __int128_t y = (a[k] - a[i]);
            x = x * __int128_t(b[i]*a[k] - b[k]*a[i]);
            y = y * __int128_t(b[i]*a[j] - b[j]*a[i]);
            return (x <= y);
        };
        int i = ord[choice], t = sz(hull) - 1;
        while (t > 0 and compare(i, hull[t], hull[t-1])) t--, hull.pop_back();
        hull.pb(i);
    }
    vector<pair<ld, ld>> pts;
    int foi = 0;
    for (int i = 0; i < sz(hull)-1; ++i) {
        ld x = (ld)(a[hull[i]] - a[hull[i+1]]) / (-a[hull[i+1]]*b[hull[i]]+b[hull[i+1]]*a[hull[i]]);
        ld y = (x * b[hull[i]] - 1) / a[hull[i]];
        if (foi == 0 and y >= -1e-20) { 
            pts.pb({ld(1)/b[hull[i]], 0});
            foi = 1;
        }
        if (min(x, y) >= 0) pts.pb({x, y});
    }
    if (!foi) pts.pb({ld(1)/b[hull.back()], 0});
    sort(all(pts));
    int q; cin >> q;
    while (q--){
        int c, d; cin >> c >> d;
        if (a[id] * d > c * b[id]) {
            cout << -1 << endl;
            continue;
        }
        auto get = [&] (int i) {
            auto [alpha, beta] = pts[i];
            return alpha * d - beta * c; 
        };
        int l = 0, r = sz(pts)-1;
        while (r-l > 2) {
            int m1 = l + (r-l)/3, m2 = r - (r-l)/3;
            if (get(m1) < get(m2)) l = m1;
            else r = m2;
        }
        ld ans = 0;
        for (int i = l; i <= r; ++i) ckmax(ans, get(i));
        cout << fixed << setprecision(10) << ans << endl;
    }

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
