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
    int g0, ra, rb, q; cin >> q >> g0 >> ra >> rb;
    const int M = (1LL<<31)-1;
    const int c = 48271LL * 48271LL * 48271LL % M;
    const int M1 = 2 * ra + 1;
    const int M2 = 2 * rb + 1;
    int x1 = g0 * 48271LL % M, x2 = x1 * 48271LL % M, x3 = x2 * 48271LL % M;
    int ans = 0;
    for (int j = 1; j <= q; ++j) {
        int a = -ra + (x1 % M1);
        int b = -rb + (x2 * M + x3) % M2;
        for (auto [x, y] : pt) {
            if (y >= a * x + b) ans++;
        }
        x1 = x1 * c % M, x2 = x2 * c % M, x3 = x3 * c % M;
    }
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

