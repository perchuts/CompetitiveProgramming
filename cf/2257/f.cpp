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
    int n, q, x; cin >> n >> q >> x;
    vector<int> a(n), b(n);
    for (auto& y : a) cin >> y;
    for (auto& y : b) cin >> y;
    struct node {
        array<int, 25> cost;
        int len;
        node() {
            cost.fill(1e18);
        }
    };
    auto merge = [&] (node &a, node &b) {
        node c;
        c.len = a.len + b.len;
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < min(x,b.len); ++j) {
                for (int k = 0; k < x; ++k) {
                    ckmin(c.cost[5*j+i], a.cost[5*k+i] + b.cost[min({b.len-1-j, x-k-1})+5*j]);
                }
            }
        }
        return c;
    };
    vector<node> seg(4*n);
    auto restart = [&] (int k, int l) {
        seg[k].len = a[l];
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < x; ++j) {
                if (a[l]-1-j >= i) seg[k].cost[5*j+i] = (a[l]-1-i-j+x-1)/x * b[l];
                else seg[k].cost[5*j+i] = 0;
            }
        }
    };
    auto build = [&] (auto&& self, int i, int l, int r) -> void {
        if (l == r) {
            restart(i, l);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md);
        self(self, 2*i+1, md+1, r);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x) -> void {
        if (l == r) {
            restart(i, l);
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x);
        else self(self, 2*i+1, md+1, r, x);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
	auto print = [&] (node a) {
		cout << a.len << endl;
		for (int i = 0; i < x; ++i) {
            for (int j = 0; j < x; ++j) cout << a.cost[5*j+i] << " ";
            cout << endl;
		}
        cout << endl;
	};
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (x <= l and r <= y) {
			//cout << "i = " << i << " l = " << l << " r = " << r << endl;
			//print(seg[i]);
			return seg[i];
		}
        int md = (l+r)/2;
        if (y <= md) return self(self, 2*i, l, md, x, y);
        if (md+1 <= x) return self(self, 2*i+1, md+1, r, x, y);
        auto lx = self(self, 2*i, l, md, x, y);
        auto rx = self(self, 2*i+1, md+1, r, x, y);
        //cout << "after merge: ";
		//cout << "i = " << i << " l = " << l << " r = " << r << endl;
        //auto z = merge(lx, rx);
        //print(z);
        return merge(lx, rx);
    };
    build(build, 1, 0, n-1);
    while (q--) {
        char c; cin >> c;
        if (c == '?') {
            int l, r; cin >> l >> r; --l, --r;
            auto resp = query(query, 1, 0, n-1, l, r);
            cout << resp.cost[0] << endl;
        } else if (c == '1') {
            int i, x; cin >> i >> x; --i;
            a[i] = x;
            upd(upd, 1, 0, n-1, i);
        } else {
            int i, x; cin >> i >> x; --i;
            b[i] = x;
            upd(upd, 1, 0, n-1, i);
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
