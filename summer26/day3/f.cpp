#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
//#define gato

using namespace std;

using ll = long long;
const int mod = (119<<23)+1;

template<int p> struct mod_int {
	ll expo (ll b, ll e) {
		ll ret = 1;
		while (e) {
			if (e % 2) ret = ret * b % p;
			e /= 2, b = b * b % p;
		}
		return ret;
	}
	ll inv(ll b) { return expo(b, p-2); }
	using m = mod_int;
	int v;
	mod_int() : v(0) {}
	mod_int(ll v_) {
		if  (v_ >= p or v_ <= -p) v_ %= p;
		if (v_ < 0) v_ += p;
		v = v_;
	}
	m& operator +=(const m& a) {
		v += a.v;
		if (v >= p) v -= p;
		return *this;
	}
	m& operator -=(const m& a) {
		v -= a.v;
		if (v < 0) v += p;
		return *this;
	}
	m& operator *=(const m& a) {
		v = v * ll(a.v) % p;
		return *this;
	}
	m& operator /= (const m& a) {
		v = v * inv(a.v) % p;
		return *this;
	}
	m operator -() { return m(-v); }
	m& operator ^= (ll e) {
		if (e < 0) {
			v = inv(v);
			e = -e;
		}
		v = expo(v, e);
		return *this;
	}
	bool operator == (const m& a) { return v == a.v; }
	bool operator != (const m& a) { return v != a.v; }
	friend m operator +(m a, m b) { return a += b; }
	friend m operator -(m a, m b) { return a -= b; }
	friend m operator /(m a, m b) { return a /= b; }
	friend m operator *(m a, m b) { return a *= b; }
	friend m operator ^(m a, ll e) { return a ^= e; }
};

typedef mod_int<mod> mint;

void ntt(vector<mint>& a, bool rev) {
	int n= a.size(); auto b = a;
	assert(!(n&(n-1)));
	mint g = 1;
	while ((g^(mod/2)) == 1) g += 1;
	if (rev) g = 1 / g;

	for (int step = n / 2; step; step /= 2) {
		mint w = g^(mod / (n / step)), wn = 1;
		for (int i = 0; i < n/2; i += step) {
			for (int j = 0; j < step; ++j) {
				auto u = a[2*i+j], v = wn * a[2*i+j+step];
				b[i+j] = u + v; b[i+n/2+j] = u-v;
			}
			wn = wn * w;
		}
		swap(a, b);
	}
	if (rev) {
		auto n1 = mint(1)/n;
		for (auto& x : a) x *= n1;
	}
}

vector<mint> convolution(const vector<mint>& a, const vector<mint>& b) {
	vector<mint> l(a.begin(), a.end()), r(b.begin(), b.end());
	int N = l.size() + r.size() - 1, n = 1 << __lg(2*N-1);
	l.resize(n);
	r.resize(n);
	ntt(l, false);
	ntt(r, false);
	for (int i = 0; i < n; ++i) l[i] *= r[i];
	ntt(l, true);
	l.resize(N);
	return l;
}

int solve(int n, vector<int> p) {
	vector<int> used(2*n);
	int falta = 0;
	for (auto x : p) {
		if (x != -1) used[x] = 1;
		else falta++;
	}
	int A = 0, B = 0, C = 0;
	for (int i = 0; i < n; ++i) {
		if (p[i] == -1 and p[i+n] == -1) C++;
		if (used[i] == 0 and used[2*n-1-i] == 0) A++;
		if (p[i] == -1 and p[i+n] != -1) {
			if (used[2*n-1-p[i+n]] == 0) B++;
		} else if (p[i] != -1 and p[i+n] == -1) {
			if (used[2*n-1-p[i]] == 0) B++;
		}
	}
	for (int i = 0; i < n; ++i) {
		if (p[i] != -1 and p[i+n] != -1 and p[i]+p[i+n] == 2*n-1) return 0;
	}
	int N = 2*n + 50;
	vector<int> fat(N, 1), ifat(N);
	for (int i = 1; i < N; ++i) fat[i] = i * fat[i-1] % mod;
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			e /= 2, b = b * b % mod;
		}
		return ans;
	};
	ifat[N-1] = fexp(fat[N-1], mod-2);
	for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
	auto ncr = [&] (int a, int b) {
		if (b > a or min(a, b) < 0) return 0LL;
		return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
	};
	vector<int> pot(N, 1);
	for (int i = 1; i < N; ++i) pot[i] = 2 * pot[i-1] % mod;
	vector<mint> P(B+1), Q(falta+1);
	for (int i = 0; i <= B; ++i) {
		P[i] = ncr(B, i);
		if (i & 1) P[i] *= -1;
	}
	for (int i = 0; i <= falta; ++i) Q[i] = fat[i];
	auto res = convolution(P, Q);
	mint ans = 0;
	for (int i = 0; i <= min(A, C); ++i) {
		int z = ncr(A, i) * ncr(C, i) % mod * pot[i] % mod * fat[i] % mod;
		if (i & 1) z = (mod - z) % mod;
		int want = falta - 2 * i;
		if (0 <= want and want < res.size()) {
			ans += z * res[want];
		}
	}
	//ans = 0;
	//for (int i = 0; i <= min(A, C); ++i) {
	//	for (int j = 0; j <= B; ++j) {
	//		int ways = ncr(A, i) * ncr(C, i) % mod * fat[i] % mod * pot[i] % mod * ncr(B, j) % mod * fat[falta - 2 * i - j] % mod;
	//		if ((i+j) % 2) ans -= ways;
	//		else ans = (ans + ways) % mod;
	//	}
	//}
	return ans.v;
}

int brute(int n, vector<int> p) {
	vector<int> pp(2*n);
	iota(begin(pp), end(pp), 0);
	int ans = 0;
	do {
		bool ok = 1;
		for (int i = 0; i < 2*n; ++i) {
			if (p[i] != -1) ok &= (pp[i] == p[i]);
		}
		if (!ok) continue;
		for (int i = 0; i < n; ++i) ok &= (pp[i] + pp[i+n] != 2*n-1);
		ans += ok;
	} while (next_permutation(begin(pp), end(pp)));
	return ans;
};

mt19937 rng(69);
int rnd(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
};
int32_t main() {_
#ifndef gato
	int n; cin >> n;
	vector<int> p(2*n);
	for (auto& x : p) cin >> x;
	for (auto& x : p) {
		if (x != -1) x--;
	}
	cout << solve(n, p) << endl;
#else
	int t = 1;
	while (true) {
		int n = rnd(1, 4);
		vector<int> p(2*n); iota(begin(p), end(p), 0);
		shuffle(begin(p), end(p), rng);
		for (int i = 0; i < 2*n; ++i) {
			if (rnd(0, 1)) p[i] = -1;
		}
		auto my = solve(n, p);
		auto ans = brute(n, p);
		if (my != ans) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << endl;
			for (auto x : p) {
				if (x == -1) cout << x << " ";
				else cout << x+1 << " ";
			}
			cout << endl;
			cout << "solve: " << my << endl;
			cout << "brute: " << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#endif
}
