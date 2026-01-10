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
    vector<int> d(n+1, 1e18), x(n+1);
    for (int i = 1; i <= n; ++i) cin >> x[i];
    set<ii> s;
    d[0] = 1e18;
    s.insert({0, 0});
    int ans = 1e18;
    for (int i = 1; i <= n; ++i) {
        auto it = s.lower_bound({x[i], -1});
        int opt = 1e18;
        if (it != end(s)) {
            auto [pos, who] = *it;
            ans -= d[who];
            ckmin(d[who], pos - x[i]);
            ckmin(d[i], pos - x[i]);
            ans += d[who];
        }
        if (it != begin(s)) {
            it = prev(it);
            auto [pos, who] = *it;
            ans -= d[who];
            ckmin(d[who], x[i] - pos);
            ckmin(d[i], x[i] - pos);
            ans += d[who];
        }
        ans += d[i];
        s.insert({x[i], i});
        cout << ans << endl;
    }
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
