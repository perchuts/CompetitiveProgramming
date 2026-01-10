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
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(rbegin(a), rend(a));
    vector<int> _a;
    for (int i = 0; i < min(n, 30LL); ++i) _a.pb(a[i]);
    while (q--) {
        int c; cin >> c;
        a = _a; int ans = 0;
        for (int i = 29; ~i; --i) {
            int cntc = (c >> i & 1);
            int cnta = 0;
            for (auto x : a) cnta += (x >> i & 1);
            if (cntc > cnta) {
                int best = inf, argmin;
                for (int j = 0; j < min(n, 30LL); ++j) if (ckmin(best, (1 << i) - (a[j] % (1 << i)))) argmin = j;
                ans += best, a[argmin] += best;
            }
            if (cntc < cnta) break;
        }
        cout << ans << endl;
    }
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
