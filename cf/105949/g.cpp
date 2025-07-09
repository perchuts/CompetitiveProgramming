#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) int((x).size())

template<int M, int R>
struct Mod {
  static const int MOD = M, ROOT = R;
  int x;
  Mod(ll y = 0) : x(y % M) { x += (x < 0) * M; }
  Mod& operator+=(Mod o) {
    if ((x += o.x) >= M) x -= M;
    return *this; }
  Mod& operator-=(Mod o) {
    if ((x -= o.x) < 0) x += M;
    return *this; }
  Mod& operator*=(Mod o) {
    x = 1ll * x * o.x % M;
    return *this; }
  Mod& operator/=(Mod o) { return *this *= o.inv(); }
  friend Mod operator+(Mod a, Mod b) { return a += b; }
  friend Mod operator-(Mod a, Mod b) { return a -= b; }
  friend Mod operator*(Mod a, Mod b) { return a *= b; }
  friend Mod operator/(Mod a, Mod b) { return a /= b; }
  auto operator<=>(const Mod&) const = default;
  Mod pow(ll n) const {
    Mod a = x, b = 1;
    for (; n; n /= 2, a *= a) if (n & 1) b *= a;
    return b;
  }
  Mod inv() const { assert(x != 0); return pow(M - 2); }
};
using mint = Mod<998244353, 3>;

template<class T>
void ntt(vector<T>& a, bool inv) {
  int n = sz(a); vector<T> b(n);
  for (int i = n / 2; i; i /= 2, swap(a, b)) {
    T w = T(T::ROOT).pow((T::MOD - 1) / n * i), m = 1;
    for (int j = 0; j < n; j += 2 * i, m *= w) rep(k, 0, i) {
      T u = a[j + k], v = a[j + k + i] * m;
      b[j / 2 + k] = u + v, b[j / 2 + k + n / 2] = u - v;
    }
  }
  if (inv) {
    reverse(1 + all(a));
    T z = T(n).inv(); rep(i, 0, n) a[i] *= z;
  }
}
template<class T>
vector<T> conv(vector<T> a, vector<T> b) {
  int s = sz(a) + sz(b) - 1, n = 1 << __lg(2 * s - 1);
  a.resize(n); ntt(a, 0); b.resize(n); ntt(b, 0);
  rep(i, 0, n) a[i] *= b[i];
  ntt(a, 1); a.resize(s);
  return a;
}

using Poly = vector<mint>;
Poly& operator+=(Poly& a, const Poly& b) {
  a.resize(max(sz(a), sz(b)));
  rep(i, 0, sz(b)) a[i] += b[i];
  return a;
}
Poly& operator-=(Poly& a, const Poly& b) {
  a.resize(max(sz(a), sz(b)));
  rep(i, 0, sz(b)) a[i] -= b[i];
  return a;
}
Poly& operator*=(Poly& a, const Poly& b) {
  if (sz(a) + sz(b) < 100) {
    Poly c(sz(a) + sz(b) - 1);
    rep(i, 0, sz(a)) rep(j, 0, sz(b)) c[i + j] += a[i] * b[j];
    return a = c;
  }
  return a = conv(move(a), b);
}
Poly operator+(Poly a, const Poly& b) { return a += b; }
Poly operator-(Poly a, const Poly& b) { return a -= b; }
Poly operator*(Poly a, const Poly& b) { return a *= b; }

Poly modK(Poly a, int k) { return a.resize(min(sz(a), k)), a; }
Poly inv(const Poly& a) {
  Poly b = {1 / a[0]};
  while (sz(b) < sz(a))
    b = modK(b * (Poly{2} - modK(a, 2 * sz(b)) * b), 2 * sz(b));
  return modK(b, sz(a));
}

Poly deriv(Poly a) {
  if (!sz(a)) return {};
  rep(i, 1, sz(a)) a[i - 1] = a[i] * i;
  return a.pop_back(), a;
}
Poly integr(const Poly& a) {
  if (!sz(a)) return {};
  Poly b(sz(a) + 1);
  b[1] = 1;
  rep(i, 2, sz(b)) b[i] = b[mint::MOD % i] * -(mint::MOD / i);
  rep(i, 1, sz(b)) b[i] *= a[i - 1];
  return b;
}

Poly log(const Poly& a) {
  return modK(integr(deriv(a) * inv(a)), sz(a));
}
Poly exp(const Poly& a) {
  Poly b = {1};
  if (!sz(a)) return b;
  while (sz(b) < sz(a)) {
    b.resize(sz(b) * 2);
    b *= Poly{1} + modK(a, sz(b)) - log(b);
    b.resize(sz(b) / 2 + 1);
  }
  return modK(b, sz(a));
}

Poly pow(Poly a, ll m) {
  int p = 0, n = sz(a);
  while (p < sz(a) && a[p] == 0) ++p;
  if (ll(m) * p >= sz(a)) return Poly(sz(a));
  mint j = a[p];
  a = Poly(p + all(a)) * Poly{1 / j};
  a.resize(n);
  auto res =  exp(log(a) * Poly{m}) * Poly{j.pow(m)};
  res.insert(res.begin(), p*m, 0);
  return {res.begin(), res.begin()+n};
}

Poly &operator/=(Poly& a, Poly b) {
  if (sz(a) < sz(b)) return a = {};
  int s = sz(a) - sz(b) + 1;
  reverse(all(a)), reverse(all(b));
  a.resize(s), b.resize(s);
  a = a * inv(b);
  a.resize(s), reverse(all(a));
  return a;
}
Poly operator/(Poly a, Poly b) { return a /= b; }
Poly &operator%=(Poly& a, Poly b) {
  if (sz(a) < sz(b)) return a;
  Poly c = (a / b) * b;
  a.resize(sz(b) - 1);
  rep(i, 0, sz(a)) a[i] -= c[i];
  return a;
}
Poly operator%(Poly a, Poly b) { return a %= b; }

vector<mint> eval(const Poly& a, const vector<mint>& x) {
  int n = sz(x);
  if (!n) return {};
  vector<Poly> up(2 * n);
  rep(i, 0, n) up[i + n] = Poly{0 - x[i], 1};
  for (int i = n - 1; i > 0; i--)
    up[i] = up[2 * i] * up[2 * i + 1];
  vector<Poly> down(2 * n);
  down[1] = a % up[1];
  rep(i, 2, 2 * n) down[i] = down[i / 2] % up[i];
  vector<mint> y(n);
  rep(i, 0, n) y[i] = down[i + n][0];
  return y;
}

Poly interp(vector<mint> x, vector<mint> y) {
  int n = sz(x);
  vector<Poly> up(2 * n);
  rep(i, 0, n) up[i + n] = Poly{0 - x[i], 1};
  for (int i = n - 1; i > 0; i--)
    up[i] = up[2 * i] * up[2 * i + 1];
  vector<mint> a = eval(deriv(up[1]), x);
  vector<Poly> down(2 * n);
  rep(i, 0, n) down[i + n] = Poly{y[i] / a[i]};
  for(int i = n - 1; i > 0; i--)
    down[i] = down[2*i] * up[2*i+1] + down[2*i+1] * up[2*i];
  return down[1];
}

Poly subsetSum(Poly a) {
  int n = sz(a);
  Poly b(n);
  rep(i, 1, n) b[i] = mint(i).inv() * (i % 2 ? 1 : -1);
  for (int i = n - 2; i > 0; i--)
    for (int j = 2; i * j < n; j++)
      a[i * j] += b[j] * a[i];
  return exp(a);
}


#define P 998244353
#define MAGIC 1

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

vector<int> D(vector<int> p) {
	if (p.empty()) return p;
	for (int i = 0; i + 1 < p.size(); i++) p[i] = (i + 1) * p[i + 1] % P;
	p.pop_back();
	return p;
}

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

pair<vector<int>, vector<int>> divslow(const vector<int>& a, const vector<int>& b) {
	vector<int> q, r = a;
	while (r.size() >= b.size()) {
		q.push_back(r.back() * inv(b.back()) % P);
		if (q.back() != 0) {
			for (int i = 0; i < b.size(); i++) {
				r.end()[-i-1] = sub(r.end()[-i-1], q.back() * b.end()[-i-1] % P);
			}
		}
		r.pop_back();
	}
	return {q, r};
}

vector<int> divmod(vector<int>& a, const vector<int>& b) {
	if (a.size() >= b.size()) {
		auto q = a;
		auto ps = b;
		int s = int(a.size()) - int(ps.size()) + 1;
		int nn = 1; for (; nn < s; nn <<= 1) {}
		reverse(q.begin(), q.end());
		reverse(ps.begin(), ps.end());
		q.resize(nn); ps.resize(nn);
		ps = inv(ps);
		q = conv(q, ps);
		q.resize(s); reverse(q.begin(), q.end());
		q = conv(q, b);
		//Poly Q = (*this / fs) * fs;
		//this->resize(fs.size() - 1);
		a.resize(b.size() - 1);
		for (int x = 0; x < int(a.size()); ++x) a[x] = sub(a[x], q[x]);
	}
	while (a.size() && a.back() == 0) a.pop_back();
	return a;
}

namespace multipoint {
	vector<int> evaluate(vector<int>& fs, vector<int>& qs) {
		int N = int(qs.size());
		if (N == 0) return {};
		vector<vector<int>> up(2 * N);
		for (int x = 0; x < N; ++x) {
			up[x + N] = {P-qs[x], 1};
		}
		for (int x = N-1; x >= 1; --x) {
			up[x] = conv(up[2 * x], up[2 * x + 1]);
		}
		vector<vector<int>> down(2 * N);
		down[1] = divmod(fs, up[1]);
		for (int x = 2; x < 2*N; ++x) {
			down[x] = divmod(down[x / 2], up[x]);
		}
		vector<int> y(N);
		for (int x = 0; x < N; ++x) {
			y[x] = (down[x + N].empty() ? 0 : down[x + N][0]);
		}
		return y;
	}
}

int32_t main() {
	fast_io;

	for (int seed = 0; ; seed++) {

		//int n = rand() % 3 + 1;
		//set<int> st;
		//while (st.size() != n + 1) st.insert(rand() % 10 + 1);
		//int t = *st.begin(); st.erase(t);
		//vector<int> a(st.begin(), st.end()); random_shuffle(a.begin(), a.end());

		int n, t; cin >> n >> t;
		vector<int> a(n);
		for(auto& x : a) cin >> x;

		for(int i=0;i<n;i++){
			if(a[i] == t){
				for(int j=0;j<n;j++){
					if(j == i) cout << 1 << " ";
					else cout << 0 << " ";
				}
				cout << endl;
				exit(0);
			}
		}

		// tudo tem que ser distinto
		auto b = a;
		sort(b.begin(), b.end());
		b.erase(unique(b.begin(), b.end()), b.end());
		assert(b.size() == n);

		vector<int> MvKaio(n+1); // coeficientes daquele polinomio
		auto vai = [&] (auto&& self, int l, int r) -> vector<int> {
			if (l + 1 == r) return {P-a[l], 1};
			int mid = (l + r) / 2;
			auto ql = self(self, l, mid);
			auto qr = self(self, mid, r);
			auto res = conv(ql, qr);
			return res;
		};
		MvKaio = vai(vai, 0, n);
		//vector<int> g;

		vector<mint> dmv(n + 1);
		for (int i = 0; i <= n; i++) dmv[i] = MvKaio[i];
		dmv = deriv(dmv);
		vector<mint> pts(n);
		for (int i = 0; i < n; i++) pts[i] = a[i];
		auto g = eval(dmv, pts);

		int pt = 0;
		for(int i=0, ti=1; i<=n; i++, ti = ti * t % P){
			pt = (pt + ti * MvKaio[i]) % P;
		}

		vector<int> ans(n);
		for(int i=0;i<n;i++){
			int tai = (t + P- a[i]) % P * g[i].x % P;
			ans[i] = pt * fexp(tai, P-2) % P;
			cout << pt * fexp(tai, P-2) % P << " ";
		}
		cout << endl;
	
		//bool ok = true;
		//cout << n << " " << t << endl;
		//for (int i = 0; i < n; i++) cout << a[i] << " ";
		//cout << endl;

		//for (int i = 0; i < n; i++) cout << ans[i] << " ";
		//cout << endl;
		//for (int j = 0; j < n; j++) {
		//	int val = 0;
		//	for (int i = 0; i < n; i++) {
		//		val = (val + (fexp(a[i], j) * ans[i] % P)) % P;
		//	}
		//	//assert(val == fexp(t, j));
		//	cout << j << ": " << val << " " << fexp(t, j) << endl;
		//	ok &= val == fexp(t, j);
		//}
		//if (!ok) break;
		break;
	}
}
