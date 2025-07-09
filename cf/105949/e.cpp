#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

#define P 998244353

int fexp(int b, int e){
	int r = 1;
	while(e){
		if(e&1) r = r * b % P;
		e /= 2; b = b * b % P;
	}
	return r;
}
int inv(int g) { return fexp(g, P - 2); }
int add(int a, int b) {
	a += b; if (a >= P) a -= P;
	return a;
}
int sub(int a, int b) {
	a -= b; if (a < 0) a += P;
	return a;
}

void ntt(vector<int>& a, bool rev) {
	int n = a.size(); auto b = a;
	assert(!(n&(n-1)));
	int g = 1;
	while (fexp(g, P / 2) == 1) g += 1;
	if (rev) g = inv(g);

	for (int step = n/2; step; step /= 2) {
		int w = fexp(g, P / (n / step)), wn = 1;
		for (int i = 0; i < n/2; i += step) {
			for (int j = 0; j < step; j++) {
				auto u = a[2*i + j], v = wn * a[2*i + j + step] % P;
				b[i+j] = add(u, v); b[i + n/2 + j] = sub(u, v);
			}
			wn = wn * w % P;
		}
		swap(a, b);
	}

	if (rev) {
		auto n1 = inv(n);
		for (auto& x : a) x = x * n1 % P;
	}
}

vector<int> conv(vector<int> l, vector<int> r) {
	int N = l.size()+r.size()-1, n = 1;
	while (n <= N) n *= 2;
	l.resize(n); r.resize(n);
	ntt(l, false);
	ntt(r, false);
	for (int i = 0; i < n; i++) l[i] = l[i] * r[i] % P;
	ntt(l, true);
	l.resize(N);
	return l;
}

const int mod = (119<<23)+1;

vector<int> inv(vector<int> p) {
	assert(!p.empty() && p[0] != 0);

	vector<int> q = {inv(p[0])};
	int n = p.size(), k = 1;
	while (k < n) {
		k *= 2;
		q.resize(2*k);
		ntt(q, false);
		vector<int> p0(2*k);
		copy_n(p.begin(), min(k, n), p0.begin());
		ntt(p0, false);
		for (int i = 0; i < 2*k; i++)
			q[i] = q[i] * (2 - (p0[i] * q[i] % P) + P) % P;
		ntt(q, true);
		q.resize(k);
	}
	q.resize(n);

	return q;
}

int32_t main() {
	fast_io;
	int n, k; cin >> n >> k;
	if (n < k or k == 2) {
		cout << 0 << endl;
		exit(0);
	}
	int N = n+5;
	vector<int> f(N), g(N+1), dp(k), fat(N+1, 1), ifat(N+1);
	for (int i = 1; i <= N; ++i) g[i] = fexp(2, i*(i-1)/2), fat[i] = i * fat[i-1] % mod;
    ifat[N] = fexp(fat[N], mod-2);
    for (int i = N-1; i >= 0; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    //auto C = [&] (int x, int y) { return fat[x] * ifat[y] % mod * ifat[x-y] % mod; };
	auto go = [&] (auto&& self, int l, int r) -> void {
		if (l == r) {
			f[l] = (g[l] - f[l] * fat[l]) % mod;
			f[l] = (f[l] + mod) % mod;
			return;
		}
		int md = (l+r)/2;
		self(self, l, md);
		vector<int> p1(md-l+1), Q(r-l+1);
		for (int i = l; i <= md; ++i) p1[i-l] = f[i] * ifat[i] % mod;
		for (int i = 1; i <= r-l; ++i) Q[i] = g[i] * ifat[i] % mod;
		auto res = conv(p1, Q);
		for (int i = md+1; i <= r; ++i) f[i] = (f[i] + res[i-l]) % mod;
		self(self, md+1, r);
	};
	go(go, 1, k-1);
	//cout << "comparacao: " << endl;
	//for (int i = 1; i < k; ++i) {
	//	dp[i] = g[i];
	//	for (int j = 1; j < i; ++j) {
	//		dp[i] = (dp[i] - dp[j] * g[i-j] % mod * C(i, j)) % mod;
	//		dp[i] = (dp[i] + mod) % mod;
	//	}
	//	//cout << f[i] << ' ' << dp[i] << endl;
	//}
	int e = n+1;
	vector<int> poly = {1};
	for (int i = 0; i < f.size(); ++i) f[i] = f[i] * ifat[i] % mod;
	auto div = f;
	while (e) {
		if (e&1) {
			poly = conv(poly, f);
			if (poly.size() > n+5) poly.resize(n+5);
		}
		f = conv(f, f);
		if (f.size() > n+5) f.resize(n+5);
		e /= 2;
	}
	//for (auto x : poly) cout << x << ' ';
	//cout << endl;
	poly[0] = (poly[0] - 1 + mod) % mod;
	div[0] = (div[0] - 1 + mod) % mod;
	div = inv(div);
	poly = conv(poly, div);
	//for (int i = 1; i <=n; ++i) cout << poly[i] * fat[i] % mod << ' ';
	//cout << endl;
	int ans = poly[n] * fat[n] % mod;
	ans = (g[n] - ans + mod) % mod;
	cout << ans << endl;
}
