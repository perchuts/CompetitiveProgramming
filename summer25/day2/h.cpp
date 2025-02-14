#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int p;
struct mint {
	ll expo(ll b, ll e) {
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
		if (v_ >= p or v_ <= -p) v_ %= p;
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
	m& operator /=(const m& a) {
		v = v * inv(a.v) % p;
		return *this;
	}
	m operator -(){ return m(-v); }
	m& operator ^=(ll e) {
		if (e < 0) {
			v = inv(v);
			e = -e;
		}
		v = expo(v, e);
		return *this;
	}
	bool operator ==(const m& a) { return v == a.v; }
	bool operator !=(const m& a) { return v != a.v; }

	friend m operator +(m a, m b) { return a += b; }
	friend m operator -(m a, m b) { return a -= b; }
	friend m operator *(m a, m b) { return a *= b; }
	friend m operator /(m a, m b) { return a /= b; }
	friend m operator ^(m a, ll e) { return a ^= e; }

	friend ostream& operator <<(ostream& out, m a) {
		return out << a.v;
	}
};

template<typename T> T evaluate(vector<T> c, vector<T> s, ll k) {
	int n = c.size();
	assert(c.size() <= s.size());

	auto mul = [&](const vector<T>& a, const vector<T>& b) {
		vector<T> ret(a.size() + b.size() - 1);
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < b.size(); j++)
				ret[i+j] += a[i]*b[j];
		for (int i = ret.size()-1; i >= n; i--)
			for (int j = n-1; j >= 0; j--)
				ret[i-j-1] += ret[i]*c[j];
		ret.resize(min<int>(ret.size(), n));
		return ret;
	};

	vector<T> a = n == 1 ? vector<T>({c[0]}) : vector<T>({0, 1}), x = {1};
	while (k) {
		if (k&1) x = mul(x, a);
		a = mul(a, a), k >>= 1;
	}
	x.resize(n);

	T ret = 0;
	for (int i = 0; i < n; i++) ret += x[i] * s[i];
	return ret;
}

template<typename T> vector<T> berlekamp_massey(vector<T> s) {
	int n = s.size(), l = 0, m = 1;
	vector<T> b(n), c(n);
	T ld = b[0] = c[0] = 1;
	for (int i = 0; i < n; i++, m++) {
		T d = s[i];
		for (int j = 1; j <= l; j++) d += c[j] * s[i-j];
		if (d == 0) continue;
		vector<T> temp = c;
		T coef = d / ld;
		for (int j = m; j < n; j++) c[j] -= coef * b[j-m];
		if (2*l <= i) l = i + 1 - l, b = temp, ld = d, m = 0;
	}
	c.resize(l + 1);
	c.erase(c.begin());
	for (T& x : c) x = -x;
	return c;
}

template<typename T> T guess_kth(const vector<T>& s, ll k) {
	auto c = berlekamp_massey(s);
	return evaluate(c, s, k);
}

//mint eval(int n, int m) {
//	vector dp(m, vector(m, mint(0)));
//	dp[0][0] = 1;
//	for (int i = 0; i < n; i++) {
//		vector ndp(m, vector(m, mint(0)));
//
//		for (int j = 1; j < m; j++) {
//			for (int k = 0; k < m; k++) dp[j][k] += dp[j - 1][k];
//		}
//		for (int j = 0; j < m; j++) {
//			for (int k = 1; k < m; k++) dp[j][k] += dp[j][k - 1];
//		}
//
//		for (int l1 = 0; l1 < m; l1++) {
//			for (int r1 = 0; l1 + r1 < m; r1++) {
//				ndp[l1][r1] = dp[m - l1 - 1][m - r1 - 1];
//			}
//		}
//
//		dp = ndp;
//	}
//	
//	mint tot = 0;
//	for (int l = 0; l < m; l++) {
//		for (int r = 0; l + r < m; r++) {
//			tot += dp[l][r];
//		}
//	}
//
//	return tot;
//}

//void pol(vector<mint>& a) {
//	int n = a.size();
//
//	vector<mint> a0;
//	int grau = -2;
//	while (a.size() > 1) {
//		bool zero = true;
//		for (int i = 0; i < a.size(); i++) 
//			zero &= a[i] == 0;
//
//		for (int i = 0; i < 20; i++) 
//			cout << a[i] << " ";
//		cout << endl;
//
//		a0.push_back(a[0]);
//		grau++;
//
//		if (zero) break;
//
//
//		vector<mint> b;
//		for (int i = 1; i < a.size(); i++)
//			b.push_back(a[i] - a[i - 1]);
//
//		a = b;
//	}
//
//	cout << "grau = " << grau << endl;
//	for (auto i : a0) cout << i << " ";
//	cout << endl;
//	cout << endl;
//	cout << endl;
//}

int32_t main() {
	fast_io;

	int n; cin >> n;
	cin >> p;

	auto eval = [&] (int n, int m) {
		vector dp(m, vector(m, mint(0)));
		dp[0][0] = 1;
		for (int i = 0; i < n; i++) {
			vector ndp(m, vector(m, mint(0)));

			for (int j = 1; j < m; j++) {
				for (int k = 0; k < m; k++) dp[j][k] += dp[j - 1][k];
			}
			for (int j = 0; j < m; j++) {
				for (int k = 1; k < m; k++) dp[j][k] += dp[j][k - 1];
			}

			for (int l1 = 0; l1 < m; l1++) {
				for (int r1 = 0; l1 + r1 < m; r1++) {
					ndp[l1][r1] = dp[m - l1 - 1][m - r1 - 1];
				}
			}

			dp = ndp;
		}

		mint tot = 0;
		for (int l = 0; l < m; l++) {
			for (int r = 0; l + r < m; r++) {
				tot += dp[l][r];
			}
		}

		return tot;
	}

	return 0;

//	for (int n = 1; n <= _n; n++) {
//
//		vector<mint> v = {0};
//		for (int i = 1; i <= mx; i++) {
//			v.push_back(eval(n, i));
//		}
//
//		int len;
//		for (len = 5; len <= mx; len++) {
//			vector<mint> w = v;
//			w.resize(len);
//
//			bool ok = true;
//			for (int i = 0; i < mx; i++)
//				ok &= v[i] == guess_kth(w, i);
//
//			if (ok) break;
//		}
//
//		cout << "n=" << n << endl;
//
//		vector<mint> w = v;
//		auto coef = berlekamp_massey(w);
//		reverse(coef.begin(), coef.end());
//		coef.push_back(1);
//
//		for (int i = 0; i < coef.size(); i++) {
//			int x = coef[i].v;
//			if (x > 500000) cout << "-" << (MOD-x) << " ";
//			else cout << x << " ";
//		}
//		cout << endl;
//
//		pol(v);
//	}
}
