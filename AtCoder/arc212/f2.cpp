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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n, m, x; cin >> n >> m >> x;
    // so precisamos resolver o caso com gcd(a1, a2) = 1
    // a[3]-a[2] = value added to form a[3] = +- a[1]
    // a[4]-a[3] = value added to form a[4] = +- a[2]
    // a[5]-a[4] = value added to form a[5] = += a[3]
    // number of ways to get to coordinate (x, y) in N-2 steps
    int lim = 10;
    vector<vector<ii>> achieve(lim+1);
    achieve[0] = {{0, 1}, {1, 0}};
    const int shift = 100;
    auto go = [&] (auto&& self, int x1, int y1, int x2, int y2, int layer) -> void {
        if (layer > lim) return;
        if (min({x1, x2}) < 0) return;
        achieve[layer].pb({x1, y1});
        self(self, x1+x2, y1+y2, x1, y1, layer+1);
        self(self, x1-x2, y1-y2, x1, y1, layer+1);
    };
    go(go, 1, 0, 0, 1, 0);
    for (int w = 0; w <= lim; ++w) {
        sort(all(achieve[w]));
        achieve[w].erase(unique(all(achieve[w])), end(achieve[w]));
        vector<vector<char>> grid(2*shift+1, vector<char>(2*shift+1, '.'));
        cout << "layer = " << w << endl;
        for (auto [x, y] : achieve[w]) {
            assert(max(abs(x), abs(y)) <= shift);
            if (x >= 0 and y >= 0) grid[-x + shift][y + shift] = '#';
        }
        for (int i = -shift; i <= shift; ++i) {
            for (int j = -shift; j <= shift; ++j) {
                if (i == 0 and j == 0) {
                    if (grid[shift][shift] == '#') cout << "O";
                    else cout << "o";
                } else {
                    cout << grid[i+shift][j+shift];
                }
            }
            cout << endl;
        }
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
