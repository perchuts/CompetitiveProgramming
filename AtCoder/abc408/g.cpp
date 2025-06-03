#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato
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

__int128 gcd(__int128 a, __int128 b) {
    if (a == 0) return b;
    return gcd(b%a, a);
}
__int128 solve(int a, int b, int c, int d) {
    int X = a/b+1;
    int g1 = gcd(a, b), g2 = gcd(c, d);
    a /= g1, b /= g1, c /= g2, d /= g2;
    __int128 sexo = X, sexo2 = d, sexo3 = c;
    if (sexo*sexo2 < sexo3) return 1;
    auto f = [] (auto&& self, __int128 a, __int128 b, __int128 c, __int128 d) -> pair<__int128, __int128> {
        //cout << int(a) << ' ' << int(b) << ' ' << int(c) << ' ' << int(d) << endl;
        if (b == 0) return make_pair(c/d+1, 1);
        if (d == 0) return make_pair(a/b+1, 1);
        __int128 k = a/b, k2 = c/d;
        if (min(k, k2) == 0) {
            if (a > b or c > d) return make_pair(1, 1);
            auto [p, q] = self(self, b, a, d, c);
            return make_pair(q, p);
        }
        auto [p, q] = self(self, a-min(k, k2)*b, b, c-min(k, k2)*d, d);
        p += q*min(k, k2);
        return make_pair(p, q);
    };
    auto [p, q] = f(f, a, b, c, d);
    return q;
}
int32_t main(){_
    auto print = [] (__int128 k) {
        vector<int> ans;
        while (k) ans.pb(k%10), k /= 10;
        reverse(all(ans));
        for (auto x : ans) cout << x;
        cout << endl;
    };
#ifndef gato
    int t; cin >> t;
    while (t--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        print(solve(a, b, c, d));
    }
#else
    while (true) {
        int a = rnd(1, 1e18);
        int b = rnd(1, 1e18);
        int c = rnd(1, 1e18);
        int d = rnd(1, 1e18);
        cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
        cout.flush();
        print(solve(a, b, c, d));
        cout.flush();
    }
#endif
}
