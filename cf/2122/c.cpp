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
    vector<int> o1(n), o2(n); iota(all(o1), 0), iota(all(o2), 0);
    for (auto& [x, y] : pt) cin >> x >> y;
    sort(all(o1), [&] (int x, int y) {
        return pt[x].first < pt[y].first;
    });
    sort(all(o2), [&] (int x, int y) {
        return pt[x].second < pt[y].second;
    });
    vector<int> onde1(n), onde2(n), a, b, c, d;
    for (int i = 0; i < n; ++i)onde1[o1[i]] = i, onde2[o2[i]] = i;
    for (int i = 0; i < n; ++i) {
        if (max(onde1[i], onde2[i]) < n/2) a.pb(i);
        else if (min(onde1[i], onde2[i]) >= n/2) b.pb(i);
        else if (onde1[i] < n/2) c.pb(i);
        else d.pb(i);
    }
    assert(sz(a) == sz(b));
    assert(sz(d) == sz(c));
    vector<ii> ans;
    for (int i = 0; i < sz(a); ++i) ans.pb({a[i], b[i]});
    for (int i = 0; i < sz(c); ++i) ans.pb({c[i], d[i]});
    int opt = 0;
    for (auto [x, y] : ans) opt += abs(pt[x].first-pt[y].first) + abs(pt[x].second-pt[y].second);
    for (auto x : ans) cout << x.first+1 << ' ' << x.second+1 << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
