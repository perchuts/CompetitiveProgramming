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
    vector<int> pos(n), l(n);
    for (auto& x : pos) cin >> x;
    for (auto& x : l) cin >> x;
    for (int i = n-1; ~i; --i) pos[i] += 151852;
    vector<int> ev;
    int ans = 0;
    for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) ev.pb((pos[i]+pos[j])/2+1), ev.pb((pos[i]+pos[j])/2);
    ev.pb(-3e18);
    ev.pb(3e18);
    sort(all(ev));
    ev.erase(unique(all(ev)), end(ev));
    auto check = [&] (int p, int mx) {
        vector<int> ord(n); iota(all(ord), 0); sort(all(ord), [&] (int a, int b) { return abs(p-pos[a]) < abs(p-pos[b]); });
        int lx = p, rx = mx-1;
        for (int j = 0; j < n; ++j) ckmax(lx, pos[ord[j]] - l[j]), ckmin(rx, pos[ord[j]] + l[j]);
        return pair(lx, rx);
    };
    for (int i = 0; i < sz(ev)-1; ++i) {
        auto [xx, yy] = check(ev[i], ev[i+1]);
        ans += max(0LL, yy-xx+1);
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
