#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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
vector<int> a;
int mx;
ii solve(int n) {
    int qq = 0;
    auto ask = [&] (int tipo, int x) {
        qq++;
        assert(qq <= 60);
        if (tipo == 0) {
#ifndef gato
            cout << "? " << x+1 << endl;
            int ret; cin >> ret;
            return ret;
#else
            return a[x];
#endif
        } else {
#ifndef gato
            if (x > 1e9) return 0LL;
            cout << "> " << x << endl;
            int ret; cin >> ret;
            return ret;
#else
            return int(mx > x);
#endif
        }
    };
    vector<int> vals;
    for (int i = 0; i < 39; ++i) {
        int id = rnd(0, n-1);
        vals.pb(ask(0, id));
    }
    sort(all(vals)); vals.erase(unique(all(vals)), end(vals));
    int g = 0;
    for (int i = 0; i < sz(vals); ++i) {
        for (int j = i + 1; j < sz(vals); ++j) {
            g = gcd(g, vals[j] - vals[i]);
        }
    }
    int mxx = vals.back(), d = g;
    int l = 0, r = n-1;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (ask(1, vals.back() + md * d)) mxx = vals.back() + md * d + d, l = md+1;
        else r = md-1;
    }
    return {mxx - (n-1) * d, d};
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n; cin >> n;
    auto [x1, d] = solve(n);
    cout << "! " << x1 << ' ' << d << endl;
#else
    int t = 1;
    while (true) {
        int n = 1000000;
        a.resize(n);
        int d = rnd(1, 1e3);
        int x1 = rnd(0, 1e5);
        mx = (n-1)*d + x1;
        for (int i = 0; i < n; ++i) a[i] = x1 + i * d;
        shuffle(all(a), rng);
        auto [z1, z2] = solve(n);
        if (z1 != x1 or z2 != d) {
            cout << "Wrong answer on test " << t << endl;
            cout << "x1 = " << x1 << " d = " << d << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << z1 << ' ' << z2 << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
