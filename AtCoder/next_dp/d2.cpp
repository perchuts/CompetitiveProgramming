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
    vector<int> vals;
    int cur = n;
    while (cur) vals.pb(cur % 10), cur /= 10;
    reverse(all(vals));
    vector<int> dp_p(10, inf), dp_m(10, inf);
    dp_p[0] = 0;
    dp_m[1] = 1;
    for (auto d : vals) {
        vector<int> ndp_p(20, inf), ndp_m(20, inf);
        ndp_p[d] = dp_p[0];
        ndp_p[10+d] = dp_p[1];
        ndp_m[10-d] = dp_m[1];
        for (int i = 1; i < 20; ++i) {
            ckmin(ndp_p[0], ndp_p[i] + i);
            ckmin(ndp_p[1], ndp_p[i] + i - 1);
            ckmin(ndp_m[1], ndp_p[i] + i + 1);
            ckmin(ndp_m[1], ndp_m[i] + i - 1);
        }
        swap(dp_m, ndp_m);
        swap(dp_p, ndp_p);
    }
    int ans = inf;
    for (int i = 0; i < 10; ++i) ckmin(ans, min(dp_p[i], dp_m[i]) + i);
    cout << ans << endl;

}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
