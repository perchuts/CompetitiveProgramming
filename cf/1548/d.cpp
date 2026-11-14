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
    array<array<int, 2>, 2> qt{};
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        qt[x>>1&1][y>>1&1]++;
    }
    int ans = 0;
    for (int a = 0; a < 4; ++a) {
        int x1 = a&1, y1 = a>>1&1;
        for (int b = 0; b < 4; ++b) {
            if (b == a) continue;
            int x2 = b&1, y2 = b>>1&1;
            ans += (qt[x1][y1])*(qt[x1][y1]-1)*qt[x2][y2]/2;
        }
        ans += (qt[x1][y1])*(qt[x1][y1]-1)*(qt[x1][y1]-2)/6;
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
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
