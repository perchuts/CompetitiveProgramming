#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
    int n, x; cin >> n >> x;
    // define ans[0][i], ans[i][0]
    // ans[i][j] = ans[0][0] ^ ans[i][0] ^ ans[0][j] if i or j even
    // otherwise ans[i][j] = ans[0][0] ^ ans[i][0] ^ ans[0][j] ^ x
    // ans[0][0] ^ ans[0][j] = x
    // ans[i] = ans[i] ^ ans[j] ^ ans[0] ^ x
    // x = ans[j] ^ ans[0]
    // a[i] ^ a[j] ^ a[0] = a[i] ^ a[k] ^ a[0] ^ x
    if (n == 2) {
        cout << (x ? "-1" : "0 1\n1 0") << endl;
        return;
    }
    if (__builtin_popcount(n) != 1) {
        cout << -1 << endl;
        return;
    }
    vector<int> mark(n, -1), a, b;
    for (int i = 0; i < n; ++i) {
        if (mark[i] == -1) {
            a.pb(i), b.pb(i ^ max(1, x));
            mark[i] = mark[i ^ max(1, x)] = 1;
        }
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        ans.pb(a.back()), a.pop_back();
        ans.pb(a.back()), a.pop_back();
        swap(a, b);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0) cout << ans[j] << " ";
            else if (j == 0) cout << ans[i] << " ";
            else if (i % 2 == 0 or j % 2 == 0) cout << (ans[i] ^ ans[j] ^ ans[0]) << " ";
            else cout << (ans[i] ^ ans[j] ^ ans[0] ^ x) << " ";
        }
        cout << endl;
    }
    cout << endl;
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
