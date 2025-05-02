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
// SegTree
//
// Recursiva com Lazy Propagation
// Query: soma do range [a, b]
// Update: soma x em cada elemento do range [a, b]
// Pode usar a seguinte funcao para indexar os nohs:
// f(l, r) = (l+r)|(l!=r), usando 2N de memoria
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))

const int MAX = maxn;

namespace seg {
	ll seg[4*MAX], lazy[4*MAX];
	int n, *v;

	ll build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = 0;
		int m = (l+r)/2;
		return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}
	void buildar(int n2) {
		n = n2;
		build();
	}
	void prop(int p, int l, int r) {
		seg[p] += lazy[p];
		if (l != r) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	ll query(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) return seg[p];
		if (b < l or r < a) return inf;
		int m = (l+r)/2;
		return min(query(a, b, 2*p, l, m), query(a, b, 2*p+1, m+1, r));
	}
	ll update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
			lazy[p] += x;
			prop(p, l, r);
			return seg[p];
		}
		if (b < l or r < a) return seg[p];
		int m = (l+r)/2;
		return seg[p] = min(update(a, b, x, 2*p, l, m), update(a, b, x, 2*p+1, m+1, r));
	}
// primeira posicao >= val em [a, b] (ou -1 se nao tem)
int get_left(int a, int b, int p=1, int l=0, int r=n-1) {
	prop(p, l, r);
	if (b < l or r < a or seg[p]) return -1;
	if (r == l) return l;
	int m = (l+r)/2;
	int x = get_left(a, b, 2*p, l, m);
	if (x != -1) return x;
	return get_left(a, b, 2*p+1, m+1, r);
}

// ultima posicao >= val em [a, b] (ou -1 se nao tem)
int get_right(int a, int b, int p=1, int l=0, int r=n-1) {
	prop(p, l, r);
	if (b < l or r < a or seg[p]) return -1;
	if (r == l) return l;
	int m = (l+r)/2;
	int x = get_right(a, b, 2*p+1, m+1, r);
	if (x != -1) return x;
	return get_right(a, b, 2*p, l, m);
}
};


void solve(){
    int n, m; cin >> n >> m;
    vector<iii> v(m);
    for (auto& [x, y, z] : v) cin >> x >> y >> z, --y, --z;
    seg::buildar(n);
    vector<int> ptr(m+1, m-1);
    vector<multiset<int>> mt(n);
    vector<int> seg(4*n);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k, int mode) -> void {
        if (l == r) {
            if (mode) {
                mt[l].insert(k);
                seg[i] = *begin(mt[l]);
            } else {
                mt[l].erase(mt[l].find(k));
                seg[i] = *begin(mt[l]);
            }
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k, mode);
        else self(self, 2*i+1, md+1, r, x, k, mode);
        seg[i] = min(seg[2*i], seg[2*i+1]);
    };
    for (int i = 0; i < n; ++i) upd(upd, 1, 0, n-1, i, n, 1);
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return n;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return min(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    auto rem = [&] (int i) {
        auto [a, b, c] = v[i];
        if (a) upd(upd, 1, 0, n-1, b, c, 0);
        else seg::update(b, c, -1);
    };
    auto add = [&] (int i) {
        auto [a, b, c] = v[i];
        if (a) upd(upd, 1, 0, n-1, b, c, 1);
        else seg::update(b, c, 1);
    };
    for (int l = m-1; ~l; --l) {
        ptr[l] = ptr[l+1];
        auto [a, b, c] = v[l];
        add(l);
        if (a) {
            while (seg::query(b, c) != 0) rem(ptr[l]--);
        } else {
            while (true) {
                int lx = seg::get_right(0, c), rx = seg::get_left(b, n-1);
                if (lx == -1) lx = 0;
                else lx++;
                if (rx == -1) rx = n-1;
                else rx--;
                int mn = query(query, 1, 0, n-1, lx, rx);
                if (mn > rx) break;
                rem(ptr[l]--);
            }
        }
    }
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        --l, --r;
        cout << (ptr[l] >= r ? "YES" : "NO") << endl;
    }
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
