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
const int maxn = 2e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

// MO
//
// Para ter o bound abaixo, escolher
// SQ = n / sqrt(q)
// 
// O(n * sqrt(q))

const int MAX = 2e5+10;
const int SQ = sqrt(MAX)/12;

int ans, n;

inline ll hilbert(int x, int y) {
	static int N = 1 << (__builtin_clz(0) - __builtin_clz(MAX));
	int rx, ry, s;
	ll d = 0;
	for (s = N/2; s > 0; s /= 2) {
		rx = (x & s) > 0, ry = (y & s) > 0;
		d += s * ll(s) * ((3 * rx) ^ ry);
		if (ry == 0) {
			if (rx == 1) x = N-1 - x, y = N-1 - y;
			swap(x, y);
		}
	}
	return d;
}

// segtree de soma, frequencia (par)

ii seg[4*maxn];

void upd(int i, int l, int r, int x, int v1, int v2) {
    if (l == r) {
        seg[i].first = v1;
        seg[i].second = v2;
        return;
    }
    int md = (l+r)/2;
    if (x <= md) upd(2*i, l, md, x, v1, v2);
    else upd(2*i+1, md+1, r, x, v1, v2);
    seg[i].first = seg[2*i].first + seg[2*i+1].first;
    seg[i].second = seg[2*i].second + seg[2*i+1].second;
}

int query(int i, int l, int r, int x) {
    if (l == r) return (x ? seg[i].first : 0);
    int md = (l+r)/2;
    if (seg[2*i].second >= x) return query(2*i, l, md, x);
    return query(2*i+1, md+1, r, x - seg[2*i].second) + seg[2*i].first;
}

int onde[2*maxn], quem[2*maxn], val[2*maxn];

inline void insert(int p) {
    //cout << "adding " << p << ": " << onde[quem[p]] << ' ' << val[quem[p]] << ' ' << 1 << endl;
    upd(1, 0, 2*n-1, onde[quem[p]], val[quem[p]], 1);
}

inline void erase(int p) {
    //cout << "erasing " << p << ": " << quem[p] << ' ' << 0 << ' ' << 0 << endl;
    upd(1, 0, 2*n-1, onde[quem[p]], 0, 0);
}
#define HILBERT true
vector<int> MO(vector<pair<int, int>> &q, vector<int> reqs) {
	ans = 0;
	int m = q.size();
	vector<int> ord(m);
	iota(ord.begin(), ord.end(), 0);
#if HILBERT
	vector<ll> h(m);
	for (int i = 0; i < m; i++) h[i] = hilbert(q[i].first, q[i].second);
	sort(ord.begin(), ord.end(), [&](int l, int r) { return h[l] < h[r]; });
#else
	sort(ord.begin(), ord.end(), [&](int l, int r) {
		if (q[l].first / SQ != q[r].first / SQ) return q[l].first < q[r].first;
		if ((q[l].first / SQ) % 2) return q[l].second > q[r].second;
		return q[l].second < q[r].second;
	});
#endif
	vector<int> ret(m);
	int l = 0, r = -1;
	for (int i : ord) {
		int ql, qr;
		tie(ql, qr) = q[i];
		while (r < qr) insert(++r);
		while (l > ql) insert(--l);
		while (l < ql) erase(l++);
		while (r > qr) erase(r--);
        //cout << "answering query = " << i << endl;
		ret[i] = query(1, 0, 2*n-1, reqs[i]);
        //cout << "answer = " << ret[i] << endl;
	}
	return ret;
}

void solve() {
    cin >> n;
    vector<int> a(n), b(n), lvl(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    vector<vector<int>> g(n);
    vector<ii> edg(n-1);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        edg[i] = {u, v};
        g[u].pb(v);
        g[v].pb(u);
    }
    int q; cin >> q;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y, --x;
    vector<int> lx(n), rx(n);
    int t = -1;

    vector<int> vals(2*n), ord(2*n);
    for (int i = 0; i < n; ++i) vals[i] = a[i], vals[i+n] = val[i] = b[i] - a[i];
    iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return vals[x] < vals[y]; });
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        lx[u] = ++t;
        quem[t] = u;
        lvl[u] = 1 + lvl[p];
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
        rx[u] = t;
    };
    dfs(dfs, 0, 0);
    vector<ii> intrs;
    vector<int> reqs;
    for (int i = 0; i < q; ++i) {
        int j = qu[i].first;
        auto [u, v] = edg[j];
        if (lvl[u] < lvl[v]) swap(u, v);
        //cout << "qry: " << lx[u] << ' ' << rx[u] << ' ' << qu[i].second << endl;
        intrs.pb({lx[u], rx[u]}), reqs.pb(qu[i].second);
    }
    //for (int i = 0; i < n; ++i) cout << lx[i] << ' ' << rx[i] << endl;
    for (int i = 0; i < 2*n; ++i) {
        if (ord[i] < n) upd(1, 0, 2*n-1, i, vals[ord[i]], 1);
        else onde[ord[i]-n] = i;
    }
    auto ans = MO(intrs, reqs);
    for (auto x : ans) cout << x << endl;
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
