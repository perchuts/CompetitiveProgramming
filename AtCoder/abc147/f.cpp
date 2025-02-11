#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato
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

int solve(int n, int a0, int d){
    if (a0 == 0) {
        if (d == 0) return 1;
        return n*(n-1)/2+1;
    }
    if (d == 0) return n+1;
    int lcm = a0*d/gcd(a0, d), ans = 1;
    int c1 = lcm/a0, c2 = lcm/d;
    int sgn = (c1 > 0 ? 1 : -1);
    for (int i = 1; i <= n; ++i) {
        int lx = i*(i-1)/2, rx = (2*n-i-1)*i/2;
        int k = i-sgn*c1;
        ans += rx-lx+1;
        if (k >= 0) {
            int lx2 = k*(k-1)/2-sgn*c2, rx2 = (2*n-k-1)*k/2-sgn*c2;
            if (rx2 < lx or rx < lx2) {}
            else if (lx <= lx2) ans -= min(rx, rx2) - lx2 + 1;
            else ans -= min(rx, rx2) - lx + 1;
        }
    }
    return ans;
}
vector<int> gajos;
int brute(int n, int x, int d) {
    vector<int> v(n);
    v[0] = x;
    for (int i = 1; i < n; ++i) v[i] = v[i-1] + d;
    vector<int> b;
    for (int m = 0; m < (1 << n); ++m) {
        int t = 0;
        for (int i = 0; i < n; ++i) {
            if (m >> i & 1) t += v[i];
        }
        b.pb(t);
    }
    sort(all(b));
    b.erase(unique(all(b)), end(b));
    gajos = b;
    return sz(b);
}
int32_t main(){_
#ifndef gato
    int n, x, d; cin >> n >> x >> d;
    cout << solve(n, x, d) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 20), x = rnd(-5, 5), d = rnd(-5, 5);
        int my = solve(n, x, d), br = brute(n, x, d);
        if (my != br) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << x << ' ' << d << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << br;
            cout << " -> ";
            for (auto z : gajos) cout << z << ' '; 
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
