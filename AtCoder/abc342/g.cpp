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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int q; cin >> q;
    vector<bool> disabled(q);
    vector<set<ii>> seg(4*n);
    int id = 0;
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int k) -> void {
        if (r < x or y < l) return;
        if (x <= l and r <= y) {
            seg[i].insert({-k, id});
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, k);
        self(self, 2*i+1, md+1, r, x, y, k);
    };
    auto get = [&] (auto&& self, int i, int l, int r, int x) -> int {
        int best = a[x];
        while (!seg[i].empty()) {
            auto [x, y] = *begin(seg[i]);
            if (!disabled[y]) break;
            seg[i].erase({x, y});
        }
        if (!seg[i].empty()) best = -(begin(seg[i])->first);
        if (l == r) return best;
        int md = (l + r) / 2;
        if (x <= md) ckmax(best, self(self, 2*i, l, md, x));
        else ckmax(best, self(self, 2*i+1, md+1, r, x));
        return best;
    };
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int l, r, x; cin >> l >> r >> x; --l, --r;
            upd(upd, 1, 0, n-1, l, r, x);
        } else if (op == 2) {
            int x; cin >> x; --x;
            disabled[x] = true;
        } else {
            int x; cin >> x; --x;
            cout << get(get, 1, 0, n-1, x) << endl;
        }
        id++;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
