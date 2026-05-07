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
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x, --x, x %= 2;
    vector<vector<int>> v(2);
    for (int i = 0; i < n; ++i) v[i%2].pb(a[i]);
    sort(all(v[0]));
    sort(all(v[1]));
    vector<int> foi(2);
    for (auto x : b) {
        if (!foi[x]) {
            foi[x] = 1;
            v[x].pop_back();
        } else if (!v[x].empty() and v[x].back() > 0) v[x].pop_back();
    }
    int S = 0;
    for (auto x : v) for (auto y : x) S += y;
    cout << S << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1;cin >> t;
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
