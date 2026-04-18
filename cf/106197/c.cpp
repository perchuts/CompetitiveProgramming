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
    int n; cin >> n;
    if (n == 1) {
        cout << "! " << 0 << endl;
        exit(0);
    }
    int pos1 = 0, used = 0;
    map<ii, int> penis;
    auto ask = [&] (int i, int j) {
        if (penis.count({i, j})) return penis[{i, j}];
        cout << "? " << i + 1 << " " << j + 1 << endl;
        used++;
        int x; cin >> x; --x;
        penis[{i, j}] = penis[{j, i}] = x;
        return x;
    };
    for (int i = 1; i < n; ++i) {
        if (i == pos1) continue;
        pos1 = ask(i, pos1);
    }
    vector<int> can;
    for (int i = 0; i < n; ++i) if (i != pos1) can.pb(i);
    int tries = 0;
    while (tries < 1000 and (used + sz(can) - 1 <= 3*n or used + sz(can) * (sz(can)-1)/2 > 3*n)) {
        tries++;
        shuffle(all(can), rng);
        vector<int> ok(sz(can), 1);
        for (int i = 1; i < sz(can); ++i) {
            int x = ask(can[i-1], can[i]);
            if (x != pos1) {
                if (x != can[i]) ok[i] = 0;
                if (x != can[i-1]) ok[i-1] = 0;
            }
        }
        vector<int> ncan;
        for (int i = 0; i < sz(can); ++i) if (ok[i]) ncan.pb(can[i]);
        swap(can, ncan);
    }
    vector<int> ans = can;
    if (used + sz(can) * (sz(can)-1)/2 <= 3*n) {
        vector<int> ok(sz(can), 1);
        for (int i = 0; i < sz(can); ++i) {
            for (int j = i + 1; j < sz(can); ++j) {
                int x = ask(can[i], can[j]);
                if (x != pos1) {
                    if (x != can[i]) ok[i] = 0;
                    if (x != can[j]) ok[j] = 0;
                }
            }
        }
        ans.clear();
        for (int i = 0; i < sz(can); ++i) if (ok[i]) ans.pb(can[i]);
    }
    cout << "! ";
    cout << sz(ans) << " ";
    for (auto x : ans) cout << x + 1 << " ";
    cout << endl;
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
