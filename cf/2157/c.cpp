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
    int n, k, q; cin >> n >> k >> q;
    vector<array<int, 3>> v(q);
    for (auto& x : v) cin >> x[0] >> x[1] >> x[2], --x[1], --x[2];
    vector<int> bad(n+1), bad2(n+1);
    for (int i = 0; i < q; ++i) {
        if (v[i][0] == 2) {
            bad[v[i][1]]++, bad[v[i][2]+1]--;
        } else {
            bad2[v[i][1]]++, bad2[v[i][2]+1]--;
        }
    }
    vector<int> ans(n, -1);
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        cur += bad[i];
        if (cur == 0) ans[i] = k;
    }
    vector<int> pode(n);
    cur = 0;
    for (int i = 0; i < n; ++i) {
        cur += bad2[i];
        if (cur == 0) pode[i] = 1;
    }
    int turn = 0;
    for (int i = 0; i < n; ++i) {
        if (pode[i] == 1) ans[i] = turn, turn = (turn + 1) % k;
    }
    for (int i = 0; i < n; ++i) {
        if (ans[i] == -1) ans[i] = 1e9;
    }
    for (auto x : ans) cout << x << ' ';
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
