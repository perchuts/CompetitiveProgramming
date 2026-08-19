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
    int N = 1;
    while (N < n) N *= 2;
    vector<int> mn(5*N), mx(5*N), ans(5*N);
    auto upd = [&] (auto&& self, int i, int l, int r, int target, int val) -> void {
        if (l == r) {
            mn[i] = mx[i] = val;
            return;
        }
        int md = (l + r) / 2;
        if (target <= md) self(self, 2*i, l, md, target, val);
        else self(self, 2*i+1, md+1, r, target, val);
        mn[i] = min(mn[2*i], mn[2*i+1]);
        mx[i] = max(mx[2*i], mx[2*i+1]);
        ans[i] = max(ans[2*i], ans[2*i+1]);
        if (mn[2*i+1] < mx[2*i]) ans[i] = (md+1)^md;
    };
    for (int i = 0; i < N; ++i) {
        if (i < n) upd(upd, 1, 0, N-1, i, a[i]);
        else upd(upd, 1, 0, N-1, i, 2e9);
    }
    vector<int> msb(N);
    msb[1] = 1;
    for (int i = 2; i < N; ++i) msb[i] = 2*msb[i/2];
    cout << msb[ans[1]] << endl;
    while (q--) {
        int i, x; cin >> i >> x;
        upd(upd, 1, 0, N-1, i, x);
        cout << msb[ans[1]] << endl;
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
