#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    int n, m; cin >> n >> m;
    vector<int> a(n), b(n+1);
    for (auto& x : a) cin >> x;
    if (n == 1) {
        cout << 0 << endl; 
        return;
    }
    b[0] = a[0];
    for (int i = 1; i < n; ++i) b[i] = (m + a[i] - a[i-1]) % m;
    b[n] = (m-a[n-1])%m;
    vector<int> vals;
    if (n & 1) {
        for (int i = 1; i <= n/2; ++i) vals.pb((b[i] + b[n-i])%m);
    } else {
        for (int i = 1; i < n/2; ++i) vals.pb((b[i] + b[n-i])%m);
        vals.pb(b[n/2]);
    }
    sort(all(vals));
    int S = 0;
    for (auto x : vals) S += x;
    int ans = (m*sz(vals) - S);
    int ps = 0;
    for (int i = 0; i < sz(vals); ++i) {
        ps += vals[i];
        ckmin(ans, max(ps, (m*(sz(vals)-i-1) - (S-ps))));
    }
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
