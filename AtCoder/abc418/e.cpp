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

void solve() {
    int n; cin >> n;
    vector<ii> pt(n);
    for (auto& [x, y] : pt) cin >> x >> y;
    vector<ii> a, b;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            auto [x1, y1] = pt[i];
            auto [x2, y2] = pt[j];
            int g = gcd(x1-x2, y1-y2);
            a.pb({(x2-x1)/g, (y2-y1)/g});
            a.pb({(x1-x2)/g, (y1-y2)/g});
            b.pb({x1+x2, y1+y2});
        }
    }
    sort(all(a));
    sort(all(b));
    int ans = 0;
    for (int l = 0, r = 0; l != sz(a); l = r) {
        int y = 0;
        while (r != sz(a) and a[l] == a[r]) y++, r++;
        ans += y * (y-1) / 2;
    }
    ans /= 2;
    for (int l = 0, r = 0; l != sz(b); l = r) {
        int y = 0;
        while (r != sz(b) and b[l] == b[r]) y++, r++;
        ans -= y * (y-1) / 2;
    }
    // N places K coffees
    // coffee in the last spot: (N-K choose K-1)
    // coffee not in the last spot: (N-K choose K)
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
