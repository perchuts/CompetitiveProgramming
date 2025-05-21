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
const int maxn = 1e6+100;

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
const int SQ = sqrt(MAX);
int v[MAX];

int ans, freq[maxn];
vector<ii> bichos[MAX];
int tot[maxn];
inline void insert(int p) {
    for (auto [x, y] : bichos[p]) {
        if (freq[x] == 0) ans++;
        freq[x] += y;
        if (freq[x] >= 3) freq[x] -= 3;
        if (freq[x] == 0) ans--;
    }
}

inline void erase(int p) {
    for (auto [x, y] : bichos[p]) {
        if (freq[x] == 0) ans++;
        freq[x] += 3-y;
        if (freq[x] >= 3) freq[x] -= 3;
        if (freq[x] == 0) ans--;
    }
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
vector<int> MO(vector<pair<int, int>> &q) {
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
		ret[i] = ans;
	}
	return ret;
}
int sexo[maxn];
void solve(){
    int n, q; cin >> n >> q;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    vector<ii> qq(q);
    for (auto& [x, y] : qq) cin >> x >> y, --x, --y;
    for (int i = 2; i < maxn; ++i) {
        if (sexo[i]) continue;
        sexo[i] = i;
        for (int j = i * i; j < maxn; j += i) if (sexo[j] == 0) sexo[j] = i; 
    }
    for (int i = 0; i < n; ++i) {
        int cur = v[i];
        while (cur != 1) {
            int p = sexo[cur], t = 0;
            while (sexo[cur] == p) cur /= p, t++;
            t %= 3;
            if (t) bichos[i].pb({p, t});
        }
    }
    auto ans = MO(qq);
    for (auto x : ans) cout << (x == 0 ? "Yes" : "No") << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
