#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
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
namespace seg {
	ll seg[4*maxn], lazy[4*maxn];
	int n;
    vector<int> v;

	ll build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = max(build(2*p, l, m), build(2*p+1, m+1, r));
	}
	void build(int n2, vector<int>& v2) {
		n = n2, v = v2;
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
		if (b < l or r < a) return -1e18;
		int m = (l+r)/2;
		return max(query(a, b, 2*p, l, m), query(a, b, 2*p+1, m+1, r));
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
		return seg[p] = max(update(a, b, x, 2*p, l, m),
			update(a, b, x, 2*p+1, m+1, r));
	}
	ll setar(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
            seg[p] = x;
			return seg[p];
		}
		if (b < l or r < a) return seg[p];
		int m = (l+r)/2;
		return seg[p] = max(setar(a, b, x, 2*p, l, m),
			setar(a, b, x, 2*p+1, m+1, r));
	}
};
int brute(int n, vector<int> v, vector<int> a, vector<int> b) {
    vector<int> onde_a(n), onde_b(n), s_maior(n);
    for (int i = 0; i < n; ++i) onde_b[b[i]] = i, onde_a[a[i]] = i;
    int ans = 0;
    vector<int> dp(n);
    // speedup this!
    for (int i = 0; i < n; ++i) {
        int pos = onde_a[b[i]];
        dp[pos] = -1e18;
        int adc = v[a[pos]];
        for (int j = pos-1; j >= 0; --j) {
            if (onde_b[a[j]] < i) ckmax(dp[pos], dp[j] + adc);
            else adc += v[a[j]];
        }
        ckmax(dp[pos], adc);
        ckmax(ans, dp[pos]);
    }
    return ans;
}

int solve(int n, vector<int> v, vector<int> a, vector<int> b) {
    vector<int> onde_a(n), onde_b(n), s_maior(n);
    for (int i = 0; i < n; ++i) onde_b[b[i]] = i, onde_a[a[i]] = i;
    int ans = 0;
    vector<int> bit(n+1);
    auto insert = [&] (int x, int k) {
        while (x <= n) bit[x] += k, x += x & (-x);
    };
    auto query = [&] (int x) {
        int rep = 0;
        while (x) {
            rep += bit[x];
            x -= x & (-x);
        }
        return rep;
    };
    for (int i = n-1; ~i; --i) {
        int pos = onde_a[b[i]];
        s_maior[pos] = query(pos+1);
        insert(pos+1, v[a[pos]]); 
    }
    vector<int> lixo(n, -1e18);
    seg::build(n, lixo);
    for (int i = 0; i < n; ++i) {
        int pos = onde_a[b[i]];
        int best = max(0LL, seg::query(0, pos)) + s_maior[pos] + v[a[pos]];
        ckmax(ans, best);
        seg::update(pos, n-1, v[a[pos]]);
        seg::setar(pos, pos, best - s_maior[pos]);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n), b(n), v(n);
        for (auto& x : v) cin >> x;
        for (auto& x : a) cin >> x, --x;
        for (auto& x : b) cin >> x, --x;
        cout << solve(n, v, a, b) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 50);
        vector<int> v(n), a(n), b(n); iota(all(a), 0), iota(all(b), 0); shuffle(all(a), rng), shuffle(all(b), rng);
        for (auto& x : v) x = rnd(-10, 10);
        int my = solve(n, v, a, b), ans = brute(n, v, a, b);
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
