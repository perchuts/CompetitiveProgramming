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
    int mark = 0;
    vector<array<int, 4>> seg(4*n);
    auto merge = [&] (array<int, 4> lx, array<int, 4> rx) {
        array<int, 4> ans;
        ans[0] = ans[1] = ans[2] = ans[3] = 1e18;
        for (int esq = 0; esq < 4; ++esq) {
            int a1 = esq & 1, a2 = esq >> 1 & 1;
            for (int dir = 0; dir < 4; ++dir) {
                int b1 = dir & 1, b2 = dir >> 1 & 1;
                if (a2 == 0 and b1 == 0) continue;
                ckmin(ans[a1+2*b2], lx[esq] + rx[dir]);
            }
        }
        return ans;
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            seg[i][0] = 0;
            seg[i][1] = seg[i][2] = 1e18;
            seg[i][3] = a[l];
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md);
        self(self, 2*i+1, md+1, r);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    build(build, 1, 0, n-1);
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> array<int, 4> {
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        if (md < x) return self(self, 2*i+1, md+1, r, x, y);
        if (y <= md) return self(self, 2*i, l, md, x, y);
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    int ans = 1e18;
    for (int i = 0; i <= n-k; ++i) {
        auto z = query(query, 1, 0, n-1, i, i+k-1);
        ckmin(ans, z[3]);
        if (i != n-k) ckmin(ans, z[1] + a[i+k]);
    }
    cout << ans << endl;
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
