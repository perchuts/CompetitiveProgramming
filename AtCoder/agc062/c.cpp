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
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(all(a));
    vector<int> ans;
    vector<ii> ix = {{a[0], a[0]}};
    for (int i = 1; i < n; ++i) {
        int gaps = 0, last = 0;
        for (auto [x, y] : ix) {
            if (a[i] < x) break;
            gaps += x - last - 1;
            last = y;
        }
        if (gaps >= k) break;
        vector<ii> nix = {{a[i], a[i]}}, nv;
        for (auto [x, y] : ix) {
            auto& [xx, yy] = nix.back();
            if (yy == x + a[i] - 1) yy = y + a[i];
            else nix.pb({x+a[i], y+a[i]});
        }
        int p1 = 0, p2 = 0;
        while (p2 != sz(nix)) {
            if (p1 == sz(ix) or ix[p1] > nix[p2]) nv.pb(nix[p2++]);
            else nv.pb(ix[p1++]);
            if (sz(nv) > 1) {
                auto [x1, y1] = nv[sz(nv)-1];
                auto [x2, y2] = nv[sz(nv)-2];
                if (x1 <= y2) nv.pop_back(), ckmax(nv.back().second, y1);
            }
        }
        swap(ix, nv);
    }
    int last = 0;
    for (auto [x, y] : ix) {
        while (last < x - 1 and k != 0) ans.pb(++last), --k;
        if (!k) break;
        last = y;
    }
    while (k != 0) ans.pb(++last), --k;
    for (auto x : ans) cout << x << " ";
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
