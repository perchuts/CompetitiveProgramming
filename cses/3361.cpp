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
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    for (int i = 1; i < n; ++i) a[i] += a[i-1], b[i] += b[i-1];
    auto check = [&] (double k) {
        int xx = 0, yy = 0;
        double ba = (double)a[0]-k, bb = (double)b[0]-k;
        for (int i = 1; i < n; ++i) {
            if (ckmax(ba, a[i] - (i+1)*k)) xx = i;
            if (ckmax(bb, b[i] - (i+1)*k)) yy = i;
        }
        return pair(xx, yy);
    };
    double l = 1, r = 1e9;
    for (int i = 0; i < 50; ++i) {
        double md = (l+r)/2;
        auto [x, y] = check(md);
        double med = (a[x] + b[y]) / (double)(x+y+2);
        if (med >= md-1e-8) l = md;
        else r = md;
    }
    auto [x, y] = check(l);
    cout << x + 1 << ' ' << y + 1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
