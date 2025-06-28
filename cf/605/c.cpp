#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define double long double

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
    int n, p, q; cin >> n >> p >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    double l = 0, r = max(p, q);
    for (int tries = 0; tries < 100; ++tries) {
        double md = (l+r)/2;
        bool ok = 1;
        double mn = 0, mx = md/q;
        for (int i = 0; i < n; ++i) {
            double x = (double)p - md * a[i];
            int y = b[i] * p - q * a[i];
            //cout << x << ' ' << y << endl;
            if (y == 0) ok &= (x > -1e-15);
            else if (y > 0) ckmin(mx, x/y);
            else ckmax(mn, x/y);
        }
        //cout << endl;
        if (-1e-15 < mn and mx-mn > -1e-15 and ok) l = md;
        else r = md;
    }
    cout << fixed << setprecision(6) << l << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
