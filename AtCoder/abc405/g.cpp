#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#pragma GCC target("bmi,bmi2,popcnt,lzcnt")
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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

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

const int MAX = 2.5e5+10;
const int SQ = sqrt(MAX);
int v[MAX];

int freq[MAX], n__, inv[MAX], Fat[MAX], Ifat[MAX];
int b[MAX], fb[MAX];

inline void insert(int p) {
	int o = v[p];
	freq[o]++;
    fb[o/SQ]++;
    b[o/SQ] = b[o/SQ] * inv[freq[o]] % mod;
}

inline void erase(int p) {
	int o = v[p];
    b[o/SQ] = b[o/SQ] * freq[o] % mod;
    fb[o/SQ]--;
	freq[o]--;
}

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

#define HILBERT true
vector<int> MO(vector<pair<int, int>> &q, vector<int> sexo) {
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
        int lim = sexo[i], j = 0, f = 0, pinv = 1;
        for ( ; (j+1) * SQ <= lim; ++j) {
            pinv = pinv * b[j] % mod;
            f += fb[j];
        }
        for (int k = j * SQ; k < lim; ++k) {
            pinv = pinv * Ifat[freq[k]] % mod;
            f += freq[k];
        }
        ret[i] = Fat[f] * pinv % mod;
	}
	return ret;
}

void solve(){
    int n, q; cin >> n >> q;
    n__ = n;
    vector<int> a(n);
    for (auto& x : a) cin >> x, --x;
    vector<ii> qu(q);
    vector<int> sexo(q);
    Fat[0] = 1;
    for (int i = 0; i <= n; ++i) b[i] = 1;
    for (int i = 1; i <= n; ++i) {
        v[i-1] = a[i-1];
        Fat[i] = Fat[i-1] * i % mod;
    }
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            b = b * b % mod, e /= 2;
        }
        return ans;
    };
    Ifat[n] = fexp(Fat[n], mod-2);
    for (int i = n-1; ~i; --i) Ifat[i] = (i+1) * Ifat[i+1] % mod;
    for (int i = 1; i <= n; ++i) inv[i] = (Fat[i-1] * Ifat[i]) % mod;
    for (int i = 0; i < q; ++i) {
        int l, r, x; cin >> l >> r >> x;
        --l, --r, --x;
        qu[i] = {l, r};
        sexo[i] = x;
    }
    auto ans = MO(qu, sexo);
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
