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
    int S = 0;
    vector<int> a(n);
    for (auto& x : a) cin >> x, S += x;
    int r = (n+1)*n/2;
    if (S % r) {
        cout << "NO" << endl;
        return;
    }
    if (n == 1) {
        cout << "YES" << endl;
        return;
    }
    vector<int> ops(n);
    for (int i = 0; i < n; ++i) {
        int val = (a[(i+1)%n] - a[i]) % (n-1);
        val = (S/r - val) % (n-1);
        val = (val + (n-1)) % (n-1);
        ops[(i+1)%n] = val;
    }
    int tot = 0, ts = 0;
    for (int i = 0; i < n; ++i) {
        tot += ops[i];
        ts += tot;
        a[i] -= ts;
    }
    tot = ts = 0;
    for (int i = n-1; ~i; --i) {
        ts -= tot;
        a[i] -= ts;
        ts += (n+1) * ops[i];
        tot += ops[i];
    }
    for (int i = 0; i < n-1; ++i) {
        if (a[i] < 0) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;

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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
