#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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
// Suffix Array - O(n log n)
//
// kasai recebe o suffix array e calcula lcp[i],
// o lcp entre s[sa[i],...,n-1] e s[sa[i+1],..,n-1]
//
// Complexidades:
// suffix_array - O(n log(n))
// kasai - O(n)

vector<int> suffix_array(vector<int> s, int N) {
    s.pb(0);
    int n = s.size();
    vector<int> sa(n), ra(n);
    for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];

    for(int k = 0; k < n; k ? k *= 2 : k++) {
        vector<int> nsa(sa), nra(n), cnt(N);
        for(int i = 0; i < n; i++) nsa[i] = (nsa[i]-k+n)%n, cnt[ra[i]]++;
        for(int i = 1; i < N; i++) cnt[i] += cnt[i-1];
        for(int i = n-1; i+1; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];

        for(int i = 1, r = 0; i < n; i++) nra[sa[i]] = r += ra[sa[i]] !=
            ra[sa[i-1]] or ra[(sa[i]+k)%n] != ra[(sa[i-1]+k)%n];
        ra = nra;
        if (ra[sa[n-1]] == n-1) break;
    }
    return vector<int>(sa.begin()+1, sa.end());
}

vector<int> kasai(vector<int> s, vector<int> sa) {
    int n = s.size(), k = 0;
    vector<int> ra(n), lcp(n);
    for (int i = 0; i < n; i++) ra[sa[i]] = i;

    for (int i = 0; i < n; i++, k -= !!k) {
        if (ra[i] == n-1) { k = 0; continue; }
        int j = sa[ra[i]+1];
        while (i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
        lcp[ra[i]] = k;
    }
    return lcp;
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

int solve(int n, vector<int> a, vector<int> b, vector<int> c) {
    int x1 = sz(b), x2 = sz(c), opt = 0;
    vector<int> str;
    for (auto x : b) str.pb(x+1);
    str.pb(1);
    for (auto x : c) str.pb(x+1);
    auto sa = suffix_array(str, 2*n+5);
    auto lcp = kasai(str, sa);
    rmq<int> qq(lcp);
    int N = sz(str);
    auto dfs = [&] (auto&& self, int l, int r) -> int {
        int cur_alt = (l == r ? N - sa[l] : qq.query(l, r-1));
        int tipos = 0;
        if (cur_alt + sa[l] == N) {
            if (sa[l] < x1) tipos |= 1;
            if (x1 < sa[l]) tipos |= 2;
            l++;
        }
        while (l <= r) {
            int pos = (l == r ? -1 : qq.index_query(l, r-1));
            if (pos == -1 or lcp[pos] > cur_alt) pos = r;
            tipos |= self(self, l, pos);
            l = pos + 1;
        }
        if (tipos == 3) ckmax(opt, cur_alt);
        return tipos;
    };
    dfs(dfs, 0, N-1);
    if (opt) return x1 + x2 - 2 * opt;
    // they do not share any character
	vector<vector<int>> g(n+5);
	for (int i = 0; i < n-1; ++i) {
		if (a[i] != a[i+1]) {
			g[a[i]].pb(a[i+1]);
			g[a[i+1]].pb(a[i]);
		}
	}
	queue<int> q;
	vector<int> dist(n+5, inf);
	for (auto x : b) { 
		if (dist[x] == inf) {
			dist[x] = 0;
			q.push(x);
		}
	}
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (auto y : g[x]) {
			if (dist[y] == inf) {
				dist[y] = 1 + dist[x];
				q.push(y);
			}
		}
	}
	int mnd = inf;
	for (auto x : c) ckmin(mnd, dist[x]);
	return x1 + x2 + 2 * mnd - 2;
}

int brute(int n, vector<int> a, vector<int> _b, vector<int> _c) {
    map<deque<int>, int> dist;
    set<deque<int>> pode;
    deque<int> b, c;
    for (auto x : _b) b.pb(x);
    for (auto x : _c) c.pb(x);
    for (int i = 0; i < n; ++i) {
        deque<int> v;
        for (int j = i; j < n; ++j) {
            v.pb(a[j]);
            pode.insert(v);
        }
    }
    dist[b] = 0;
    queue<deque<int>> q;
    q.push(b);
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        int d = dist[u];
        if (!u.empty()) {
            int x = u.back();
            u.pop_back();
            if (!dist.count(u) and !u.empty()) {
                dist[u] = d + 1;
                q.push(u);
            }
            u.pb(x);
            x = u.front();
            u.pop_front();
            if (!dist.count(u) and !u.empty()) {
                dist[u] = d + 1;
                q.push(u);
            }
            u.push_front(x);
        }
        for (int i = 1; i <= n; ++i) {
            u.pb(i);
            if (pode.find(u) != end(pode) and !dist.count(u)) {
                dist[u] = d + 1;
                q.push(u);
            }
            u.pop_back();
            u.push_front(i);
            if (pode.find(u) != end(pode) and !dist.count(u)) {
                dist[u] = d + 1;
                q.push(u);
            }
            u.pop_front();
        }
    }
    return dist[c];
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int np, nq; cin >> np;
    vector<int> p(np);
    for (auto& x : p) cin >> x;
    cin >> nq;
    vector<int> q(nq);
    for (auto& x : q) cin >> x;
    cout << solve(n, a, p, q) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(5, 30);
        vector<int> a(n), p, q;
        for (auto& x : a) x = rnd(1, n);
        int l = rnd(0, n-1), r = rnd(l, n-1);
		ckmin(r, l + 1);
        for (int i = l; i <= r; ++i) p.pb(a[i]);
        l = rnd(0, n-1), r = rnd(l, n-1);
		ckmin(r, l + 1);
        for (int i = l; i <= r; ++i) q.pb(a[i]);
        int my = solve(n, a, p, q), ans = brute(n, a, p, q);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << sz(p) << endl;
            for (auto x : p) cout << x << " ";
            cout << endl;
            cout << sz(q) << endl;
            for (auto x : q) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
