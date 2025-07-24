#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define gato

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
// RMQ <O(n), O(1)> - min queue
//
// O(n) pra buildar, query O(1)
// Se tiver varios minimos, retorna
// o de menor indice

template<typename T> struct rmq {
	vector<T> v;
	int n; static const int b = 30;
	vector<int> mask, t;

	int op(int x, int y) { return v[x] <= v[y] ? x : y; }
	int msb(int x) { return __builtin_clz(1)-__builtin_clz(x); }
	int small(int r, int sz = b) { return r-msb(mask[r]&((1<<sz)-1)); }
	rmq() {}
	rmq(const vector<T>& v_) : v(v_), n(v.size()), mask(n), t(n) {
		for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
			at = (at<<1)&((1<<b)-1);
			while (at and op(i-msb(at&-at), i) == i) at ^= at&-at;
		}
		for (int i = 0; i < n/b; i++) t[i] = small(b*i+b-1);
		for (int j = 1; (1<<j) <= n/b; j++) for (int i = 0; i+(1<<j) <= n/b; i++)
			t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
	}
	int index_query(int l, int r) {
		if (r-l+1 <= b) return small(r, r-l+1);
		int x = l/b+1, y = r/b-1;
		if (x > y) return op(small(l+b-1), small(r));
		int j = msb(y-x+1);
		int ans = op(small(l+b-1), op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
		return op(ans, small(r));
	}
	T query(int l, int r) { return v[index_query(l, r)]; }
};
vector<int> solve(int n, int q, vector<int> a, vector<ii> qqq) {
    if (n == 1) return vector<int>(q, 0);
    vector<int> ord(n); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) {
        return a[x] < a[y];
    });
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[ord[i]] = i;
    rmq<int> sexo(pos);
    const int B = 700;
    vector<vector<iii>> qu(n/B+1);
    int II = 0;
    for (auto [l, r] : qqq) qu[l/B].pb({r, l, II++});
    vector<int> ans(q);
    struct node {
        int orr = 0, andd = (1<<30)-1;
    } neutro;
    vector<node> seg(4*n);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int ox, int ax) -> void {
        if (l == r) {
            seg[i].orr = ox;
            seg[i].andd = ax;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, ox, ax);
        else self(self, 2*i+1, md+1, r, x, ox, ax);
        seg[i].orr = seg[2*i].orr|seg[2*i+1].orr;
        seg[i].andd = seg[2*i].andd&seg[2*i+1].andd;
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (r < x or y < l) return neutro;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        auto lx = self(self, 2*i, l, md, x, y);
        auto rx = self(self, 2*i+1, md+1, r, x, y);
        return {lx.orr|rx.orr, lx.andd&rx.andd};
    };
    int lx = 0, rx = 0;
    for (int i = 0; i * B < n; ++i) {
        sort(all(qu[i]));
        for (auto [r, l, id] : qu[i]) { 
            while (rx <= r) {
                //cout << "add " << rx << endl;
                upd(upd, 1, 0, n-1, pos[rx], a[rx], a[rx]), rx++;
            }
            while (r < rx-1) {
                //cout << "rem " << rx-1 << endl;
                --rx, upd(upd, 1, 0, n-1, pos[rx], 0, (1<<30)-1);
            }
            while (lx < l) {
                //cout << "rem " << lx << endl;
                upd(upd, 1, 0, n-1, pos[lx], 0, (1<<30)-1), lx++;
            }
            while (l < lx) {
                //cout << "add " << lx-1 << endl;
                --lx, upd(upd, 1, 0, n-1, pos[lx], a[lx], a[lx]);
            }
            if (l == r) continue;
            //cout << "answer " << id << endl;
            //int base = sexo.query(l, r);
            //while (base < n-1) {
            //    int p1 = base+1, p2 = n-1, nbase = n-1;
            //    int X = query(query, 1, 0, n-1, 0, base).orr;
            //    int Y = query(query, 1, 0, n-1, base+1, n-1).andd;
            //    //cout << "base = " << base << " X = " << X << " Y = " << Y << endl;
            //    if (X == Y) { ans[id] = 1; break; }
            //    while (p1 <= p2) {
            //        int md = p1 + (p2-p1+1)/2;
            //        int XX = query(query, 1, 0, n-1, 0, md).orr;
            //        int YY = query(query, 1, 0, n-1, md+1, n-1).andd;
            //        if (XX != X or YY != Y) nbase = md, p2 = md-1;
            //        else p1 = md+1;
            //    }
            //    base = nbase;
            //}

        }
    }
    return ans;
}

vector<int> brute(int n, int q, vector<int> a, vector<ii> que) {
    vector<int> ans;
    for (auto [l, r] : que) {
        auto aa = a;
        sort(begin(aa)+l, begin(aa)+r+1);
        if (l == r) { ans.pb(0); continue; }
        bool ok = 0;
        for (int i = l; i < r; ++i) {
            int x = 0, y = (1 << 30)-1;
            for (int j = l; j <= i; ++j) x |= aa[j];
            for (int j = i+1; j <= r; ++j) y &= aa[j];
            if (x == y) ok = 1;
        }
        ans.pb(ok);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<ii> qq(q);
    for (auto& [x, y] : qq) cin >> x >> y, --x, --y;
    auto ans = solve(n, q, a, qq);
    for (auto x : ans) cout << (x ? "YES" : "NO") << endl;
#else
    int t = 1;
    while (true) {
        int n = 1e5, q = 1e5;
        int bits = 30;
        vector<int> a(n);
        for (auto& x : a) x = rnd(0, (1<<bits)-1);
        vector<ii> qq(q);
        for (auto& [x, y] : qq) x = rnd(0, n-1), y = rnd(x, n-1);
        auto my = solve(n, q, a, qq);
        cout << n << ' ' << q << endl;
        cout << "ok " << my[0] << endl;
        //auto ans = brute(n, q, a, qq);
        //if (my != ans) {
        //    cout << "Wrong answer on test " << t << endl;
        //    cout << n << ' ' << q << endl;
        //    for (auto x : a) cout << x << ' ';
        //    cout << endl;
        //    for (auto [x, y] : qq) cout << x + 1 << ' ' << y + 1 << endl;
        //    cout << "Your output: ";
        //    for (auto x : my) cout << (x ? "YES" : "NO") << ' ';
        //    cout << endl;
        //    cout << "Answer: ";
        //    for (auto x : ans) cout << (x ? "YES" : "NO") << ' ';
        //    cout << endl;
        //    exit(0);
        //}
        cout << "Accepted on test " << t++ << endl;
        exit(0);
    }
#endif
}
